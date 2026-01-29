/*
 *  CLIFF_ROOMS + rocks4.c
 *  This room connects the cliff to
 *  the fishing village 
 *  It is also connected to a wading
 *  area to the north
 *  Here is where the unlucky fisherman lives
 * (see QUESTS doc for more information)
 *
 */
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include "defs.h"
inherit ROOM_TELL;

object fisherman;

void
reset_room()
{
    if (!objectp(fisherman))
    {
	fisherman = clone_object(SEA_CREATURES + "unlucky_fisherman");
	fisherman->move(this_object(), 1);
	fisherman->command("emote walks in.");
    }
}

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
      " make it slippery underfoot. The blue-green"+
      " Calian sea is to the north and every now"+
      " and then a large wave crashes over the path."+
      " To the northeast you see a gate-like cleft between"+
      " some large boulders.\n");

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


    add_item(({"cracks", "crevices", "erosion"}),
      "Erosion has created deep cracks in the face"+
      " of the cliff.\n");

    add_item(({"cliff", "vertical cliff", "south"}),
      "Extending around to the southwest stands"+
      " a tall granite cliff that is seamed with"+
      " cracks caused from erosion.\n");
    add_item(({"cleft", "northeast", "cleft in rocks",
	"boulders"}),
      "To the northeast there is a cleft between"+
      " some granite boulders through which you can"+
      " glimpse the south end of a small fishing"+
      " village. The cleft functions like a gate"+
      " allowing you to go northeast.\n");
    add_item(({"village", "fishing village"}),
      "Peering through the cleft in the rocks, you"+
      " can see a few small huts.\n");
    add_item(({"boats", "fishermen", "nets"}),
      "The sea provides the main source of"+
      " livelihood for some of the folk who live"+
      " nearby. You see them actively pursuing their"+
      " trade, casting nets from small boats and hauling"+
      " in catches of fish.\n");
    add_item(({"sea", "waves"}),
      "You gaze out over the waves to the north and"+
      " west. A bit further to the north you see"+
      " the line of piers extending along the"+
      " port of Gelan. Some distance from shore"+
      " there are fishermen casting nets from"+
      " small boats. The blue-green sea meets"+
      " the sky at the horizon to the west."+
      " Unfortunately the rough waves make it too rough"+
      " to enter here.\n");

    add_item(({"piers", "line of piers", "Gelan"}),
      "Some distance to the north brightly coloured ships pass"+
      " to and from the piers that extend out into the bay.\n");

    add_item("water",
      "Brackish puddles of water partially"+
      " cover the path.\n");



    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,0);


    add_exit(CLIFF_ROOM + "rocks3", "southwest", 0, 0);
    add_exit(BEACH + "cleft", "northeast", 0, 0);
    set_tell_time(150);
    add_tell("A wave crashes against the rocks and"+
      " splashes you.\n");
    add_tell("Your feet slip on the wet slimy rocks.\n");
    add_tell("You see a sea osprey dive into the"+
      " waves and emerge again carrying a huge silvery"+
      " fish in its talons.\n");
    add_tell("A fisherman casts his net from a rowboat"+
      " not far from shore.\n");
    reset_room();

}

void
hook_smelled(string str)
{
    write("There is an awful odour coming from the slimy substance."+
      " It seems to be worse toward the southwest.\n");
    return;
}

