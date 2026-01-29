/*
 *  This is a shadow responsible for petrified corpses
 *  when killed by the staff of the medusa.
 *
 *  Based off /d/Krynn/throtyl/obj/petrify_corpse_sh.c
 *
 *  Arman, January 2021
 */

inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>

public nomask void set_no_corpse(int flag);
int no_corpse_flag;

#define CORPSE_OBJ   "/d/Genesis/start/human/obj/petrify_corpse"

public object 
make_corpse()
{
    int size;
    object corpse;

    /*First let us check if the creator of the
     *victim didn't prepare his/her own mask of
     *the make_corpse() function.             */

    if (objectp(corpse = (object)query_shadow_who()->make_corpse()))
    {
        return corpse;
    }

    if (!no_corpse_flag)
    {
        setuid();
        seteuid(getuid());

        corpse = clone_object(CORPSE_OBJ);
        size = query_shadow_who()->query_prop(OBJ_I_VOLUME);

        corpse->set_name(query_shadow_who()->query_name());
        corpse->add_prop(CONT_I_WEIGHT,
            query_shadow_who()->query_prop(CONT_I_WEIGHT));
        corpse->add_prop(CONT_I_VOLUME,
            query_shadow_who()->query_prop(CONT_I_VOLUME));
        corpse->add_prop(CONT_I_MAX_WEIGHT,
            query_shadow_who()->query_prop(CONT_I_MAX_WEIGHT));
        corpse->add_prop( CONT_I_MAX_VOLUME,
            query_shadow_who()->query_prop(CONT_I_MAX_VOLUME));
        corpse->add_prop(CORPSE_S_RACE,
            query_shadow_who()->query_race_name());
        corpse->add_prop(CONT_I_TRANSP, 1);

        return corpse;
    }
}

/* Function    : set_no_corpse
 * Descriptions: When you have a corpse then a bunch or procedures
 *               is executed. It's no need to do that if a death
 *               variant doesn't leave a corpse.
 * Arguments   : 1 if there is no corpse yet, 0 otherwise (default).
 */
public nomask void 
set_no_corpse(int flag = 0)
{
    no_corpse_flag = flag;
}

/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    tell_room(environment(killer),
        QCTNAME(this_object()) + " is petrified to stone! ", 
        this_object());

    if (!living(killer))
    {
        return;
    }
    /*
     * Give specific information about who killed this poor soul.
     */

    tell_object(killer, "Your staff of the medusa wails in sibilant " +
        "victory as it turns " + this_object()->query_the_name(killer) + 
        " into a statue!\n");

    tell_room(environment(killer),  QCTPNAME(killer) + " staff of the " +
        "medusa wails in sibilant victory as it turns " +
        this_object()->query_objective() + " into a statue!\n", 
       ({ this_object(), killer }));
}
