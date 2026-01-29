// Dusty cape, equipment of ~Avenir/common/dark/rogue
// made by Boriska, Feb 1995

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("cape");
  set_short("black dusty cape");
  add_adj(({"dusty", "black"}));
  set_long ("Black cape made of leather and canvas stripes.\n" +
	    "It is covered with dust and stains of unknown liquid.\n");
  set_ac (10);
  set_at (A_ROBE);
  add_prop (OBJ_I_WEIGHT, 3000);
  add_prop (OBJ_I_VOLUME, 2000);
}
