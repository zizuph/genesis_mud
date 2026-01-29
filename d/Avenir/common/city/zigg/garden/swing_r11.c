// file name:   swing_r11.c
// creator(s):  Zielia and Lucius, Sept 2006
// last update:
// purpose: seat in the garden
// note:
// bug(s):
// to-do:
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <adverbs.h>
#include <language.h>
#include "zigg.h"

inherit "/lib/commands.c";
inherit (ZIG_LIB + "seating");

#define SS_NORMAL      0        /* Person is sitting upright and normally. */
#define SS_STRETCH     1        /* Person is stretched out.                */

private static int swg;

public void
create_seating(void)
{
    set_name("swing");
    add_adj(({"sturdy","wooden",}));
    set_short("sturdy wooden swing");
    set_long("A sturdy wooden swing hangs "+
	"from a thick oak branch allowing someone to swing out toward the "+
	"aqueduct railing as though flying into the panorama of the City. "+
	"The swing is made out of a heavy piece of wood and webcloth ropes.\n");

    set_seat_names("swing");

    set_seat_id("__zigg_garden_swing");

    set_max_seat(1);
    set_lay_num(0);

    set_stand_cmds(({"stand", "jump"}));
    set_stand_args(({"up", "off", "off swing"}));

    set_allow_kinky(0);
}

public void
ss_seated(int state)
{
    string verb = query_verb();

    switch(state)
    {
    case SS_NORMAL:
	write("You hold the "+ short() +" steady and carefully sit down.\n");
	say(QCTNAME(TP) +" holds the "+ short() +" steady and carefully "+
	    "sits down on it.\n");
	break;

    case SS_STRETCH:
	notify_fail("You cannot lie on this swing.\n");
	break;
    }
}

public void
ss_stand(void)
{
    if(swg)
    {
	write("You jump off the "+ short() +", nearly careening into the "+
	    "aqueduct railing as the momentum sends you stumbling.\n");
	say(QCTNAME(TP) + " jumps off the "+ short() +", nearly careening "+
	    "into the aqueduct railing as the momentum sends "+
	    HIM(TP) +" stumbling.\n");
	remove_alarm(swg);
	swg = 0;
    }
    else
    {
	write("You hop off the "+ short() +", leaving it swaying "+
	    "slightly.\n");
	say(QCTNAME(TP) + " hops off the "+ short() +", leaving it swaying "+
	    "slightly.\n");
    }
}

public void
swinging(int count, object who)
{
    object room = environment(TO);
    switch(++count)
    {
    case 1:
	who->catch_tell("You kick off the ground, propelling yourself "+
	    "backwards on the "+ short() +". Gravity quickly shifts your "+
	    "momentum, sending you swinging forward.\n");
	tell_room(room, QCTNAME(who) +" kicks off the ground, propelling "+
	    HIM(who) +"self backwards on the "+ short() +". Gravity quickly "+
	    "shifts "+ HIM(who) +" momentum, sending "+ HIM(who) +
	    " swinging forward.\n", who, TO);
	break;
    case 2:
	who->catch_tell("You pump your legs and rock your body, gaining "+
	    "momentum as you swing out toward the aqueduct railing.\n");
	tell_room(room, QCTNAME(who) +" pumps "+ HIS(who) +" legs and rocks "+
	    HIS(who) +" body, gaining momentum as "+ HE(who) +" swings out "+
	    "toward the aqueduct railing.\n", who, TO);
	break;
    case 3:
	who->catch_tell("Air caresses your face as you swing faster, soaring "+
	    "higher, as though about to fly out over the Forbidden City.\n");
	tell_room(room, QCTNAME(who) +" swings faster, soaring higher as "+
	    "though about to fly out over the Forbidden City.\n", who, TO);
	break;
    case 4:
	who->catch_tell("You feel euphoric and giddy as each pendulous "+
	    "swing takes you a little closer to the Source.\n");
	tell_room(room, QCTNAME(who) +" seems delighted as "+ HE(who) +
	    " swings higher and higher.\n", who, TO);
	break;
    case 5:
	who->catch_tell("Your energy seems to flag and you begin to swing "+
	    "slower, gradually losing height and momentum.\n");
	tell_room(room, QCTNAME(who) +" seems weary as "+ HE(who) +" begins "+
	    "to swing slower, gradually losing height and momentum.\n", who, TO);
	break;
    case 6:
	who->catch_tell("You come to a stop, feeling youthful and buoyant.\n");
	tell_room(room, QCTNAME(who) +" comes to a stop, looking jubilant.\n",
	    who, TO);
	break;
    }
    if (count < 6)
    {
	swg = set_alarm(10.0, 0.0, &swinging(count, who));
    }
    else
    {
	remove_alarm(swg);
	swg = 0;
    }
}

public int
f_swing(string str)
{
    if(query_seated(TP))
    {
	if(swg)
        {
	    notify_fail("You are already swinging.\n");
	    return 0;
        }

	swinging(0, TP);
	return 1;
    }
    else
    {
	notify_fail("You should sit in it first.\n");
	return 0;
    }
}

public int
f_stop(string str)
{
    if (str != "swinging")    {return 0;}

    if(!query_seated(TP) || !swg)
    {
	notify_fail("You are not swinging.\n");
	return 0;
    }

    write("You drag your feet on the ground, bringing yourself to a "+
	"quick halt.\n");
    say(QCTNAME(TP) +" drags "+ HIS(TP) +" feet on the ground, "+
	"bringing "+ HIM(TP) +"self to a quick stop.\n");

    remove_alarm(swg);
    swg = 0;
    return 1;
}

int
f_push(string str)
{
    object *oblist;
    int num = random(3) + 1;

    if (!strlen(str))
    {
	notify_fail("Push who?\n");
	return 0;
    }

    oblist = parse_this(str, "[the] %l", ACTION_CONTACT);

    if (sizeof(oblist) != 1)
    {
	notify_fail("Push who?\n");
	return 0;
    }

    if (!query_seated(oblist[0]))
    {
	notify_fail(capitalize(oblist[0]->query_the_name(TP)) +" isn't on "+
	    "the swing!\n");
	return 0;
    }

    if (!swg)
    {
	notify_fail(capitalize(oblist[0]->query_the_name(TP)) +" isn't "+
	    "swinging!\n");
	return 0;
    }

    actor("You give", oblist, " a firm push, sending "+ HIM(oblist[0]) +
	" swinging swiftly higher.");
    all2actbb(" gives", oblist," a firm push, sending "+ HIM(oblist[0]) +
	" swinging swiftly higher.", "", ACTION_CONTACT);
    target(" gives you a firm push, sending you swinging swiftly higher "+
	"over the view of the City.", oblist, "", ACTION_CONTACT);
    remove_alarm(swg);
    swg = set_alarm(5.0, 0.0, &swinging(num, oblist[0]));
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(  f_swing, "swing"  );
    add_action(   f_push, "push"   );
    add_action(   f_stop, "stop"   );
}