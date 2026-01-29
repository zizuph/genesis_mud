/*
 *  CLIFF_ROOMS + rocks2.c
 *  This path connects the cliff to
 *  the fishing village 
 *  An entrance through a culvert
 *  leads to the undewater kroug
 *  caves.
 *
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
inherit ROOM_TELL;

object fish;

int enter_cave(string str);

void
reset_room()
{
    if (!objectp(fish))
    {
	fish = clone_object(SEA_OBJECTS + "rotten_fish");
	fish->move(this_object(), 1);
	tell_room(this_object(), "A dead fish washes up on shore.\n",
	  ({}));
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
      " make it slippery underfoot. The path extends"+
      " to the northeast and southwest along the cliff,"+
      " skirting a stone embankment.\n");

    add_item(({"stone embankment", "embankment"}),
      "It is hard to tell whether the embankment is"+
      " natural or fabricated. It is little more than"+
      " a loosely-constructed heap of stones against"+
      " the foot of the cliff. Toward the bottom of the embankment"+
      " you spot a hole that is partially camouflaged"+
      " by rocks and dead seaweed.\n");
    add_item(({"hole", "entrance", "cave entrance"}),
      "A dark, partially camouflaged hole lies"+
      " at the base of the embankment."+
      " Some nasty black substance like slime"+
      " or sewage is oozing slowly from it,"+
      " dripping onto the path and into the"+
      " sea. Entering may be unpleasant since you"+
      " will need to get down on all fours and crawl"+
      " through the opening.\n");
    add_item(({"path", "rocky path"}),
      "A rocky path follows along the base of"+
      " a tall granite cliff that extends along"+
      " the southwest.\n");
    add_item(({"rocks", "stones"}),
      "Rough granite rocks have fallen down from"+
      " the cliff and are strewn all over the path.\n");
    add_item(({"seaweed", "dead seaweed"}),
      "Some dead seaweed is strewn over the rocks."+
      " Apparently it has been cast up by the action of"+
      " the waves. It is coated with a black slimy substance.\n");
    add_item(({"substance", "slimy substance",
	"black slimy substance", "slime"}),
      "You wonder what this substance can be--It"+
      " is slippery and has a foul smell.\n");
    add_item(({"huts", "village"}),
      "To the northeast you see"+
      "some huts grouped together"+
      " to form a village. You will need"+
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
    add_item(({"sea", "waves"}),
      "You gaze out over the waves to the north and"+
      " west. A bit further to the north you can see"+
      " the line of piers extending along the"+
      " port of Gelan. Some distance from shore"+
      " there are fishermen casting nets from"+
      " the sky at the horizon to the west."+
      " You feel it would be unwise to swim north, however,"+
      " due to the rough waves crashing on the rocks.\n");
    add_item("water",
      "Brackish puddles of water partially"+
      " cover the path.\n");
    add_item(({"boats", "fishermen", "nets"}),
      "The sea provides the main source of"+
      " livelihood for some of the folk who live"+
      " nearby. You see them actively pursuing their"+
      " trade, casting nets from small boats and hauling"+
      " in catches of fish.\n");


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_exit(CLIFF_ROOM + "rocks3", "northeast", 0, 0);
    add_exit(CLIFF_ROOM + "rocks1", "southwest", 0, 0);

    reset_room();

    set_tell_time(150);
    add_tell("Waves crash against the rocks.\n");
    add_tell("Dead seaweed floats on a slime slick nearby.\n");
    add_tell("Some distance out from shore you see"+
      " a fisherman cast his net from a rowboat.\n");
    add_tell("Black slime seeps out into the sea.\n");
    add_tell("A large sea osprey dives into the"+
      " waves and emerges again carrying a huge silvery"+
      " fish in its talons.\n");

}

public void
hook_smelled(string str)
{

    write("There is an awful odour coming from the slimy substance."+
      " The stench nearly knocks you over.\n");
    return;
}

void
init()
{
    ::init();
    add_action(&enter_cave(), "crawl");
}


int
enter_cave(string rest_cmd)
{

    object tp = this_player();

    if (!rest_cmd)
    {
	notify_fail("Crawl where?\n");
	return 0;
    }

    if (!parse_command(rest_cmd, this_object(), " 'through' [the]"+
	" 'hole' / 'opening' "))
    {
	notify_fail("Crawl where?\n");
	return 0;
    }

    write("You get down on all fours and crawl"+
      " through the hole.\n");
    say(QCTNAME(tp) + " crawls through a dark"+
      " hole in the embankment.\n");
    tp->move_living("M", CAVE_LEV1 + "entrance", 1, 0);
    say(QCTNAME(tp) + " crawls in.\n");
    return 1;
}
