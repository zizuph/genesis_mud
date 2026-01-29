#pragma strict_types

inherit "/std/receptacle.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

int cage_alarm;
int open_times;

void
create_receptacle()
{
    set_short("wire cage");
    set_name("cage");
    set_adj("wire");
    set_long("This cage is contructed of strong thin wire. The wire is so " +
        "finely meshed together that the cage's small door can only be " +
        "accessed from the outside. It hangs from the ceiling in the " +
        "center of the chamber. ");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The wire cage is attached to the ceiling, you " +
        "cannot take it.\n");

    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     1);

}

void do_cage_alarm()
{
    object *obs, ob;

    if(query_prop(CONT_I_CLOSED)) open_times = 0;
    else open_times++;

    // Find the inventory
    obs = all_inventory(this_object());
    obs = filter(obs, living);

    if(!sizeof(obs))
    {
        // Stop the alarm when there are no messengers
        remove_alarm(cage_alarm);
        cage_alarm = 0;
        return;
    }

    ob = obs[random(sizeof(obs))];

    // See if we have a messenger escape
    if(open_times >= 2 + random(3))
    {
        tell_room(environment(this_object()),
            QCTNAME(ob) + " escapes through the open door of the wire cage " +
            "and disappears from your sight.\n");
        ob->remove_object();
        open_times = 0;
        return;
    }

    // Write a random message
    switch(random(6))
    {
        case 0:
        {
            tell_room(environment(this_object()),
                "The wire cage dangles back and forth.\n");
            break;
        }
        case 1:
        {
            tell_room(environment(this_object()),
                "You hear a noise coming from the wire cage.\n");
            break;
        }
        case 2:
        {
            tell_room(environment(this_object()),
                QCTNAME(ob) + " peeks through the wires " +
                "of the wire cage.\n");
            break;
        }
        case 3:
        {
            tell_room(environment(this_object()),
                "There's a loud thump from the cage as " + QTNAME(ob) + 
                " crashes against the wires in an attempt to escape.\n");
            break;
        }
        case 4:
        {
            tell_room(environment(this_object()),
                QCTNAME(ob) + " stares at you from inside the cage.\n");
            break;
        }
        case 5:
        {
            tell_room(environment(this_object()),
                QCTNAME(ob) + " follows you with " + ob->query_possessive() +
                " eyes.\n");
            break;
        }
    }
}

void enter_inv(object ob, object from)
{
    if(objectp(ob) && !cage_alarm)
        cage_alarm = set_alarm(30.0, 60.0, do_cage_alarm);
}