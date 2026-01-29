/*
 *  IGARD_ROOM + "catapult_room.c"
 *
 *  Temporary room for flying through the air.
 *
 *  Last modified by Alto, 23 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";

public string      long_func();
public int         start_catapult();
public int         move_catapult();
public int         exit_catapult();
public int         remove_excess_item(object ob);
public int	        catch_all(string str);

object             actor;

public void
create_gondor()
{
    set_short("in the air");
    set_long(long_func);

    add_item(({"air", "room", "surroundings"}), long_func);
    sky_add_items();
    outside_add_items();

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_MAGIC, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    reset_room();
}


public string
long_func()
{
    string  longtxt;

    longtxt = 
        "You are flying through the air, very high above the ground, "
        + "hurtling along at a tremendous rate of speed. As you tumble head "
        + "over heels through the air, the stone of Isengard shifts "
        + "into the blue of the sky, then back to stone, then back to "
        + "sky, and then back again. If the fall doesn't kill you first, "
        + "it seems likely that you will lose your lunch.\n"; 

    return longtxt;
}


int
move_catapult()
{
    actor = TP;

    set_alarm(0.0, 0.0, &write("Wind screams in your ears as you "
        + "somersault head over heels toward the sky.\n"));
    set_alarm(5.0, 0.0, &write("You continue hurtling in an upward "
        + "trajectory. The ground falls away below you and the ring "
        + "wall grows smaller behind.\n"));
    set_alarm(10.0, 0.0, &write("Your ascent begins to slow.\n"));
    set_alarm(15.0, 0.0, &write("Having reached the highest point "
        + "inertia and gravity permit, you begin the inevitable descent "
        + "toward the ground below.\n"));
    set_alarm(20.0, 0.0, &write("You are falling faster and faster now. "
        + "It seems unlikely you will survive this.\n"));
    set_alarm(22.0, 0.0, &write("The ground rushes up to meet you!\n"));

    return 1;

}


int
exit_catapult()
{
    int healed, int_health, hurt;

    actor = TP;
    healed = TP->query_max_hp();
    int_health = healed - 1;
    hurt = healed - int_health;

    write("Your body shatters as it smashes into the ground.\n");
    tell_room(environment(actor), QCTNAME(actor) + " smashes into "
        + "the ground! Blood and gore splatter everywhere.\n", 
        ({actor}));
    tell_room(IGARD_WALL + "gate", QCNAME(TP) + " falls from "
        + "the sky and smashes into the ground. Blood and gore "
        + "splatter everywhere.\n");

    TP->set_hp(hurt);

    TP->move_living("M", IGARD_WALL + "gate", 1, 0);

//    if (TP->query_prop(FURNACE_KILLED_ME))
//    {
//        TP->heal_hp(-50000);
//        TP->do_die(ENV(TP));
//    }

    return 1;
}


int
start_catapult()
{
    move_catapult();
    set_alarm(23.0, 0.0, &exit_catapult());        
    return 1;
}



public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        {
        start_catapult();
        initiate_trap();
        return;
        }
    set_alarm(2.0, 0.0, &remove_excess_item(ob));

}


public int
remove_excess_item(object ob)
{
    string excess;

    excess = ob->query_short();

    write("The " + excess + " falls away behind you and out of sight.\n");
    ob->remove_object();
    return 1;
}


public int 
catch_all(string str)
{
    string  vb = query_verb();
    object trappee;
    trappee = TP;

    switch (vb)
    {
    case "quit":
        WRITE("What? And miss the thrill of flying through the air with "
            + "the greatest of ease?");
        return 1;
        break;
    default:
        return 0;
    }
}

public int
initiate_trap()
{
    add_action(catch_all, "", 1);
}