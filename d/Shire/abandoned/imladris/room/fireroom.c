#include <stdproperties.h>
#include "defs.h"
#include "/d/Shire/imladris/guild/council/cdefs.h"

create_rivendell_room()
{
    set_short("Hall of Fire");

    set_long(
	"You are looking into a large room which is called the Hall of Fire. "+
	"Not so strange name though, because on the opposite side of this "+
	"many-pillared room stands a huge fire-place and chairs in "+
	"front of the fire. Here in the south however, you can see "+
	"out the windows in the west towards the porch and the bridge "+
	"outside the garden. There is a poster on the eastern wall. "
    );

    add_exit(IML_DIR + "fireplace", "north");
    add_exit(IML_DIR + "passage1",  "south");
    add_exit(IML_DIR + "guild/council/council", "council", "@@chk_enter");

    add_item( ({ "hall","room","pillars" }),
	"Many pillars stands here on both sides of the room, but why "+
	"this is so remains a puzzle.\n");
    add_item( ({ "fire","fireplace","chairs" }),
	"Alas! It is not here. You must walk over the room (north) to "+
	"examine it more closely.\n" );
    add_item( ({ "roof","ceiling" }),
	"The roof is of dark wood, probably oak, though due to a lot "+
	"of smoke from the fire-place, it has darkened and prevails no "+
	"extra information.\n" );

    add_item( ({ "window", "windows" }),
	"Looking through the window, you realize that you are gazing "+
	"westwards toward the lowlands. @@day_desc@@. The valley of Imladris "+
	"continues in this direction, and far to the west you know "+
	"there is the Shire and Bree, as this is 'The Last Friendly House'.\n");
    add_item( ({ "porch", "bridge", "garden" }),
	"Looking through the window, you see the garden outside the " +
	"porch of Elrond's House. @@day_desc@@, and even further west " +
	"you see a bridge crossing over what must be a river.\n");

	add_item("poster", "The poster has some words written on it.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  1);

}

void
init()
{
	::init();
	add_action("do_read", "read");
	add_action("do_apply", "apply");
}

int
do_read(string str)
{
	if (str != "poster")
	{
		NF("Read what?\n");
		return 0;
	}

	write(
	"As you read the poster you understand that you are able to\n"+
	"'apply for council' here. That can be done when there are free\n"+
	"space in the council.\n");
	return 1;
}

int
do_apply(string str)
{
	NF("Apply for what?\n");

	if (!str)
	return 0;

	str = lower_case(str);

	if (str != "council" && str != "for council" )
	return 0;

	/* Check if council is full. */
	if (COUNCIL->query_council_full())
	{
		write("The council is currently full. When a free space occurs, or a new\n"+
			  "council member is being elected, a note will be put up on the board.\n");
		return 1;
	}

	/* Apply for membership in the council. */
	COUNCIL->apply_for_council(TP->query_real_name());
	write("Your application has been logged. We urge you to be patient as\n"+
		  "enough members of the council has to vote on your membership.\n");
	return 1;
}

int
chk_enter()
{
	seteuid(getuid());
	if(COUNCIL->is_imladris_council(TP->query_real_name()) || 
		("/secure/master"->query_wiz_dom(TP->query_real_name())=="Shire" &&
		(TP->query_real_name()=="Odin" ||
		 TP->query_real_name()=="Rogon" ||
		 TP->query_real_name()=="Dunstable")))
	{
		write("You walk into the council room with your head lifted.\n");
		if(TP->short())
		say(QCTNAME(TP)+" walks into the council room with lifted head.\n");
		return 0;
	}
	write("You are not allowed to enter there!\n");
	return 1;
}

#define EARLY_NIGHT	22..24
#define LATE_NIGHT      0..3
#define EARLY_MORNING   4..7
#define MORNING         8..10
#define NOON            11..13
#define AFTERNOON       14..17
#define EVENING         18..21


string
day_desc()
{
    switch(qhour())
    {
	case EARLY_NIGHT :
	    return "It is early night outside";
	case LATE_NIGHT :
	    return "It is late night outside";
	case EARLY_MORNING :
	    return "It is early morning outside";
	case MORNING:
	    return "It is in the morning";
	case NOON:
	    return "It is at noon outside";
	case AFTERNOON:
	    return "It is afternoon outside";
	case EVENING:
	    return "It is evening outside";
    }
}
