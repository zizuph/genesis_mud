#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <macros.h>

#include "defs.h"

create_rivendell_room()
{
    set_short("Fireplace");

    set_long(
	"You are standing by the fireside in the Hall of Fire.\n"+
	"This is a cosy place in front of an ever-burning fireplace. "+
	"Chairs stand in front of it, and you could relax here "+
	"pondering upon the strangeness of the world. "+
	"@@desc_chairs@@"
    );

    add_exit(IML_DIR + "fireroom", "south");

    add_item( ({ "hall","room","pillars" }),
	"Many pillars stands here on both sides of the room, but why "+
	"this is so remains a puzzle.\n");
    add_item( ({ "fire","fireplace" }),
	"The ever warm fire brings light and warmth into this room.\n");
    add_item( ({ "roof","ceiling" }),
	"The roof is of dark wood, probably oak, though due to a lot "+
	"of smoke from the fire-place, it has darkened and prevails no "+
	"extra information.\n" );

    add_item( ({ "window", "windows" }),
	"Looking through the window, you realize that you are gazing "+
	"westwards toward the lowlands. @@day_desc@@. The valley of Imladris "+
	"continues in this direction, and far to the west you know "+
	"there is the Shire and Bree, as this is 'The Last Homely House'.\n");
    add_item( ({ "porch", "bridge", "garden" }),
	"Looking through the window, you see the garden outside the " +
	"porch of Elrond's House. @@day_desc@@, and even further west " +
	"you see a bridge crossing over what must be a river.\n");

    add_item( ({ "chairs" }), "@@desc_chairs@@\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  1);

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

#define CHAIRS 8

object *sitting;

init()
{
    ::init();
    add_action("do_sit", "sit");
    add_action("do_rise", "rise");
    add_action("do_rise", "stand");
}

void
leave_inv(object ob, object to)
{
    if (living(ob)) 
	if (member_array(ob, sitting) != -1) {
	    ob->catch_msg("You rise from your chair.\n");
	    tell_room(TO, QCTNAME(ob) + " rises from " + HIS_HER(ob) + " chair.\n", ob);
	    sitting -= ({ ob });
	}
    ::leave_inv(ob, to);
}

int
do_sit(string str)
{
    if (strlen(str) && str != "in chair" && str != "down")
	return notify_fail("Sit down perhaps?\n");

    if (sizeof(sitting) > CHAIRS)
	return notify_fail("Sorry, all chairs are taken.\n");

    if (member_array(TP, sitting) >= 0)
	return notify_fail("You already sit in a chair.\n");

    write("You comfartably sit down in a free chair.\n");
    say(QCTNAME(TP) + " comfortably sits down in a chair.\n");

    if (sizeof(sitting))
	sitting += ({ TP });
    else
	sitting = ({ TP });

    call_out("get_relaxed", 30, TP);

    return 1;
}

int
do_rise(string str)
{
    if (strlen(str) && str != "up" && str != "up from chair")
	return notify_fail("Rise up perhaps?\n");

    if (member_array(TP, sitting) == -1)
	return notify_fail("But, you are not sitting in a chair!\n");

    write("You stand up, feeling much more relaxed.\n");
    say(QCTNAME(TP) + " stands up from " + HIS_HER(TP) + " chair.\n");

    sitting -= ({ TP });
    return 1;
}

void
get_relaxed(object tp)
{
    if (member_array(tp, sitting) == -1)
	return;

    TP -> add_mana(10);

    call_out("get_relaxed", 30, TP);
}

string
desc_chairs()
{
    if (sizeof(sitting) == 0)
	return "There are " + LANG_WNUM(CHAIRS) + " free chairs now.";

    if (sizeof(sitting) == 1 && sitting[0]!=TP)
	return "Just one chair is occupied by " + COMPOSITE_LIVE(sitting) +
	       ", and " + LANG_WNUM(CHAIRS-1) + " are free.";

    if (sizeof(sitting) == 1 && sitting[0]==TP)
	return "You are sitting in one of the " + LANG_WNUM(CHAIRS) +
	       " chairs in front of the fire.";

    if (member_array(TP, sitting) >= 0 && sizeof(sitting) == 2)
	return "You and " + COMPOSITE_LIVE(sitting - ({ TP })) + " are sitting " +
	       "in front of the warm fire, while " + LANG_WNUM(CHAIRS-2) +
	       " seats are free.";

    if (member_array(TP, sitting) >= 0)
	return "You, " + COMPOSITE_LIVE(sitting - ({ TP })) + " are sitting " +
	       "in front of the warm fire, while " + (sizeof(sitting) == CHAIRS ?
	       "none" : LANG_WNUM(CHAIRS - sizeof(sitting)) ) +
	       " chairs are free.";

    return
	CAP(LANG_WNUM(sizeof(sitting))) + " chairs are taken by "+
	COMPOSITE_LIVE(sitting) + ", and " + (sizeof(sitting) == CHAIRS ?
	"none" : LANG_WNUM(CHAIRS - sizeof(sitting)) ) + " are free.";
}

int
check_sitting()
{
    if (member_array(TP, sitting) >= 0)
    {
	write("But you must stand up first.\n");
	return 1;
    }

    return 0;
}
