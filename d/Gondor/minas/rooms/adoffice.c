/*
 * /d/Gondor/minas/rooms/adoffice.c
 *
 * Modification Log:
 *    31 August 2001, Alto. Repaired enemy list so that it would
 *      reset itself when the Gondor clock resets.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define SAVE		(MINAS_DIR + "npc/hunthor")
#define STATUS_LOG      (LOG_DIR + "rangers")
#define PRISON		(MINAS_DIR + "rooms/prison")
#define THE_CLOCK            ("/d/Gondor/common/mordor/sys/clock")

void    reset_room();

static  object  Master;
        string *bsw_solved = ({}),
               *enemy = ({});

public nomask int
query_clock_time() 
{
    return (THE_CLOCK->time());
}


public void
create_gondor()
{
    set_short("the office of the Master of Advice");
    set_long(BSN("You are in the office of the Minas Tirith Master of Advice. "
      + "He is the counsellor of the Steward, and has a high position in the "
      + "City. If he is present, he will quite possibly have tasks for you to do. "
      + "To the east is the administration office."));
    add_prop(ROOM_I_INSIDE,1);
    add_exit(MINAS_DIR + "rooms/mtoffice", "east", 0, 0);
    FIX_EUID
    restore_object(SAVE);
    reset_room();
}


/*
 * Is this old code? I believe this may be the reason the enemy
 * list stopped clearing. We should also check into the prison
 * code to make sure it isn't clogged up as well.
 *
 */
public void
reset_rq_stage()
{
    enemy = ({});
    save_object(SAVE);
    PRISON->load_me();
    PRISON->reset_rq_stage();
}



/*
 * During the first two hours following Gondor clock restart,
 * this room will cause the enemy list to clear upon room reset
 *
 */
public void
reset_room()
{
    Master = clone_npc(Master, MINAS_DIR + "npc/hunthor");

    if (query_clock_time() <= 7200) 
    {
    enemy = ({});
    save_object(SAVE);
    }
}

void
add_bsw_solved(string name)
{
    bsw_solved += ({ name });
    save_object(SAVE);
}

string *
query_bsw_solved()
{
    return bsw_solved;
}

void
add_enemy(object e)
{
    int     i;
    string  n = e->query_real_name(),
            r = e->query_race();

    if (e->query_npc())
        return;
    if (!stringp(n))
        return;


    if ((i = member_array(n, enemy)) >= 0)
    {
        if (r != enemy[i+1])
        {
            enemy[i+1] = r;
            save_object(SAVE);
        }
        return;
    }

    enemy += ({ n, r });
    if (IS_RANGER(e))
      write_file(STATUS_LOG,CAP(n) + " was reported having killed someone in Minas Tirith, "
        + ctime(time()) + ".\n");
    save_object(SAVE);
}

void
remove_enemy(string name)
{
    int     i;
    object  who = this_interactive();

    name = LOW(name);
    if ((i = member_array(name, enemy)) < 0)
        return 0;
    enemy = exclude_array(enemy, i, i+1);
    save_object(SAVE);
}

varargs mixed
query_enemy(string name, string race)
{
    int     i;

    if (!stringp(name))
        return enemy;

    name = LOW(name);
    if ((i = member_array(name, enemy)) < 0)
        return 0;

    if (!stringp(race))
        race = find_living(name)->query_race();
    if (!stringp(race))
        return 1;
    if (enemy[i+1] != race)
    {
        remove_enemy(name);
        return 0;
    }
    return 1;
}

