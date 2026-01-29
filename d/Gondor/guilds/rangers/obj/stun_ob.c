/*
 * /d/Gondor/guilds/rangers/obj/stun_ob.c
 *
 * This is an object that is cloned into a player to stun him for some time.
 * It is used with the "brawl" command of the Rangers of the North.
 *
 * Originally coded by Lord Elessar Telcontar
 *
 * Revision history:
 * /Elessar, 19. Sept. 1994. Modified from disarm_ob.c to be used with
 *  the new stun-effect.
 */
inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"


int    Rtime, Desting;
int    Seen = 0;
int    RsaAid;
object Brawler;
object Victim;

void
create_object()
{
    set_name("Ranger_Stun_Object");

    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_time(int i)
{
    Rtime = i;
}

void
set_seen(int i)
{
    Seen = i;
}

void
set_brawler(object ob)
{
    Brawler = ob;
}

void
remove_stun_again()
{
    int bp;

    RsaAid = 0;

    if (Brawler && ENV(Brawler) == ENV(Victim))
        bp = 1;

    if (Victim->query_ghost() || !living(ENV(TO)))
    {
        Desting = 1;
        Rtime = 0;
        remove_object();
        return;
    }

    if (!Rtime) 
    {
        Victim->remove_stun();
        if (Victim->query_prop(LIVE_I_STUNNED) <= 0)
        {
            Victim->catch_tell("You recover your balance again.\n");
            if (bp)
                Brawler->catch_tell("You notice that " +
                    Victim->query_the_name(Brawler) + " has recovered " +
                    POSSESSIVE(Victim) + " balance again.\n");
        }

        if (bp && Seen)
        {
            Brawler->catch_tell(Victim->query_The_name(Brawler) +
                " glares angrily at you.\n");
            Victim->catch_tell("You glare angrily at " +
                Brawler->query_the_name(Victim) + ".\n");
            say(QCTNAME(Victim) + " glares angrily at " + QTNAME(Brawler) +
                ".\n", ({ Brawler, Victim }));

            if (!objectp(Victim->query_attack()))
                Victim->attack_object(Brawler);
        }

        Desting = 1;
        remove_object();
        return;
    }

    if (Rtime > 0)
        RsaAid = set_alarm(itof(Rtime), 0.0, remove_stun_again);

    Rtime = 0;
}

void
do_stun()
{
    RsaAid = set_alarm(itof(Rtime), 0.0, remove_stun_again);
    Rtime = 0;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to))
    {
        set_alarm(1.0, 0.0, remove_object);
        Desting = 1;
        return;
    }

    if (!living(to))
    {
        set_alarm(1.0, 0.0, remove_object);
        Desting = 1;
        return;
    }

    Victim = to;
    set_alarm(3.0, 0.0, do_stun);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (Desting)
        return;

    if (RsaAid)
        remove_stun_again();
}

