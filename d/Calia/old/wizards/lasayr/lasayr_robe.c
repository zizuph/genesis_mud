/* Created by Lasayr 9/9/98 */
/* lasayr_robe.c            */
/* Comments:                */
/* ToDo:                    */


inherit "/std/armour.c";

inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Calia/domain.h"


void
create_armour()
{

  set_name("robe");
  set_adj(({"lengthy","shimmering"}));
  set_short("lengthy shimmering robe");
  set_long("A scintillating sheen of colors " +
  "reflect on the surface of the myriad of " +
  "woven cloth. Crafted as though the very " +
  "elements were used to bind it, you can " +
  "almost make out shards of gem, whispers " +
  "of wind, marks of flame, and mirrors of " +
  "water. Each bleeding into the other to " +
  "show no change. Your eyes catch only the " +
  "completeness. The length of the robe " +
  "would seem a little large on any stature " +
  "of person.\n");
  
  add_item(({"colors", "cloth", "surface", "elements"}),
  "The Creator could not have done a more perfect " +
  "reflection in the making.  Showing the relation " +
  "of the elements in the subtleness of them. Much " +
  "as the seasons come upon time, a change but the " +
  "same.\n\n"); 
  
  add_item(({"shards of gem", "shards", "gem"}),
  "Shards of shattered gems lay writhing within the " +
  "folds of the robe. Pulsing to some beat, they " +
  "shine with almost ethereal life.\n\n");

  add_item(({"whispers of wind", "whispers", "wind"}),
  "Motes of playful wind gather within the folds of " +
  "the robe. Swaying to the unknown, they breathe " +
  "with visible life.\n\n");
  
  add_item(({"marks of flame", "marks", "flame"}),
  "Flickers of bright flame hold within the folds of " +
  "the robe. Dancing to a vague tune, they cast " +
  "shadows to life.\n\n");

  add_item(({"mirrors of water", "mirrors", "water"}),
  "Streams of shining water run deep within the " +
  "folds of the robe. Shifting to ebb and tide, " +
  "they crash effortlessly and struggle for life.\n\n");

  set_at(A_ROBE|A_ARMS);
  set_ac(5);
    
  set_keep(1);
  
  add_prop(OBJ_M_NO_BUY, "An item such as this could never be sold.");
  add_prop(MAGIC_AM_MAGIC, ({5, "enchantment"}));

}
