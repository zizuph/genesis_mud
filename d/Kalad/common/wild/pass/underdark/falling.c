/*
 * /d/Kalad/common/wild/pass/underdark/falling.c
 * Purpose    : Entrance to Dark Dominion at the rate of 9.8m/s/s
 * Located    : Dead center of the shaft leading down from Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 *              Fysix, X-mas '97: fixed bug, player got stuck in here.
 */

# pragma strict_types

# include "dark_dom.h"
# include <macros.h>
# include <stdproperties.h>

inherit DARK_DOM;

void
create_dark_dom()
{
    set_short("Falling");
    set_long("You are falling rapidly towards the ground. You have a nice\n" +
      "view from here though....\n");

    add_prop(ROOM_M_NO_ATTACK, "You cannot fight while falling.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
}

void
land(object ob)
{
string str;

    if (!ob || !present(ob, this_object()))
	return;

    str = "You hear a horrible noise from above, " +
      "suddenly you see ";

    if (living(ob))
    {
	tell_room(DARK(u7), str + QTNAME(ob) +
	  " slams into the ground.\n");
	ob->move_living("M", DARK(u7));

	tell_object(ob, "You slam into the ground with terrible force!\n");
	ob->heal_hp(-600);
	ob->remove_prop(LIVE_S_EXTRA_SHORT);

	if (ob->query_hp() < 1)
	    ob->do_die(this_object());
    }
    else
    {
	tell_room(DARK(u7), str + LANG_ASHORT(ob)+" falls down.\n");
	ob->move(DARK(u7));
    }
}

void
halfway(object ob)
{
string str;

    if (!ob || !present(ob, this_object()))
	return;

    str = "You hear a loud noise and suddenly see ";

    if (living(ob))
    {
	tell_object(ob, "The ground is getting closer.\n");
	str += QTNAME(ob);
    }
    else
	str += LANG_ASHORT(ob);

    tell_room(DARK(u6), 
      str + " fall through the shaft and continue down.\n");

    set_alarm(3.0, 0.0, &land(ob));
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
	tell_object(ob, "You feel unhappy not standing on solid ground.\n");
	add_prop(LIVE_S_EXTRA_SHORT, " is also falling.\n");
    }

    set_alarm(3.0, 0.0, &halfway(ob));
}

int
quit(string str)
{
    write("No no, you can't escape this fall that easy.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(quit, "quit");/* Don't let anyone quit himself out. */
}
