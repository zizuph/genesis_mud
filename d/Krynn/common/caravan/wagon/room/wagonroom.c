/*
 *  Filename:       wagon/room/wagonroom.c
 *  Description     This is the base files for the room that are the wagon
 'inside'
 *                  in a caravan
 *
 *  Copyright (c) Aug. 2003 by Peter B. Lund
 */
#include "/d/Krynn/common/defs.h"
#include "../wagon.h"
#include "/sys/language.h"
#include "/sys/macros.h"
#include "../../obj/fire.h"
/* Inherit the Krynn std room */

inherit R_FILE

#define CREATE "create_wagon_room"
#define RESET  "reset_wagon_room"

int    gRoomType;
int    fire_startlevel; /* the firelevel that this wagon starts
                           in people. */
int    fire_damage;     /* the base fire damage that this wagon
                           will put in a person. */
int    fire_strength;   /* the strength of this wagons fire */



object myWagon;


public void
set_wagon(object wagon)
{
    myWagon = wagon;
}

public object
query_wagon()
{
    return myWagon;
}



public string
long_desc(string longdesc)
{
    return longdesc;
}

public string
short_desc(string shortdesc)
{
    return shortdesc;
}

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * Leaves the wagon.
 */

public int
leave_wagon(string str)
{
    string desc;

    if (objectp(query_wagon()))
        desc = query_wagon()->short();

    if (str == "wagon")
    {

        if (!myWagon->check_leave_wagon())
            return 1;

        write("You leave the " + desc + ".\n");
        say(QCTNAME(TP) + " leaves the wagon.\n", TP);
        tell_room(query_wagon()->query_room(R_LEFT, M_OBJECT), QCTNAME(TP) +
        " arrives from the " + desc + ".\n");
        TP->move_living("M", query_wagon()->query_room(R_LEFT, M_OBJECT) );
        return 1;
    }
    else
        return 0;

}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{

/*  start at level 3 fire with 25 in base damage and
    150 base damage from the room fire */

    fire_startlevel = WAGON_FIRE_LVL_START;
    fire_damage = WAGON_FIRE_DAMAGE;
    fire_strength = WAGON_FIRE_DOT;

    call_other(TO, CREATE);
    set_dircmd("wagon");

    set_long("@@long_desc@@");
    set_short("@@short_desc@@");

}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}


public void
init()
{
    ::init();

    add_action(leave_wagon, "leave");
}


varargs public mixed
long(string str)
{
    return ::long(str);
}

varargs public mixed
short(string str)
{
    return ::short(str);
}


public int
burn_actions()
{
    mixed obj;
    object fireobj;
    int ir, dam, rnddam, rndfire;

    obj = all_inventory(TO);
    for (ir = 0;ir < sizeof(obj);ir++)
    {
        if (living(obj[ir]))
        {
          /* takes damage from the room */
          dam =  (OBJ + "burning_damage")->hurt_player(obj[ir],
          fire_damage);

          /* person aren't engulfed in flames already is he? */
          if (!obj[ir]->query_burning_shadow())
          {
            rnddam = random(dam);
            rndfire = random(fire_damage);

            if ( dam > 0 && ( rnddam > rndfire ) )
              /* this person goes on fire! */
            {
                setuid();
                seteuid(getuid());


                tell_object( obj[ir], "The fire catches onto you!\n");
                tell_room(E(obj[ir]), QCTNAME(obj[ir]) + " is suddenly caught " +
                "in the fire.\n",   obj[ir]);
                fireobj=clone_object(OBJ + "burning_object");
                fireobj->move(obj[ir],1);
                fireobj->start(obj[ir], fire_startlevel, fire_strength,
                 FIRE_DEFAULT_DOT_TIME   );
            }
          }
        }
    }

}


