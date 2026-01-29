/*
 * 
 * 
*  coded by Amelia 6/1/97
 */

inherit "/d/Earthsea/std/room";
#pragma no_clone
#pragma strict_types

#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
inherit BASE_HERB_ROOM;
#include FOREST_HERB_SET





void
create_earthsea_room()
{

    set_short("Trail through the forest");
    set_long(BS("This seems to be a fairly new trail, judging "+
	"from the condition of the trees that were cut "+
	"down to form it. Branches lying around in disorder are "+
	"still green, and it looks as tho cut down in haste.\n", 70));

    add_item((({"branches", "trail"})),
      "The narrow trail goes west/east through the forest "+
      "and as you look at the green branches cast carelessly "+
      "to the side, it appears to have been made recently "+
      "in a hurry.\n");

    add_item((({"forest", "trees"})),
      "Tall pine and larch trees from the evergreen "+
      "forest surround you.\n");

    set_tell_time(90);
    add_tell("A cloud of pine smoke comes from the west.\n");
    add_tell("You have the feeling you are being watched.\n");
    add_exit(CAMP2 + "camp_path_1", "west");
    add_exit(SOUTH_PATH + "trails2", "east");


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);

    set_up_herbs(TO->select_herb_files(FOREST_HERBS),
      FOREST_LOCATIONS, 3);


}

