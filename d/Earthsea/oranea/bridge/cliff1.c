/*
*  coded by Amelia 8/2/97
*
*/

inherit "/d/Earthsea/std/room";

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include <ss_types.h>
inherit ROOM_TELL;


int enter_waterfall(string str);

void
create_earthsea_room()
{
    set_short("Limestone ledge");
    set_long(break_string("The narrow ledge beneath your feet "+
	"looks out over a waterfall, where "+
	"a torrent of water rushes down the mountainside to plunge "+
	"into a maelstrom far below. The ledge is situated on a "+
	"tall limestone cliff that extends upward and downward "+
	"almost vertically. White mist seems to emanate "+
	"from the water, surrounding a swaying rope bridge that extends "+
	"out into it to the south. Like a veil the mist shrouds the view "+
	"in that direction and does not permit you to view what lies on "+
	"the farther side.\n",
	70));

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_item((({"cliff", "ledge", "perch"})),
      "You are standing on a narrow ledge of solid limestone.\n");
    add_cmd_item("cliff", "climb", "The cliff is almost vertical, "+
      "and it is impossible to climb.\n");
    add_cmd_item("maelstrom", ({"dive", "dive in"}), "To dive in "+
      "there would mean your certain death.\n");

    add_item((({"bridge", "rope bridge", "swaying rope bridge"})),
      "The bridge looks as though it were hurriedly constructed "+
      "from long woven strands of rope. It sways with every breeze.\n");
    add_item("maelstrom",
      "Far below you see the torrent from the waterfall plunging into "+
      "a vast swirling whirlpool. As you look down into it, you "+
      "feel mesmerized ... It calls you to dive into it.\n");
    add_item((({"mist", "white mist"})),
      "A dense cloud of white mist seems to emanate from the waterfall, "+
      "making it difficult to view the surroundings or what lies ahead.\n");
    add_item("rainbow",
      "All the colours of the spectrum radiate from rainbows that arc "+
      "through the shifting mists.\n");
    add_item((({"waterfall", "water"})),
      "A curtain of water plunges down the mountainside in the "+
      "form of a waterfall which begins way above and ends far below "+
      "where the waters meet in a swirling maelstrom. As you "+
      "gaze at the waterfall, you have the feeling it is special, "+
      "like the portal between two worlds.\n");
    add_item("mountainside",
      "The mountain extends up into the clouds, and you cannot see the "+
      "top from here.\n");
    add_item((({"rift", "chasm"})),
      "The ledge ends overlooking a vast rift, where you see water "+
      "far below swirling in a maelstrom.\n");
    add_item((({"limestone", "solid limestone"})),
      "Though pitted and cracked, the limestone is solid rock.\n");

    set_tell_time(150);
    add_tell("The roaring sound of water hurts your ears.\n");
    add_tell("You are surrounded by a cloud of mist.\n");
    add_tell("You see a rainbow arc through the mist.\n");

    reset_room();

    add_exit(BRIDGE + "bridge5", "south", 0, 2, 0);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
	start_room_tells();
    }
}

int
enter_waterfall(string str)
{

    object tp = this_player();

    notify_fail("Enter what/where?\n");
    if (!str)
	return 0;

    if (str == "waterfall")
    {
	tp->catch_msg("You enter behind the curtain of the waterfall, "+
	  "and experience a strange sensation.\n");
	tell_room(this_object(), QCTNAME(tp) + " enters behind the "+
	  "curtain of the waterfall, disappearing from view.\n", ({tp}));
	tp->move_living("M", "/d/Earthsea/oranea/bridge/cave", 1);
	tell_room(environment(tp), QCTNAME(tp) + " enters from the "+
	  "waterfall.\n", ({tp}));
	return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(&enter_waterfall(), "enter");
}
