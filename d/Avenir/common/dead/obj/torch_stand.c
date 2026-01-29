// file name:  /d/Avenir/common/dead/obj/torch_stand.c
// creator(s): Lilith, Sept 2014
// last update: Aug 2021 updated desc for area opening.
//             Liloith Sep 2021: fixed weight/volume to hold torch
// purpose:   Cloned to the dead/mascarvin/spots.c quest room 
// note:     
// bug(s):
// to-do: 

inherit "/std/container";
#include <stdproperties.h>

void 
create_container()
{
    set_name("block");
    add_name(({"brazier", "sconce", "torch stand", "stone", "stand", "cylinder"}));
    set_adj(({"stone", "granite", "cylindrical", "white"}));
    set_short("stone torch stand");
    set_long("A cylindrical block of white granite about knee high, "
      +"covered in soot. There is a hole in the "
      +"center that seems to be made to hold "
      +"a torch or similar light source. Around it "
      +"on the floor in simple patterns are many pale dots.\n");
    add_item(({"hole", "center" }), "It is a hole drilled about "
      +"a handspan deep. It appears to be the "
      +"right size to hold a torch.\n");
    add_item(({"soot" }), "The soot appears to have been left "
      +"by torches.\n");
    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET, "It is far too heavy, even for you.\n");
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000 + 2500);
    add_prop(CONT_I_MAX_WEIGHT, 10000 + 2500);
    add_prop(OBJ_I_VALUE, 100);
}
