
// Robe for the banshee
//    -Ilyian, Oct 1995

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("robe");
  set_short("translucent gossamer robe");
  add_adj(({"translucent", "gossamer", "white"}));
  set_long ("This robe is incrediably thin, seeming like it "
           +"would be ripped even by touching it. It is made from "
           +"some sort of white gossamer silk, very valuable, "
           +"but it does not look like it would offer much "
           +"protection.\n");
  set_ac (1);
  set_at (A_ROBE);
  add_prop(OBJ_I_VALUE, 1154);
  add_prop(OBJ_I_VOLUME, 50);
  add_prop(OBJ_I_WEIGHT, 10);
}

