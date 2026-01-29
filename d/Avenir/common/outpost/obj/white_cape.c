// white cape for the snob_elf in tomato-drop quest.
// made by Kazz, March 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("cape");
  set_short("white spotless cape");
  add_adj(({"white", "spotless"}));
  set_long ("White cape made of bleached leather.\n" +
            "It is made to draw people's attention.\n");
  set_ac (10);
  set_at (A_ROBE);
  add_prop (OBJ_I_WEIGHT, 3000);
  add_prop (OBJ_I_VOLUME, 2000);
}
