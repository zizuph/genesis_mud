/*
 * N_chimn.c
 *
 * Skippern 20(c)02
 *
 * This is inside a chimney, this will give the player lots of messages about 
 *  the environment of the chimney before he arrives out in the fireplace
 *  in the bottom.
 */
inherit "/d/Gondor/std/room";

#include "../../defs.h"
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
void first_mesg();
void second_mesg();
void third_mesg();
void last_mesg();

void
create_gondor()
{
    set_short("a tube");
    set_long("he solid walls of the chimney is completely covered in sooth, " +
		"it is dark, cramped, and incredible unconfortable.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -15);
}

void
last_mesg()
{
    write("You finally climbs yout of the fireplace.\n");
    this_player()->move_living("M", DOL_HILLS + "m-11/hall2", 1, 0);
    say(QCTNAME(this_player()) + " climbs yout of the fireplace.\n");
}

void
third_mesg()
{
    object o;

    write("You feel a sting in your chest.\n");
    o = clone_object(DOL_OBJ + "sooth");
    o->move(this_player());
    o->start_poison(0);
    set_alarm(3.0, 0.0, &last_mesg());
}

void
second_mesg()
{
    write("The taste of sooth is unbearable.\n");
    set_alarm(4.0, 0.0, &third_mesg());
}

void
first_mesg()
{
    write("You hear something falling under you.\n");
    set_alarm(4.0, 0.0, &second_mesg());
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarm(2.0, 0.0, &first_mesg());
}

