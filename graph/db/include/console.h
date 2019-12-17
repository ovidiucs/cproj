
 /**
 *  @dir include
 *  @brief include directory for header files
 *
 */
 /**
 *
 *  @file console.h
 *  @brief Function prototypes for the console driver.
 *
 *  This contains the prototypes for the console
 *  driver and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Ovidiu Constantinescu (ovidiucs)
 */

     #ifndef _MY_CONSOLE_H
    #define _MY_CONSOLE_H

    #include <video_defines.h>

    /** @brief Prints character ch at the current location
     *         of the cursor.
     *
     *  If the character is a newline (`\n`), the cursor should
     *  be moved to the next line (scrolling if necessary).  If
     *  the character is a carriage return (`\r`), the cursor
     *  should be immediately reset to the beginning of the current
     *  line, causing any future output to overwrite any existing
     *  output on the line.  If backsapce (`\b`) is encountered,
     *  the previous character should be erased (write a space
     *  over it and move the cursor back one column).  It is up
     *  to you how you want to handle a backspace occurring at the
     *  beginning of a line.
     *
     *  @param ch the character to print
     *  @return The input character
     */
    int putbyte( char ch );

    /** @brief Prints the string s, starting at the current
     *         location of the cursor.
     *
     *  If the string is longer than the current line, the
     *  string should fill up the current line and then
     *  continue on the next line. If the string exceeds
     *  available space on the entire console, the screen
     *  should scroll up one line, and then the string should
     *  continue on the new line.  If `\n`, `\r`, and `\b` are
     *  encountered within the string, they should be handled
     *  as per putbyte. If len is not a positive integer or s
     *  is null, the function has no effect.
     *
     *  @param s The string to be printed.
     *  @param len The length of the string s.
     *  @return Void.
     */
    void putbytes(const char* s, int len);

    /** @brief Changes the foreground and background color
     *         of future characters printed on the console.
     *
     *  If the color code is invalid, the function has no effect.
     *
     *  @param color The new color code.
     *  @return Void.
     */
    void set_term_color(int color);

    /** @brief Writes the current foreground and background
     *         color of characters printed on the console
     *         into the argument color.
     *  @param color The address to which the current color
     *         information will be written.
     *  @return Void.
     */
    void get_term_color(int* color);

    /** @brief Sets the position of the cursor to the
     *         position (row, col).
     *
     *  Subsequent calls to putbytes should cause the console
     *  output to begin at the new position. If the cursor is
     *  currently hidden, a call to set_cursor() must not show
     *  the cursor.
     *
     *  @param row The new row for the cursor.
     *  @param col The new column for the cursor.
     *  @return Void.
     */
    void set_cursor(int row, int col);

    /** @brief Writes the current position of the cursor
     *         into the arguments row and col.
     *  @param row The address to which the current cursor
     *         row will be written.
     *  @param col The address to which the current cursor
     *         column will be written.
     *  @return Void.
     */
    void get_cursor(int* row, int* col);

    /** @brief Hides the cursor.
     *
     *  Subsequent calls to putbytes must not cause the
     *  cursor to show again.
     *
     *  @return Void.
     */
    void hide_cursor();

    /** @brief Shows the cursor.
     *
     *  If the cursor is already shown, the function has no effect.
     *
     *  @return Void.
     */
    void show_cursor();

    /** @brief Clears the entire console.
     *  @return Void.
     */
    void clear_console();

    /** @brief Prints character ch with the specified color
     *         at position (row, col).
     *
     *  If any argument is invalid, the function has no effect.
     *
     *  @param row The row in which to display the character.
     *  @param col The column in which to display the character.
     *  @param ch The character to display.
     *  @param color The color to use to display the character.
     *  @return Void.
     */
    void draw_char(int row, int col, int ch, int color);

    /** @brief Returns the character displayed at position (row, col).
     *  @param row Row of the character.
     *  @param col Column of the character.
     *  @return The character at (row, col).
     */
    char get_char(int row, int col);

    #endif /* _MY_CONSOLE_H */

