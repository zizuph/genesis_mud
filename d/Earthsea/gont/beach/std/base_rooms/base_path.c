/*
 * Gont Beach to Ten Alders path
 *
 * To be inherited by path rooms
 *
 * Ckrik Nov 1997.
 * This file is called by the path rooms and contains 
 * terrain related information.
 * 
 */

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
inherit HERB;

void
create_path();

void
create_earthsea_room()
{    
    ::create_herb_room();
    set_short("A path");
    set_long("The path continues. Trees tower " +
      "over you creating shady forests on both sides of " +
      "the path. Dense bushes prevent you from entering " +
      "the forest. To the north, a forested mountain " +
      "rises to the clouds. There seem to be signs of "+
      "activity in the mountains. Looking down south on " +
      "the path, you see a white sandy beach. ");

    add_item((({"forest", "trees", "tree", 
	  "forests"})),
      "The forest surrounds you.\n");
    add_item((({"south", "sea", "beach", "white sandy beach",
	  "sandy beach"})),
      "From this vantage point you view at a distance the vast "+
      "sea and the white beach far below.\n");
    add_item((({"pine needles", "needles", "path", "rugged path",
	  "tangled undergrowth", "undergrowth", "rocks"})),
      "Dense forest undergrowth prevents your leaving the rugged "+
      "path. Pine needles crunch under your feet as you walk.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(TO->select_herb_files(FOREST_HERBS),
      FOREST_LOCATIONS, 3);
    create_path();

}

create_path()
{}




