inherit "/d/Rhovanion/hazelnut/mirkwood/mirkwood";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>

/*
 * Bit flags used to determine what gems have been added
 */
#define	LEFT_EYE	1
#define	RIGHT_EYE	2
#define	LEFT_EAR	4
#define	RIGHT_EAR	8
#define	NOSE		16
#define	MOUTH		32

#define	GROUP		0	/* Quest bit group number */
#define	BIT		0	/* Quest bit number within group */

#define	EXPERIENCE	0	/* Amount of experience to give out */

/*
 * Property used to remember which gems the current player has
 * put into place
 */
#define	STATUE_PROP	"_dol_guldur_statue"

void
create_forest()
{
    set_long("This is Dol Guldor.  There is a statue here.\n");

    add_item("statue", "@@statue_desc@@");
}

void
reset_forest()
{
}

void
init()
{
    ::init();
    add_action("do_place", "place");
    add_action("do_place", "put");
    add_action("do_place", "stuff");
}

string
statue_desc()
{
    string str;
    int stuffed;

    stuffed = this_player()->query_prop(STATUE_PROP);
    str = "There is a big statue here.";
    if ((stuffed & (LEFT_EYE | RIGHT_EYE)) == 0)
	str += " It's eye sockets are empty!";
    else if ((stuffed & LEFT_EYE) == 0)
	str += " It's left eye socket is empty!";
    else if ((stuffed & RIGHT_EYE) == 0)
	str += " It's right eye socket is empty!";
    if ((stuffed & (LEFT_EAR | RIGHT_EAR)) == 0)
	str += " It doesn't have any ears!";
    else if ((stuffed & LEFT_EAR) == 0)
	str += " It looks like it's left ear is missing!";
    else if ((stuffed & RIGHT_EAR) == 0)
	str += " It looks like it's right ear is missing!";
    if ((stuffed & NOSE) == 0)
	str += " It does not have a nose!";
    if ((stuffed & MOUTH) == 0)
	str += " There are no tongue in it's mouth!";
    return break_string(str + "\n", 76);
}

int
do_place(string arg)
{
    object gem;
    string where, dummy;
    int side, stuffed;

    notify_fail(capitalize(query_verb()) + " what where?\n");
    if (!arg ||
	!parse_command(arg, all_inventory(this_player()),
		       "[the] %o [in] / [into] [right] / [left] %w [of] [the] [statue]",
		       gem, where))
	return 0;
    notify_fail(capitalize(query_verb()) + " it where?\n");
    if (member_array(where, ({ "eye", "ear", "nose", "mouth" }) ) < 0)
	return 0;
    side = 0;
    if (sscanf(arg, "%sleft%s", dummy, dummy) == 2)
	side = -1;
    if (sscanf(arg, "%sright%s", dummy, dummy) == 2)
	side = 1;
    notify_fail(capitalize(query_verb()) + " in which " + where + "?\n");
    if ((where == "eye" || where == "ear") && !side)
	return 0;
    stuffed = this_player()->query_prop(STATUE_PROP);
    notify_fail("You can't " + query_verb() + " THAT there!\n");
    if (!gem->query_match(where, side))
	return 0;
    notify_fail("There's something there already!\n");
    switch (where) {
	case "eye":
	    if ((stuffed & LEFT_EYE) && side < 0)
		return 0;
	    else if ((stuffed & RIGHT_EYE) && side > 0)
		return 0;
	    stuffed |= (side < 0) ? LEFT_EYE : RIGHT_EYE;
	    break;
	case "ear":
	    if ((stuffed & LEFT_EAR) && side < 0)
		return 0;
	    else if ((stuffed & RIGHT_EAR) && side > 0)
		return 0;
	    stuffed |= (side < 0) ? LEFT_EAR : RIGHT_EAR;
	    break;
	case "nose":
	    if (stuffed & NOSE)
		return 0;
	    stuffed |= NOSE;
	    break;
	case "mouth":
	    if (stuffed & MOUTH)
		return 0;
	    stuffed |= MOUTH;
	    break;
    }
    gem->remove_object();
    write("You " + query_verb() + " " + LANG_THESHORT(gem) +
	  " into the statue's " +
	  side ? (side < 0 ? "left " : "right ") : "" +
	  where + ".\n");
    say(QCTNAME(this_player()) + query_verb() + "s " + LANG_ASHORT(gem) +
	  " into the statue's " +
	  side ? (side < 0 ? "left " : "right ") : "" +
	  where + ".\n");
    if (stuffed != (LEFT_EYE | RIGHT_EYE | LEFT_EAR | RIGHT_EAR | MOUTH | NOSE))
	this_player()->add_prop(STATUE_PROP, stuffed);
    else {
	this_player()->remove_prop(STATUE_PROP);
	call_out("reward_player", 2, this_player());
    }
    return 1;
}

void
reward_player(object ob)
{
    ob->catch_msg(break_string("The statue briefly comes to life and "+
			       "thanks you profusely for helping. "+
			       "Suddenly the gems flash and are gone!\n", 76));
    if (ob->test_bit("Rhovanion", GROUP, BIT))
	return;
    ob->set_bit(GROUP, BIT);
    ob->add_exp(EXPERIENCE, 0);
    ob->catch_msg("You feel more experienced.\n");
}
