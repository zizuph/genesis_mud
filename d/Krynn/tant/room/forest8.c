/* Forest near Tantallon
 * By Teth, Jan 17 1996
 */

#include <macros.h>
#include "local.h"
inherit FORESTBASE;

public void
create_forest()
{
    add_my_desc("A small waterfall runs down a hillside into the forest, " +
        "but the water then quickly disappears underground. The thickness " +
        "of the forest and the surrounding hills prevent movement in many " +
        "directions, all except the northwest.\n");
    AI(({"small waterfall","waterfall"}),"The small waterfall brings fresh " +
        "clean water down into the area, although the water quickly " +
        "disappears.\n");
    AI("water","The water looks drinkable. It is enjoyed by many forest " +
        "creatures.\n");
    AI(({"hillside","hills","surrounding hills"}),"The hills surround " +
        "this little patch of forest.\n");

    AE(TROOM + "road9", "northwest", 0, 2, 1);

    reset_tant_room();
}

void
init()
{
    ADA("drink");
    ::init();
}
 
int
drink(string str)
{
    if (str == "from water" || str == "water" || str == "from waterfall")
      {
          if (TP->drink_soft(TP->drink_max() / 16,0))
            {
                say(QCTNAME(TP) + " drinks some water.\n");
                write("You drink some cold water and feel very " + 
                    "refreshed.\n");
            }
          else
            write("You are not thirsty at the moment.\n");
          return 1;
      }
    return 0;
}
 
