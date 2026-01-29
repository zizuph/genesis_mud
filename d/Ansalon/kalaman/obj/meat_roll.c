inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("roll");
    set_adj("meat");
    add_adj("huge");
    set_short("huge meat roll");
    set_long("The roll you are looking at must easily be twice the size of your " +
      "open hand, and is easily a hand high, filled with thich chunks of beef " +
      "dripping gravy! Mmmmm....\n");
    set_amount(200);
}
