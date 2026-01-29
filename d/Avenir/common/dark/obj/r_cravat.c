// Scarlet cravat, equipment of ~Avenir/common/dark/rogue
// made by Boriska, Feb 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("cravat");
  set_short("fancy scarlet cravat");
  add_adj(({"fancy", "scarlet"}));
  set_long ("This expesive and fancy looking cravat is made of finest\n" +
	    "silk. It gleams softly, attracting much attention to you.\n");
  set_ac (5);
  set_at (A_NECK);
  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME, 100);
  add_prop(OBJ_I_VALUE, 200);
}
