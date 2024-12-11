#ifndef UTF_8_HPP
#define UTF_8_HPP

#include <stdexcept>
#include <string>

// Function to calculate the visual width of a UTF-8 string
inline size_t utf8_visual_width(const std::string &str) {
	size_t width = 0;
	for (size_t i = 0; i < str.size();) {
		unsigned char symbol = str[i];
		if ((symbol & 0x80) == 0) { // 1-byte character (ASCII)
			width += 1;
			i += 1;
		} else if ((symbol & 0xE0) == 0xC0) { // 2-byte character
			width += 1;
			i += 2;
		} else if ((symbol & 0xF0) == 0xE0) { // 3-byte character
			width += 1;
			i += 3;
		} else if ((symbol & 0xF8) == 0xF0) { // 4-byte character
			width += 2; // Wide character
			i += 4;
		} else {
			throw std::runtime_error("Invalid UTF-8 sequence");
		}
	}
	return width;
}

// Function to pad a UTF-8 string to a specific width
inline std::string pad_utf8(const std::string &str, size_t width) {
	size_t visual_width = utf8_visual_width(str);
	if (visual_width >= width) {
		return str;
	}

	// Add spaces to reach the desired width
	return str + std::string(width - visual_width, ' ');
}

#endif // UTF_8_HPP
