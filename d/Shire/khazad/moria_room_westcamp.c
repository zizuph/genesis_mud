/* Used in westcamp rooms for random messages. */

#include <filter_funs.h>

inherit "/d/Shire/khazad/moria_room";

//      Global variables
static int     alarm_id;

//      Prototypes
void noise();

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

    alarm_id = set_alarm(1.0 + 5.0 * rnd(), 30.0 + 60.0 * rnd(), noise);
    if (!random(5))
	tell_room(this_object(), "CRUNCH!!\n\nA bettle seems to have "+
	  "gotten underfoot.\n");
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

void
noise()
{
    switch(random(15))
    {
    case 0:
	tell_room(this_object(), "You hear a dripping noise from somewhere "+
	  "nearby.\n");
	break;
    case 1:
	tell_room(this_object(), "You think you hear muffled voices from "+
	  "somewhere nearby.\n");
	break;
    case 2:
	tell_room(this_object(), "A large brown bat silently glides over "+
	  "the forest of stalagmites.\n");
	break;
    case 3:
	tell_room(this_object(), "A large brown bat glides off into the "+
	  "darkness.\n");
	break;
    case 4:
	tell_room(this_object(), "The wind whistles softly from a nearby "+
	  "opening in the cavern.\n");
	break;
    case 5:
	tell_room(this_object(), "You feel the icy touch of a water drop "+
	  "running down the back of your neck.\n");
	break;
    case 6:
	tell_room(this_object(), "You distinctly smell the foul odor of an "+
	  "orc!\n");
	break;
    case 7:
	tell_room(this_object(), "A black beetle swiftly crawl along the "+
	  "nearest stalagmite.\n");
	break;
    case 8:
	tell_room(this_object(), "A flying black beetle hums past your face.\n");
	break;
    case 9:
	tell_room(this_object(), "A brown bat swoops down and deftly snatches "+
	  "a flying beetle for its next meal.\n");
	break;
    }
}
