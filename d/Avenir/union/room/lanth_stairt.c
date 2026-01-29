/*
 *  Union lanthorn room stair, top of stairs
 *  Created by Lilith in July, 2004
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>
#include <stdproperties.h>


public int
do_down(void)
{
    write("You sit in the flue and push off with your arms, sending yourself "+
	"sliding down into the darkness\n");
    say(QCTNAME(TP) +" sits in the flue and slides down into the darkness.\n");
    TP->move_living("M", ROOM + "lanth_flue", 1);
    return 0;
}

public void
union_room(void)
{
    set_short("stairwell");
    set_long("At your feet is a flue of sorts that spirals downwards "+
	"into complete darkness. Silence and passion pulse from below, "+
	"a siren's song audible only to your ears. The space around "+
	"you is so large that even a thousand burning torches would "+
	"not reveal its dimensions. There is a faint bluish glow to "+
	"the west.\n");

    add_item(({"flue", "spiral"}),
	"It is a flue or channel made of the same dark stone as the "+
	"rest of this place. It appears to be glossy and smooth, and "+
	"it spirals downward into a black abyss.\n");
    add_item(({"down", "darkness", "space"}),
	"As you look down into the abyss, you sense that the abyss also "+
	"looks back into you.\n");

    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_S_DARK_LONG, "You are enveloped by a darkness whose "+
      "silence seems to hum in your ears. By the way the sounds of "+
      "your footsteps have carried, you surmise that you are in a "+
      "very large space. There is a faint bluish glow to the west.\n");

    add_exit("lanthorn_room", "west");
    add_exit("lanth_flue", "down", do_down, 0, 1);
}

public int
do_slide(string str)
{
    NF(CAP(query_verb()) + " what / where?\n");
    if(!strlen(str))
	return 0;

    if (!parse_command(str, ({}), "[in] / [into] / [down] "+
	    "[the] 'flue' / 'slide' / 'darkness' / 'abyss'"))
	return 0;

    do_down();
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(do_slide,  "slide");
    add_action(do_slide,  "enter");
}

public int
query_prevent_snoop(void)
{
    return 1;
}
