#ifndef WORDCLOCK_GUI_H
#define WORDCLOCK_GUI_H

class Gui {
  static String pad(int value);
  static String htmlOption(const String& label, const String& value, const String& store);
  static String createStyleSheet();
  static String createNav();
  static String createScript();
  static String createContent();
  static String createFooter();

  public:
    static String index();
};
#endif
