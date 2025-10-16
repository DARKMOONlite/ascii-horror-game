#!/usr/bin/env python3
"""
TTF to ASCII Converter
Converts TTF font files to ASCII text files containing font metadata and character information.
"""

import sys
import os
import argparse
from pathlib import Path

try:
    from fontTools.ttLib import TTFont
    from fontTools.misc.textTools import safeEval
    from fontTools.pens.recordingPen import RecordingPen
    from fontTools.pens.transformPen import TransformPen
    from PIL import Image, ImageDraw, ImageFont
    import numpy as np
except ImportError as e:
    print("Error: Required libraries are missing. Install them with: pip install fonttools Pillow reportlab")
    print(f"Specific error: {e}")
    sys.exit(1)


def extract_font_info(ttf_path):
    """Extract comprehensive information from a TTF font file."""
    try:
        font = TTFont(ttf_path)
        info = {}
        
        # Extract font name table information
        if 'name' in font:
            name_table = font['name']
            info['names'] = {}
            
            # Common name IDs and their meanings
            name_ids = {
                0: 'Copyright',
                1: 'Font Family',
                2: 'Font Subfamily',
                3: 'Unique Font Identifier',
                4: 'Full Font Name',
                5: 'Version',
                6: 'PostScript Name',
                7: 'Trademark',
                8: 'Manufacturer',
                9: 'Designer',
                10: 'Description',
                11: 'Vendor URL',
                12: 'Designer URL',
                13: 'License Description',
                14: 'License Info URL',
                16: 'Typographic Family',
                17: 'Typographic Subfamily'
            }
            
            for record in name_table.names:
                if record.nameID in name_ids:
                    try:
                        name = record.toUnicode()
                        info['names'][name_ids[record.nameID]] = name
                    except UnicodeDecodeError:
                        continue
        
        # Extract character map (cmap) information
        if 'cmap' in font:
            info['characters'] = {}
            cmap = font.getBestCmap()
            if cmap:
                for unicode_val, glyph_name in cmap.items():
                    try:
                        char = chr(unicode_val)
                        if char.isprintable():
                            info['characters'][char] = {
                                'unicode': unicode_val,
                                'unicode_hex': f"U+{unicode_val:04X}",
                                'glyph_name': glyph_name
                            }
                    except ValueError:
                        continue
        
        # Extract metrics information
        if 'head' in font:
            head_table = font['head']
            info['metrics'] = {
                'units_per_em': head_table.unitsPerEm,
                'created': str(head_table.created) if hasattr(head_table, 'created') else 'Unknown',
                'modified': str(head_table.modified) if hasattr(head_table, 'modified') else 'Unknown',
                'font_revision': head_table.fontRevision if hasattr(head_table, 'fontRevision') else 'Unknown'
            }
        
        # Extract OS/2 table information for additional metrics
        if 'OS/2' in font:
            os2_table = font['OS/2']
            if 'metrics' not in info:
                info['metrics'] = {}
            info['metrics'].update({
                'weight_class': os2_table.usWeightClass if hasattr(os2_table, 'usWeightClass') else 'Unknown',
                'width_class': os2_table.usWidthClass if hasattr(os2_table, 'usWidthClass') else 'Unknown'
            })
        return info
        
    except Exception as e:
        raise Exception(f"Error reading TTF file: {str(e)}")


def char_to_ascii_art(char, font_path, size=32, width=16, height=16):
    """Convert a single character to ASCII art representation."""
    try:
        # Create an image with the character
        img_size = size * 2  # Make it larger for better quality
        image = Image.new('L', (img_size, img_size), 255)  # White background
        draw = ImageDraw.Draw(image)
        
        # Load the font
        try:
            pil_font = ImageFont.truetype(font_path, size)
        except OSError:
            # Fallback to default font if TTF loading fails
            pil_font = ImageFont.load_default()
        
        # Get text bounding box
        bbox = draw.textbbox((0, 0), char, font=pil_font)
        text_width = bbox[2] - bbox[0]
        text_height = bbox[3] - bbox[1]
        
        # Center the text
        x = (img_size - text_width) // 2
        y = (img_size - text_height) // 2
        
        # Draw the character in black
        draw.text((x, y), char, font=pil_font, fill=0)
        
        # Resize to target dimensions
        image = image.resize((width, height), Image.Resampling.LANCZOS)
        
        # Convert to numpy array
        img_array = np.array(image)
        
        # Define ASCII characters from darkest to lightest
        ascii_chars = " .:-+*#%@"
        
        # Convert grayscale values to ASCII
        ascii_art = []
        for row in img_array:
            ascii_row = ""
            for pixel in row:
                # Invert the pixel value (0=black, 255=white) and map to ASCII chars
                char_index = int((255 - pixel) / 255 * (len(ascii_chars) - 1))
                ascii_row += ascii_chars[char_index]
            ascii_art.append(ascii_row)
        
        return ascii_art
        
    except Exception as e:
        # Return a simple representation if ASCII art generation fails
        return [f"[Error generating ASCII art for '{char}': {str(e)}]"]


def generate_character_ascii_art(font_info, font_path, art_width=12, art_height=12):
    """Generate ASCII art for all characters in the font."""
    if 'characters' not in font_info:
        return {}
    
    ascii_art_chars = {}
    total_chars = len(font_info['characters'])
    processed = 0
    
    print(f"Generating ASCII art for {total_chars} characters...")
    
    for char, char_info in font_info['characters'].items():
        try:
            ascii_art = char_to_ascii_art(char, font_path, 
                                        size=48, width=art_width, height=art_height)
            ascii_art_chars[char] = {
                'info': char_info,
                'ascii_art': ascii_art
            }
            processed += 1
            if processed % 50 == 0:
                print(f"Processed {processed}/{total_chars} characters...")
        except Exception as e:
            # Skip characters that can't be processed
            print(f"Skipping character '{char}': {str(e)}")
            continue
    
    print(f"ASCII art generation complete! Processed {len(ascii_art_chars)} characters.")
    return ascii_art_chars


def format_ascii_output(font_info, ttf_path, ascii_art_chars=None):
    """Format the extracted font information as ASCII text."""
    output_lines = []
    
    # Header
    output_lines.append("=" * 80)
    output_lines.append(f"TTF FONT INFORMATION: {os.path.basename(ttf_path)}")
    output_lines.append("=" * 80)
    output_lines.append("")
    
    # Font Names and Metadata
    if 'names' in font_info:
        output_lines.append("FONT METADATA:")
        output_lines.append("-" * 40)
        for name_type, value in font_info['names'].items():
            output_lines.append(f"{name_type:<25}: {value}")
        output_lines.append("")
    
    # Metrics
    if 'metrics' in font_info:
        output_lines.append("FONT METRICS:")
        output_lines.append("-" * 40)
        for metric_name, value in font_info['metrics'].items():
            formatted_name = metric_name.replace('_', ' ').title()
            output_lines.append(f"{formatted_name:<25}: {value}")
        output_lines.append("")
    
    # Character Information with ASCII Art
    if 'characters' in font_info:
        output_lines.append("CHARACTER MAP:")
        output_lines.append("-" * 40)
        output_lines.append(f"Total Characters: {len(font_info['characters'])}")
        output_lines.append("")
        
        # Group characters by type
        ascii_chars = []
        extended_chars = []
        
        for char, char_info in font_info['characters'].items():
            unicode_val = char_info['unicode']
            if 32 <= unicode_val <= 126:  # Standard ASCII printable
                ascii_chars.append((char, char_info))
            else:
                extended_chars.append((char, char_info))
        
        # ASCII Characters with ASCII Art
        if ascii_chars:
            output_lines.append("ASCII CHARACTERS (32-126) WITH ASCII ART:")
            output_lines.append("=" * 60)
            for char, char_info in sorted(ascii_chars, key=lambda x: x[1]['unicode']):
                output_lines.append(f"\nCharacter: '{char}' | Unicode: {char_info['unicode_hex']} | Glyph: {char_info['glyph_name']}")
                output_lines.append("-" * 50)
                
                # Add ASCII art if available
                if ascii_art_chars and char in ascii_art_chars:
                    ascii_art = ascii_art_chars[char]['ascii_art']
                    for art_line in ascii_art:
                        output_lines.append(art_line)
                else:
                    output_lines.append(f"[ASCII art not available for '{char}']")
                output_lines.append("")
            output_lines.append("")
        
        # Extended Characters (first 50 with ASCII art for readability)
        if extended_chars:
            output_lines.append("EXTENDED CHARACTERS (sample with ASCII art):")
            output_lines.append("=" * 60)
            sample_extended = sorted(extended_chars, key=lambda x: x[1]['unicode'])[:50]
            
            for char, char_info in sample_extended:
                output_lines.append(f"\nCharacter: '{char}' | Unicode: {char_info['unicode_hex']} | Glyph: {char_info['glyph_name']}")
                output_lines.append("-" * 50)
                
                # Add ASCII art if available
                if ascii_art_chars and char in ascii_art_chars:
                    ascii_art = ascii_art_chars[char]['ascii_art']
                    for art_line in ascii_art:
                        output_lines.append(art_line)
                else:
                    output_lines.append(f"[ASCII art not available for '{char}']")
                output_lines.append("")
            
            if len(extended_chars) > 50:
                output_lines.append(f"\n... and {len(extended_chars) - 50} more extended characters")
            output_lines.append("")
    
    # Footer
    output_lines.append("=" * 80)
    output_lines.append("End of font information")
    output_lines.append("=" * 80)
    
    return "\n".join(output_lines)


def main():
    """Main function to handle command line arguments and conversion."""
    parser = argparse.ArgumentParser(
        description="Convert TTF font files to ASCII text files containing font information",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python ttf-convert.py font.ttf
  python ttf-convert.py font.ttf -o output.txt
  python ttf-convert.py *.ttf
        """
    )
    parser.add_argument('ttf_files', nargs='+', help='TTF font file(s) to convert')
    parser.add_argument('-o', '--output', help='Output file name (for single input file)')
    parser.add_argument('-d', '--output-dir', help='Output directory for multiple files')
    parser.add_argument('--art-width', type=int, default=12, help='Width of ASCII art grid for each character (default: 12)')
    parser.add_argument('--art-height', type=int, default=12, help='Height of ASCII art grid for each character (default: 12)')
    parser.add_argument('--no-ascii-art', action='store_true', help='Skip ASCII art generation for faster processing')
    
    args = parser.parse_args()
    
    # Expand wildcards and validate files
    ttf_files = []
    for pattern in args.ttf_files:
        files = list(Path('.').glob(pattern))
        if files:
            ttf_files.extend([f for f in files if f.suffix.lower() == '.ttf'])
        elif os.path.exists(pattern) and pattern.lower().endswith('.ttf'):
            ttf_files.append(Path(pattern))
    
    if not ttf_files:
        print("Error: No valid TTF files found")
        sys.exit(1)
      # Process files
    for ttf_file in ttf_files:
        try:
            print(f"Processing: {ttf_file}")
            
            # Extract font information
            font_info = extract_font_info(str(ttf_file))
            
            # Generate ASCII art for characters (unless disabled)
            ascii_art_chars = None
            if not args.no_ascii_art:
                ascii_art_chars = generate_character_ascii_art(
                    font_info, str(ttf_file), 
                    art_width=args.art_width, 
                    art_height=args.art_height
                )
            
            # Format as ASCII
            ascii_content = format_ascii_output(font_info, str(ttf_file), ascii_art_chars)
            
            # Determine output file name
            if len(ttf_files) == 1 and args.output:
                output_file = args.output
            else:
                output_name = ttf_file.stem + '.txt'
                if args.output_dir:
                    output_file = os.path.join(args.output_dir, output_name)
                    os.makedirs(args.output_dir, exist_ok=True)
                else:
                    output_file = output_name
            
            # Write output file
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(ascii_content)
            
            print(f"Created: {output_file}")
            
        except Exception as e:
            print(f"Error processing {ttf_file}: {str(e)}")
            continue
    
    print("Conversion complete!")


if __name__ == "__main__":
    main()