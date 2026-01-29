/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 * Lilith Sept 2021 spell change centre to center, updated descend.
 * Lilith Mar 2022: updated south exit to not allow non-Union in anymore.
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#define SEE_EAST ({ HALL + "_e" })
#define SEE_WEST ({ HALL + "_w1", HALL+"_w2" })

public int stair;

public void make_stair(void);
public void remove_stair(void);


public string
east_view(void)
{
    object *obs = get_view(SEE_EAST);

    if (!sizeof(obs))
	return "";

    return " At the east end of the corridor is "+
	COMPOSITE_LIVE(obs) + ".";
}

public string
west_view(void)
{
    object *obs = get_view(SEE_WEST);

    if (!sizeof(obs))
	return "";

    return " At the west end of the corridor is "+
	COMPOSITE_LIVE(obs) + ".";
}


public int
exit_block(void)
{
	
    /* See if player is anything other than the desired people */
    if (!IS_MEMBER(TP))
    {
	write("Shadows and flame whorl before the doorway, blocking "+
           "you from going south.\n");
        say("A whorl of shadows and flame prevents "+ QTNAME(TP) +
           "from going south.\n");
	return 1;
    }

    /* Return 0 to allow the player to exit */
    return 0;
}

public void
union_room(void)
{
    set_short("center of mosaic");

    set_long("@@stair_desc@@ From the north, a solemn and "+
	"quiet feeling emanates, and across the hallway that "+
	"continues from east to west, a slight cold breeze can "+
	"be felt. Through the door to the south, a case full "+
        "of weapons can be seen.@@east_view@@@@west_view@@\n");

    add_item(({"floor","mosaic","ground","pattern","swirl"}),
	"The mosaic covering the floor is large and abstract, "+
	"no discernable pattern can be made out from it. It is "+
	"formed by hundreds of brightly coloured stones "+
	"perfectly placed against swirling veins of "+
	"of dark metals, making you feel slightly dizzy "+
	"just looking at it.\nIn the center of the mosaic "+
	"is the image of a black sphere, from which "+
	"a dark flame rises.\n");
    add_item(({"sphere","flame"}),
	"The mosaic on the floor bears the symbol of a dark sphere "+
	"from which rises a black flame. The artwork is sublime, "+
	"it almost seems as if the flame is flickering.\n");
    add_item(({"wall","walls","hall","hallway","corridor"}),
	"The walls of the corridor are pale limestone, broken "+
	"in numerous places by the rooms that extend "+
	"off from this central location.\n");
    add_item(({"hall","corridor","east","hallway"}),
	"The hallway stretches off to the east and end to the "+
	"west, running perfectly straight and wide."+
	"@@east_view@@@@west_view@@\n");
    add_item(({"roof","ceiling"}),
	"The ceiling overhead is made of the same dark granite "+
	"as the floor, but is simple and unadorned. It rises "+
	"slightly in the middle, forming a gentle arch that stretches "+
	"all the way down the corridor to the east.\n");

    add_cmd_item(({"breeze","wind","draft","air"}),"touch",
	"It seems to be blowing from west to east.\n");
    add_cmd_item(({"wall","walls","stone","limstone"}),"touch",
	"It is smooth and soft.\n");
    add_cmd_item(({"floor","ground"}),"touch",
	"It is hard, the patterns rising out from the floor slightly.\n");
    add_cmd_item(({"mosaic","ground","floor","stones"}),({"touch","feel"}),
	"The stones of the mosaic seem to emanate a strange "+
	"warmth, which the metals are cold and dark.\n");

    add_exit("post", "north");
    add_exit("arsenal", "south", exit_block);
    add_exit("hall_w2", "west");
    add_exit("hall_e", "east");
}

public int
touch(string str)
{
    if (!strlen(str) || !IS_TORNU(TP))
	return 0;

    if (!parse_command(str, ({}),
	"[the] 'sphere' / 'image' / 'flame' / 'fire' / 'mosaic' / 'center'"))
    {
	return NF(CAP(query_verb())+" what?\n");
    }

    write("You gently "+query_verb()+" the center of the mosaic, and "+
	"hear a soft rumble from the ground.\n");
    say(QCTNAME(TP)+" leans down and does something to the mosaic, "+
	"and you hear a soft rumble from the ground.\n");

    set_alarm(2.0, 0.0, make_stair);
    return 1;
}

public string
stair_desc(void)
{
    if (!stair)
    {
	return "Spread out in the center of the floor is a many "+
	    "coloured mosaic formed from swirling patterns of bright "+
	    "stones and dark metals.";
    }
    return "The center of the floor is open wide, leading down to a "+
	"darkened stairwell. A cold and ominous wind blows up from below.";
}

public void
make_stair(void)
{
    if (stair)
	return;

    stair = 1;
    add_item(({"stair","stairs","stairwell"}),
	"The stairs are worn smooth over the aeons, and lead down into "+
	"almost tangible shadows.\n");
    add_exit("stairwel", "down", "@@descend@@");

    tell_room(TO, "The mosaic swirls in upon itself, and suddenly "+
	"drops down into the floor, opening up into a circular "+
	"stairwell leading down into the shadows.\n");

    set_alarm(5.0, 0.0, remove_stair);
}

public void
remove_stair(void)
{
    if (!stair)
	return;

    stair = 0;
    remove_exit("down");

    remove_item("stair");
    remove_item("stairs");
    remove_item("stairwell");

    tell_room(TO, "The stairwell quickly rises up and "+
	"forms into solid floor again.\n");
}

public mixed
descend(void)
{
    if (!IS_TORNU(TP) && !FRIEND(TP))
    {
	write("As you place your foot on the first step, the "+
	    "ground begins to vibrate slightly.\n");
	set_alarm(0.0, 0.0, remove_stair);
	return 1;
    }

    write("You descend the stair, and become swaddled in shadows.\n");
    return 0;
	
	
}

public void
init(void)
{
    ::init();
    add_action(touch, "touch");
    add_action(touch, "press");
    add_action(touch,  "push");
}

