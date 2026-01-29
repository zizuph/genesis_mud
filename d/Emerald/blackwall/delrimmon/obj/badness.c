/*
 *  /d/Emerald/blackwall/delrimmon/obj/badness.c
 *
 *  So this is my final attempt to make Akugla a truly mono-e-mono
 *  fight. When he is attacked by more than one person, he throws
 *  this nasty little effect into the room. It begins to devastate
 *  anyone in the area who is not on the ledge.
 *
 *    Used by: /d/Emerald/blackwall/delrimmon/npc/captain.c
 *         in: /d/Emerald/blackwall/delrimmon/lakeside/caves/ante_room.c
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "/d/Emerald/blackwall/delrimmon/defs.h"

inherit "/std/object";

#include <filter_funs.h>
#include <stdproperties.h>
#include <time.h>

/* Prototypes */
public void        create_object();
public void        enter_env(object dest, object old);
public void        zap_everyone();
public void        increase_intensity();
public void        remove_badness();

/* Global Variables */
public int         Damage_Level = 200;

/* Definitions */
#define            BADNESS_LOG   "/d/Emerald/log/del_rimmon/badness"


/*
 * Function name:        create_object
 * Description  :        set up the effect
 */
public void
create_object()
{
    set_name(BADNESS);
    add_name( ({ "energy", "electricity", "ribbon", "mass" }) );
    add_pname( ({ "energies", "electricities" }) );
    add_adj( ({ "purple", "harmful", "arcing" }) );

    set_short("arcing mass of purple energy");
    set_long("Ribbons of harmful purple energy are arcing all along"
      + " the floor, damaging anyone they touch! Look out!\n");

    add_prop(OBJ_M_NO_GET, "You dare not touch the stuff!\n");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        enter_env
 * Description  :        When it enters the room, we want to start
 *                       up the damaging effects.
 * Arguments    :        object dest - the destination we are entering
 *                       object old  - the location we came from.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    set_alarm(10.0, 10.0, zap_everyone);
} /* enter_env */


/*
 * Function name:        zap_everyone
 * Description  :        hurt everyone in the room who is not on the
 *                       ledge
 */
public void
zap_everyone()
{
    int     i;
    mixed  *target = filter(FILTER_LIVE(all_inventory(environment(
                       this_object()))),
                       &not() @ &->query_prop("_live_s_sitting"));

    tell_room(environment(this_object()), "Purple energy lashes"
      + " across the floor, searing everything it touches!\n");

    if (!sizeof(target))
    {
        set_alarm(240.0, 0.0, remove_badness);
    }
    else
    {
        for (i = 0; i < sizeof(target); i++)
        {
            target[i]->catch_tell("You are horribly burned by the"
              + " purple energy!\n");
            target[i]->command("$wail");
            target[i]->heal_hp(0 - Damage_Level);

            if (!target[i]->query_npc())
            {
                write_file(BADNESS_LOG,
                    TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
                  + ctime(time())[11..18] + ") "
                  + capitalize(target[i]->query_name()) + " takes "
                  + Damage_Level + " damage from the badness effect!\n");
            }

            if (target[i]->query_hp() == 0)
            {
                target[i]->do_die();
                if (!target[i]->query_npc())
                {
                    write_file(BADNESS_LOG,
                        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
                      + ctime(time())[11..18] + ") "
                      + capitalize(target[i]->query_name())
                      + " was killed by"
                      + " the badness effect!\n");
                }
            }
        }
    }
} /* zap_everyone */


/* 
 * Function name:        increase_intensity
 * Description  :        So, they want to stay and get more hurt?
 *                       Fine, we up the damage.
 */
public void
increase_intensity()
{
    tell_room(environment(this_object()), "The purple energy grows"
      + " thicker, and more intense!\n");
    Damage_Level += 200;
} /* increase_intensity */


/*
 * Function name:        remove_badness
 * Description  :        Looks like no one is left in the room. Lets
 *                       Kill the effect.
 */
public void
remove_badness()
{
    tell_room(environment(this_object()), "The purple energy suddenly"
      + " shrinks to nothing and fizzles out.\n");
    remove_object();
} /* remove_badness */