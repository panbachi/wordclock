#ifndef WORDCLOCK_COLOR_H
#define WORDCLOCK_COLOR_H
class Color {
  public:
    static color_t hexToRgb(String value) {
      value.replace("#", "");
      int number = (int) strtol( value.c_str(), NULL, 16);
      
      // Split them up into r, g, b values
      int r = number >> 16;
      int g = number >> 8 & 0xFF;
      int b = number & 0xFF;
      
      color_t rgb;
      rgb.r = r;
      rgb.g = g;
      rgb.b = b;
    
      return rgb;
    }
    
    static String&& rgbToHex(const color_t& hex) {
      long hexColor = ((long)hex.r << 16L) | ((long)hex.g << 8L) | (long)hex.b;
    
      String out = String(hexColor, HEX);
    
      while(out.length() < 6) {
        out = "0" + out;
      }
    
      return std::move(out);
    }

};
#endif
