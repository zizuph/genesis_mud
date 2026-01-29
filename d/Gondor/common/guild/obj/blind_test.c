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

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

/*
 * Global variables
 */
int    time;
object brawler;
object victim;

void
create_object()
{
    set_name("Ranger_Blind_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_time(int i)
{
    time = i;
}

void
set_brawler(object ob)
{
    brawler = ob;
}

void
do_blind()
{
    int old_prop = (int)victim->query_prop(LIVE_I_SEE_DARK);

    victim->add_prop(LIVE_I_SEE_DARK, (old_prop - 100));

    call_out("can_see_again", time);
}

void
can_see_again()
{
    int old_prop = (int)victim->query_prop(LIVE_I_SEE_DARK);

    victim->add_prop(LIVE_I_SEE_DARK, (old_prop + 100));

    if ((!objectp(victim)) || (victim->query_ghost()))
    {
        return;
    }

    victim->catch_msg(BSN("You finally manage to clear your eyes of sand, " +
        "and are able to see again!"));
tell_room(environment(victim), ({ victim->query_name() + " rubs " + victim->query_possessive() +
    " eyes, and seems to have cleared them of sand!\n",
    "The " + victim->query_nonmet_name() + " rubs " + victim->query_possessive() + 
    " eyes, and seems to have cleared them of sand!\n",
    ""}),
    victim, victim);
    TELL_ROOM(ENV(victim), victim, " rubs " + POSSESSIVE(victim) +
        " eyes, and seems to have cleared them of sand!", victim);

    if ((objectp(brawler)) && (environment(brawler) == environment(victim)))
    {
        brawler->CATCH_MSG(" glares at you with hatred in " +
            POSSESSIVE(victim) + " sore eyes.", victim);

        /* I think we need an euid to force someone. */
        seteuid(getuid(TO));
        victim->add_prop(LIVE_O_LAST_KILL, brawler);
        victim->command("kill " + brawler->query_real_name());
    }

    call_out("remove_object", 1);
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to))
    {
        call_out("remove_object", 1);
        return;
    }

    if (!living(to))
    {
        call_out("remove_object", 1);
        return;
    }

    victim = to;
    do_blind();
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (find_call_out("can_see_again") != -1)
    {
        can_see_again();
    }
}