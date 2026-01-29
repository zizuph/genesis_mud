/*
 * /d/Gondor/common/guild/obj/blind_ob.c
 *
 * This is an object that is cloned into a player to blind him for some time.
 * It is used with the "brawl" command of the Gondorian Rangers.
 *
 * Originally coded by Lord Elessar Telcontar
 *
 * Revision history:
 *
 * /Mercade, 17 November 1993, recoded and enhanced, solved the killing prob
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#define BLIND_SUBLOC "ranger_blind_subloc"

/*
 * Global variables
 */
static int     time,
               csa_aid,
               desting,
               old_prop,
               old_prop2;
static object  brawler,
               victim;

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
    time += i;
}

public void
set_brawler(object ob)
{
    brawler = ob;
}

public void
do_blind()
{
    old_prop = (int)victim->query_prop(LIVE_I_SEE_INVIS);

    victim->add_prop(LIVE_I_SEE_INVIS, -1);
    old_prop2 = victim->query_prop(LIVE_I_SEE_DARK);
    victim->add_prop(LIVE_I_SEE_DARK, old_prop2 - 100);

    csa_aid = set_alarm(itof(time), 0.0, can_see_again);
    time = 0;
}

public void
can_see_again()
{
    object  disarm_ob;

    remove_alarm(csa_aid);
    csa_aid = 0;
    if (time < 1)
    {
        /* Ok, this means my eyes are cleared and I can see */
        victim->add_prop(LIVE_I_SEE_INVIS, old_prop);
        victim->add_prop(LIVE_I_SEE_DARK, victim->query_prop(LIVE_I_SEE_DARK) + 100);
        if (!objectp(victim) || victim->query_ghost() || !living(victim))
            return;

        victim->catch_msg(BSN("You finally manage to clear your eyes of sand, "
          + "and are able to see again!"));
        if (victim->query_humanoid())
            TELL_ROOM(ENV(victim), victim, " rubs " + POSSESSIVE(victim)
              + " eyes, and seems to have cleared them of sand!", victim);
        else
            TELL_ROOM(ENV(victim), victim, " shakes " + POSSESSIVE(victim)
              + " head vigorously to clear " + POSSESSIVE(victim) +
              " eyes of sand!", victim);

	/*
	 * We can see again.
	 * Have we been disarmed? If so, we should know try to pick 
	 * up our weapon and try to wield it.
	 */
        if (objectp(disarm_ob = present("Ranger_Disarm_Object", environment())))
	    disarm_ob->wield_wep_after_blinded();

        if (!interactive(victim) && objectp(brawler) && (ENV(brawler) == ENV(victim)))
        {
            brawler->CATCH_MSG(" glares at you with hatred in "
              + POSSESSIVE(victim) + " sore eyes.", victim);
            if (!objectp(victim->query_attack()))
            {
                /* I think we need an euid to force someone. */
                seteuid(getuid(TO));
                victim->add_prop(LIVE_O_LAST_KILL, brawler);
                victim->command("kill " + brawler->query_real_name());
            }
        }
        desting = 1;
        remove_object();
    }
    /* Oops, somebody has thrown more sand in my eyes! */
    else
    {
        csa_aid = set_alarm(itof(time), 0.0, can_see_again);
        time = 0;
    }
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
        desting = 1;
        remove_object();
        return;
    }

    victim = to;
    victim->add_subloc(BLIND_SUBLOC, TO);
    do_blind();
}

void
leave_env(object from, object to)
{
    from->remove_subloc(BLIND_SUBLOC);
    ::leave_env(from, to);

    if (desting)
        return;
    if (csa_aid != 0)
    {
        can_see_again();
    }
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string  str;
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
        subloc != BLIND_SUBLOC)
    {
	return "";
    }
    if (for_obj == carrier)
        str = "You have trouble looking, since your eyes are filled with sand!\n";
    else
        str = CAP(PRONOUN(carrier)) + " is desperately trying to get sand "
          + "out of " + POSSESSIVE(carrier) + " eyes!\n";
    return str;
}
