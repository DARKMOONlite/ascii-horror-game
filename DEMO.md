# ASCII Image Converter - Feature Demonstration

## Basic Colored Output
```bash
./build/ascii_converter test_image.ppm --width 60
```

## Without Color (Monochrome)
```bash
./build/ascii_converter test_image.ppm --width 60 --no-color
```

## With Sharpen Kernel
Enhances edges and details:
```bash
./build/ascii_converter test_image.ppm --width 60 --kernel sharpen
```

## With Blur Kernel
Applies Gaussian blur:
```bash
./build/ascii_converter test_image.ppm --width 60 --kernel blur
```

## With Edge Detection Kernel
Perfect for horror game aesthetic - highlights edges:
```bash
./build/ascii_converter test_image.ppm --width 60 --kernel edge
```

## Different Widths
Adjust output size:
```bash
./build/ascii_converter test_image.ppm --width 40
./build/ascii_converter test_image.ppm --width 80
./build/ascii_converter test_image.ppm --width 120
```

## Complex Example
```bash
./build/ascii_converter example_gradient.ppm --width 70
```

## Help
```bash
./build/ascii_converter --help
```
