/* Grid rows
 * 
 * Options
 * -------
 * 10: 10 rows
 * 11: 11 rows
 */
#define GRID_ROWS 11

/* Grid cols
 * 
 * Options
 * ------- 
 * 11: 11 cols
 */
#define GRID_COLS 11

/* Postition of first LED  
 *   
 * Options
 * -------
 * 0: top-left
 * 1: top-right
 * 2: buttom-left
 * 3: buttom-right
 */
#define GRID_FIRST 2

/* Grid language
 *  
 * Options
 * -------
 * 1: de_DE:     german
 * 2: de_DE_alt: german alternative
 * 3: de_DE_s: "Es ist" only at full and half hour
 * 4: de_DE_s1: "Es ist" only at full and half hour + Minutes in Last row (new Grid De_de_S1)
 */
#define GRID_LANGUAGE de_DE

/* Position of single minute LEDs
 *  
 * Options
 * -------
 * 0: before
 * 1: after
 */
#define GRID_SINGLE_MINUTES 1

/* Data PIN, where the LED strip is connected to */
#define DATA_PIN D4
#define FASTLED_INTERNAL
