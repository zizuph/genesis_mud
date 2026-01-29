/*
 *  CLIFF_ROOMS + rocks3.c
 *  This path connects the cliff to
 *  the fishing village 
 *
 */
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include "defs.h"
inherit ROOM_TELL;


void
create_room()
{

    set_short("A rocky path");
    set_long("You are standing on a narrow path"+
      " that closely follows along the base of a"+
      " tall granite cliff. The path is rough with"+
      " granite rocks that have fallen down from"+
      " above and is partially submerged in water."+
      " Seaweed and some sort of black slimy substance"+
      " make it slippery underfoot. The path extends"+
      " to the northeast and southwest along the cliff.\n");

    add_item(({"path", "rocky path"}),
      "A rocky path follows along the base of"+
      " a tall granite cliff that extends along"+
      " the southwest.\n");
    add_item(({"rocks", "stones"}),
      "Rough granite rocks have fallen down from"+
      " the cliff and are strewn all over the path.\n");
    add_item("seaweed", "Some dark seaweed"+
      " has been cast upon the rocks by the action"+
      " of the waves.\n");
    add_item(({"substance", "slimy substance",
	"black slimy substance"}),
      "You wonder what this substance can be--It"+
      " is slippery and has a foul smell.\n");
    add_item(({"huts", "village"}),
      "Some poor huts are grouped together"+
      " to form a small village. You will need"+
      " to get closer to get a better look"+
      " at them.\n");


    add_item("boulders", "This is an outcrop of"+
      " granite boulders that are heaped at the base"+
      " of a cliff that extends to the southwest.\n");
    add_item(({"cracks", "crevices", "erosion"}),
      "Erosion has created deep cracks in the face"+
      " of the cliff.\n");
    add_item(({"cliff", "vertical cliff", "south"}),
      "Extending around to the southwest stands"+
      " a tall granite cliff that is seamed with"+
      " cracks caused from erosion.\n");
    add_item(({"boats", "fishermen", "nets"}),
      "The sea provides the main source of"+
      " livelihood for some of the folk who live"+
      " nearby. You see them actively pursuing their"+
      " trade, casting nets from small boats and hauling"+
      " in catches of fish.\n");
    add_item(({"sea", "waves"}),
      "You gaze out over the waves to the north and"+
      " west. A bit further to the north you can see"+
      " the line of piers extending along the"+
      " port of Gelan. Some distance from shore"+
      " there are fishermen casting nets from"+
      " small boats. You feel it would be unwise"+
      " to swim here due to the rough waves crashing on the"+
      " rocks.\n");
    add_item("water",
      "Brackish puddles of water partially"+
      " cover the path.\n");




    add_exit(CLIFF_ROOM + "rocks4", "northeast", 0, 0);
    add_exit(CLIFF_ROOM + "rocks2", "southwest", 0, 0);
    set_tell_time(150);
    add_tell("A wave crashes against the rocks and"+
      " splashes you.\n");
    add_tell("You feet slip on the wet slimy rocks.\n");
    add_tell("You see a sea osprey dive into the"+
      " waves and emerge again carrying a huge silvery"+
      " fish in its talons.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);



}
public void
hook_smelled(string str)
{
    write("There is an awful odour coming from the slimy substance."+
      " It seems to be worse toward the southwest.\n");
    return;
}


