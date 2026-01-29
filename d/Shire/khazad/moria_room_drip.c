/* Used as the master room for tunnel rooms which drip water. */

inherit "/d/Shire/khazad/moria_room";

#include <filter_funs.h>

//      Global variables
static int     alarm_id;

//      Prototypes
void drip();

/* enter_inv and leave_inv are used in certain rooms to generate */
/* messages when a player is present in them and to remove the   */
/* alarm when it's empty.                                        */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !interactive(ob))
	return;

    if (alarm_id && sizeof(get_alarm(alarm_id)))
	return;

    alarm_id = set_alarm(1.0 + 5.0 * rnd(), 20.0 + 20.0 * rnd(), drip);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!objectp(ob) || !interactive(ob))
	return;

    if (!sizeof(FILTER_PLAYERS(all_inventory(this_object()))))
    {
	remove_alarm(alarm_id);
	alarm_id = 0;
    }
}

/* drip() is used in certain tunnel*.c files */

void
drip()
{
    switch(random(9))
    {
    case 0:
	tell_room(this_object(), "You hear a dripping noise from somewhere "+
	  "nearby.\n");
	break;
    case 1:
	tell_room(this_object(), "A tiny drop of water falls on your head.\n");
	break;
    case 2:
	tell_room(this_object(), "A tiny drop of water lands on a rock next "+
	  "to you.\n");
	break;
    case 3:
	tell_room(this_object(), "A large drop of water splatters at your feet.\n");
	break;
    case 4:
	tell_room(this_object(), "You see a drop of water forming above you.\n");
	break;
    case 5:
	tell_room(this_object(), "You feel the icy touch of a water drop "+
	  "running down the back of your neck.\n");
	break;
    case 6:
	tell_room(this_object(), "As you look up a big drop of water hits "+
	  "you in the eye.\n");
	break;
    }
}
