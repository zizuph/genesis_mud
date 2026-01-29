inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

//   Prototypes
void go_out();

int alarm_id;
int fire, nr_of_tries;

void
create_room()
{
    set_short("Seond floor of northern tower");
    set_long("@@room_long");

    add_item("stairs", break_string(
	  "The broad wooden staircase winds upwards to the top floor, "
	+ "and downwards to the first floor following the wall of the "
        + "tower.\n", 70));

    add_item(({"fire", "flames", "magical fire"}), "@@fire_long");

    /* Climbing the stairs is tiresome... */
    add_exit(STAND_DIR + "tower14", "up", "@@check_fire", 4);
    add_exit(STAND_DIR + "tower12", "down", 0, 4);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, "@@fire_on");

    fire = 1;
    nr_of_tries = 0;
}

void
reset_room()
{
    if (!fire)
    {
	fire = 1;
	nr_of_tries = 0;
    }
}

int
check_fire()
{
    if (fire)
    {
	write("You cannot get past the burning fire.\n");
	return 1;
    }
    return 0;
}

string
fire_long()
{
    string str;

    if (fire)
    {
	str = "The magical fire might have been burning here for ages. ";
	switch (nr_of_tries)
	{
	case 0:
	    str += "It burns at full strength.";
	    break;
	case 1:
	    str += "The flames of the flicker furiously.";
	    break;
	case 2:
	    str += "It is burning, but not at full strength.";
	    break;
	case 3:
	    str += "It is burning weakly.";
	    break;
	case 4:
	    str += "The flames are about to vanish.";
	    break;
	default:
	    str += "You are deceived... There are no flames.";
	}
	return break_string(str + "\n", 70);
    }
    else
	return "You don't see that.\n";
}

int
fire_on()
{
    return fire;
}

int
check_serpent()
{
    seteuid(getuid());
    return (STAND_DIR + "tower14")->serpent_present();
}

string
room_long()
{
    string str;

    str = "You are standing on the second floor of the northern tower. "
	+ "It is quite dark here, and the air is damp. The tower "
	+ "has not been used for a very long time. Circular stairs "
	+ "lead up and down. ";

    if (check_serpent())
    {
	str += "You sense danger on the floor above you. ";
    }

    if (fire)
    {
	str += "There is a magical fire burning on the stairs that "
	     + "lead up. It is blocking your way.\n";
    }
    else
    {
	str += "On the stairs that lead up are the remains of a fire.\n";
    }

    return break_string(str, 70);
}

/*
 *  This function should be called by anything that
 *  can be filled with water, e.g. a bucket.
 *  It returns 1 if the action was successful or 0 if not.
 */
int
extinguish(string str)
{
    if (!str)
	return 0;

    str = lower_case(str);

    if (fire && str == "fire")
    {
        alarm_id = set_alarm(1.0,0.0,&go_out());
	return 1;
    }
    return 0;
}

void
go_out()
{
    remove_alarm(alarm_id);
    if (!fire)
	return;

    if (random(4) < nr_of_tries)
    {
	tell_room(this_object(), "The flames go out.\n");
	fire = 0;
    }
    else
    {
	nr_of_tries++;
	tell_room(this_object(),
	    "The flames flicker for a minute, but grow bigger again.\n"
	  + "Not as big as they were before, though.\n");
    }
}
