/* dogchow.c:  Food for the Red Eye Inn.  */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("dog chow");
   add_name("dog");
   add_name("chow");
  add_name("bowl");
    set_pname("chows");
   set_adj("dog");
   set_short("bowl of dog chow");
   set_pshort("bowls of dog chow");
   set_long(break_string(
    "You look into the bowl and you wonder if this is chow for dogs " +
    "or chow made from dogs. \n", 75));
   add_prop(OBJ_I_VALUE, 0);
   set_amount(350);
   add_prop(OBJ_I_WEIGHT,350);
   add_prop(OBJ_I_VOLUME,300);
}

