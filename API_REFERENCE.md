# ASCII Display Framework API Reference

## Namespace

All classes are in the `ASCIIDisplay` namespace.

---

## TerminalUtils

Static utility class for terminal manipulation.

### Methods

#### `static void clearScreen()`
Clears the entire terminal screen.

#### `static void moveCursor(int row, int col)`
Moves cursor to specific position (0-indexed).
- **Parameters:**
  - `row`: Row position (0 = top)
  - `col`: Column position (0 = left)

#### `static void hideCursor()`
Hides the terminal cursor.

#### `static void showCursor()`
Shows the terminal cursor.

#### `static void setColor(Color fg, Color bg = Color::RESET)`
Sets text foreground and optional background color.
- **Parameters:**
  - `fg`: Foreground color
  - `bg`: Background color (optional)

#### `static void resetFormat()`
Resets all text formatting to defaults.

#### `static void getTerminalSize(int& rows, int& cols)`
Gets the current terminal size.
- **Parameters:**
  - `rows`: Output parameter for row count
  - `cols`: Output parameter for column count

#### `static void saveCursor()`
Saves current cursor position.

#### `static void restoreCursor()`
Restores previously saved cursor position.

#### `static void enableAltScreen()`
Enables alternative screen buffer.

#### `static void disableAltScreen()`
Disables alternative screen buffer.

#### `static Color rgbToColor(int r, int g, int b)`
Converts RGB values to nearest ANSI color.
- **Parameters:**
  - `r`: Red component (0-255)
  - `g`: Green component (0-255)
  - `b`: Blue component (0-255)
- **Returns:** Nearest ANSI color enum

#### `static char brightnessToChar(int brightness)`
Converts brightness value to ASCII character.
- **Parameters:**
  - `brightness`: Brightness level (0-255)
- **Returns:** ASCII character representing brightness

---

## Color

Enum class for ANSI colors.

### Values
- `BLACK` (30)
- `RED` (31)
- `GREEN` (32)
- `YELLOW` (33)
- `BLUE` (34)
- `MAGENTA` (35)
- `CYAN` (36)
- `WHITE` (37)
- `BRIGHT_BLACK` (90)
- `BRIGHT_RED` (91)
- `BRIGHT_GREEN` (92)
- `BRIGHT_YELLOW` (93)
- `BRIGHT_BLUE` (94)
- `BRIGHT_MAGENTA` (95)
- `BRIGHT_CYAN` (96)
- `BRIGHT_WHITE` (97)
- `RESET` (0)

---

## Panel

Represents a rectangular panel on the terminal.

### Constructor

#### `Panel(int x, int y, int width, int height, const std::string& title = "")`
Creates a new panel.
- **Parameters:**
  - `x`: X position on terminal
  - `y`: Y position on terminal
  - `width`: Panel width
  - `height`: Panel height
  - `title`: Optional panel title

### Methods

#### `void setPosition(int x, int y)`
Sets the panel's position on the terminal.

#### `void setSize(int width, int height)`
Sets the panel's size. Content buffer is recreated.

#### `void setTitle(const std::string& title)`
Sets the panel's title.

#### `void setBorder(bool enabled)`
Enables or disables the panel border.

#### `void setBorderColor(Color color)`
Sets the color of the panel border.

#### `void clear()`
Clears all content in the panel.

#### `void writeText(int row, int col, const std::string& text, Color fg = Color::WHITE)`
Writes text at position within panel.
- **Parameters:**
  - `row`: Row position (relative to content area)
  - `col`: Column position (relative to content area)
  - `text`: Text to write
  - `fg`: Text color

#### `void setChar(int row, int col, char ch, Color fg = Color::WHITE)`
Sets a single character at position.
- **Parameters:**
  - `row`: Row position
  - `col`: Column position
  - `ch`: Character to set
  - `fg`: Character color

#### `void fill(char ch, Color fg = Color::WHITE)`
Fills entire panel with a character.

#### `void drawLine(int row, int col, int length, char ch = '-', bool horizontal = true)`
Draws a line within the panel.
- **Parameters:**
  - `row`: Starting row
  - `col`: Starting column
  - `length`: Length of line
  - `ch`: Character to use
  - `horizontal`: True for horizontal, false for vertical

#### `void drawBox(int row, int col, int width, int height, char ch = '#')`
Draws a box outline within the panel.

#### `void render() const`
Renders the panel to the terminal.

#### Getters
- `int getX() const`: Get X position
- `int getY() const`: Get Y position
- `int getWidth() const`: Get total width
- `int getHeight() const`: Get total height
- `int getContentWidth() const`: Get content area width
- `int getContentHeight() const`: Get content area height

---

## PanelManager

Manages multiple panels and their rendering.

### Constructor/Destructor

#### `PanelManager()`
Creates a new panel manager.

#### `~PanelManager()`
Destroys the panel manager and calls cleanup().

### Methods

#### `void addPanel(std::shared_ptr<Panel> panel)`
Adds a panel to the manager.

#### `void removePanel(std::shared_ptr<Panel> panel)`
Removes a panel from the manager.

#### `std::shared_ptr<Panel> getPanel(size_t index)`
Gets a panel by index.
- **Returns:** Panel pointer or nullptr if index invalid

#### `size_t getPanelCount() const`
Gets the number of managed panels.

#### `void clearAllPanels()`
Clears content of all panels.

#### `void renderAll()`
Renders all panels to terminal in order.

#### `void initialize()`
Initializes terminal (clears screen, hides cursor).

#### `void cleanup()`
Restores terminal state (shows cursor, resets formatting).

#### `void movePanelToFront(std::shared_ptr<Panel> panel)`
Moves panel to render last (on top).

#### `void movePanelToBack(std::shared_ptr<Panel> panel)`
Moves panel to render first (behind others).

---

## ASCIIImage

Represents an ASCII art image.

### Constructors

#### `ASCIIImage()`
Creates an empty image.

#### `ASCIIImage(int width, int height)`
Creates an image with specified dimensions.

### Methods

#### `void loadFromRGB(const std::vector<unsigned char>& data, int width, int height)`
Loads image from RGB data.
- **Parameters:**
  - `data`: RGB pixel data (width × height × 3 bytes)
  - `width`: Image width
  - `height`: Image height

#### `void loadFromGrayscale(const std::vector<unsigned char>& data, int width, int height)`
Loads image from grayscale data.
- **Parameters:**
  - `data`: Grayscale pixel data (width × height bytes)
  - `width`: Image width
  - `height`: Image height

#### `void loadFromText(const std::vector<std::string>& lines)`
Loads image from text/ASCII art.
- **Parameters:**
  - `lines`: Vector of text lines

#### `void setPixel(int row, int col, char ch, Color color = Color::WHITE)`
Sets a pixel/character at position.

#### `char getChar(int row, int col) const`
Gets character at position.

#### `Color getColor(int row, int col) const`
Gets color at position.

#### `void resize(int newWidth, int newHeight)`
Resizes image using nearest neighbor sampling.

#### `void renderToPanel(Panel& panel, int row = 0, int col = 0) const`
Renders image to a panel at specified position.

#### `void clear()`
Clears image content.

#### Getters
- `int getWidth() const`: Get image width
- `int getHeight() const`: Get image height

---

## ASCIIVideo

Represents an ASCII video as a sequence of frames.

### Constructor

#### `ASCIIVideo()`
Creates an empty video.

### Methods

#### `void addFrame(std::shared_ptr<ASCIIImage> frame)`
Adds a frame to the video.

#### `void loadFromRGBSequence(const std::vector<std::vector<unsigned char>>& frames, int width, int height)`
Loads video from RGB frame sequence.

#### `void loadFromGrayscaleSequence(const std::vector<std::vector<unsigned char>>& frames, int width, int height)`
Loads video from grayscale frame sequence.

#### `std::shared_ptr<ASCIIImage> getFrame(size_t index)`
Gets a specific frame by index.

#### `std::shared_ptr<ASCIIImage> getCurrentFrame()`
Gets the current frame.

#### `void nextFrame()`
Advances to next frame (wraps around).

#### `void setFrame(size_t index)`
Sets current frame index.

#### `void setFrameRate(double fps)`
Sets frame rate for timing reference.

#### `void clear()`
Clears all frames.

#### `void renderToPanel(Panel& panel, int row = 0, int col = 0)`
Renders current frame to panel.

#### Getters
- `size_t getFrameCount() const`: Get total frame count
- `size_t getCurrentFrameIndex() const`: Get current frame index
- `double getFrameRate() const`: Get frame rate

---

## Platform Support

- **Linux/Unix**: Full support with ANSI escape codes
- **macOS**: Full support
- **Windows**: Requires Windows 10+ with ANSI support enabled or Windows Terminal

## Thread Safety

The framework is **not thread-safe**. If using multiple threads:
- Only render from one thread
- Synchronize panel updates with mutexes
- Consider double-buffering for complex updates
