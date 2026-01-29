/*
 * /d/Gondor/guilds/rangers/obj/blind_ob.c
 *
 * This is an object that is cloned into a player to blind him for some time.
 * It is used with the "brawl" command of the Gondorian Rangers.
 *
 * Originally coded by Lord Elessar Telcontar
 *
 * Revision history:
 *
 * /Mercade, 17 November 1993, recoded and enhanced, solved the killing prob
 * July 2001, Gwyneth: Added a $ to the kill command and changed to OB_NAME
 *                     Tidied up and moved
 * May 2004, Gwyneth, updated
 * Mars 2009, Cotillion: Changed to LIVE_I_BLIND
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define BLIND_SUBLOC "ranger_blind_subloc"

/* Global variables */
static int     gTime,
               gCanSeeAlarm,
               gCanSeeAlarm,
               gDesting,
               gOldProp,
               gOldProp2;
static object  gBrawler,
               gVictim;

/* Prototypes */
public void    can_see_again();

public void
create_object()
{
    set_name("Ranger_Blind_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

    set_no_show();
}

public void
set_time(int i)
{
    gTime += i;
}

public void
set_brawler(object ob)
{
    gBrawler = ob;
}

public void
do_blind()
{
    /*
     * There is now a property for blind.
     * - Cotillion 2009-03-28
    gOldProp = (int)gVictim->query_prop(LIVE_I_SEE_INVIS);
    gVictim->add_prop(LIVE_I_SEE_INVIS, -1);

    gOldProp2 = gVictim->query_prop(LIVE_I_SEE_DARK);
    gVictim->add_prop(LIVE_I_SEE_DARK, gOldProp2 - 100);
    */
    
    gOldProp = gVictim->query_prop(LIVE_I_SEE_INVIS);
    gVictim->add_prop(LIVE_I_SEE_INVIS, -1);
    gVictim->add_prop(LIVE_I_BLIND, gVictim->query_prop(LIVE_I_BLIND) + 1);
    
    gCanSeeAlarm = set_alarm(itof(gTime), 0.0, can_see_again);
    gTime = 0;
}

public void
can_see_again()
{
    object disarm_ob;

    remove_alarm(gCanSeeAlarm);
    gCanSeeAlarm = 0;

    if (gTime < 1)
    {
        /* Ok, this means my eyes are cleared and I can see */
        gVictim->add_prop(LIVE_I_BLIND, gVictim->query_prop(LIVE_I_BLIND) - 1);
        gVictim->add_prop(LIVE_I_SEE_INVIS, gOldProp);
	/*
        gVictim->add_prop(LIVE_I_SEE_DARK, 
            gVictim->query_prop(LIVE_I_SEE_DARK) + 100);
        */
        if (!objectp(gVictim) || gVictim->query_ghost() || !living(gVictim))
            return;

        gVictim->catch_tell("You finally manage to clear your eyes of sand, " +
            "and are able to see again!\n");

        if (gVictim->query_humanoid())
        {
            tell_room(environment(gVictim), QCTNAME(gVictim) + " rubs " + 
                gVictim->query_possessive() + " eyes, and seems to have " +
                "cleared them of sand!\n", gVictim);
        }
        else
            tell_room(environment(gVictim), QCTNAME(gVictim) + " shakes " + 
                gVictim->query_possessive() + " head vigorously to clear " + 
                gVictim->query_possessive() + " eyes of sand!\n", gVictim);

        /* We can see again. Have we been disarmed? If so, we should now */
        /* try to pick up our weapon and try to wield it. */
        disarm_ob = present("Ranger_Disarm_Object", environment());
        if (objectp(disarm_ob))
            disarm_ob->wield_wep_after_blinded();

        if (!interactive(gVictim) && 
          objectp(gBrawler) && 
          (environment(gBrawler) == environment(gVictim)))
        {
            gBrawler->catch_tell(gVictim->query_The_name(gBrawler) +
                " glares at you with hatred in " +
                gVictim->query_possessive() + " sore eyes.\n");

            if (!objectp(gVictim->query_attack()))
            {
                gVictim->attack_object(gBrawler);
                gVictim->add_prop(LIVE_O_LAST_KILL, gBrawler);
            }
        }

        gDesting = 1;
        remove_object();
    }
    /* Oops, somebody has thrown more sand in my eyes! */
    else
    {
        gCanSeeAlarm = set_alarm(itof(gTime), 0.0, can_see_again);
        gTime = 0;
    }
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
        gDesting = 1;
        remove_object();
        return;
    }

    gVictim = to;
    gVictim->add_subloc(BLIND_SUBLOC, this_object());
    do_blind();
}

void
leave_env(object from, object to)
{
    from->remove_subloc(BLIND_SUBLOC);
    ::leave_env(from, to);

    if (gDesting)
        return;

    if (gCanSeeAlarm != 0)
        can_see_again();
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != BLIND_SUBLOC)
    {
        return "";
    }

    if (for_obj == carrier)
    {
        str = "You have trouble looking, since your eyes are filled " +
            "with sand!\n";
    }
    else
    {
        str = capitalize(carrier->query_pronoun()) + " is desperately " +
            "trying to get sand out of " + carrier->query_possessive() + 
            " eyes!\n";
    }

    return str;
}
