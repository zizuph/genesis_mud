/*
 * /d/Gondor/common/guild/obj/disarm_ob.c
 *
 * This is an object that is cloned into a player to disarm him for some time.
 * It is used with the "brawl" command of the Gondorian Rangers.
 *
 * Originally coded by Lord Elessar Telcontar
 *
 * Revision history:
 *
 * /Mercade, 17 November 1993, recoded and enhanced, solved the killing prob
 * /Mercade, 6 January 1994, fixed re-wielding of the wrong weapon.
 * /Elessar, 15 June 1994, fixed so weapon cannot be rewielded nor picked
 *  up for the duration of the disarming.
 */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define SUCCESS_FUNCTION (40 + random(30))

int    rtime;
int    twohanded;
int    wait;
int    seen = 0;
int    can_wield = 0;
string wep_name;
object wep;
object brawler;
object victim;

void
create_object()
{
    set_name("Ranger_Disarm_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_time(int i)
{
    rtime = i;
}

void
set_seen()
{
    seen = 1;
}

void
set_brawler(object ob)
{
    brawler = ob;
}

int
test_successful()
{
    if ((!objectp(brawler)) || (!objectp(victim)))
        return 0;

    return ((brawler->query_skill(SS_BRAWLING) +
             brawler->query_stat(SS_STR) -
             victim->query_stat(SS_STR) -
             victim->query_skill(SS_PARRY)) >
                 SUCCESS_FUNCTION);
}

void
complete_disarm()
{
    if (twohanded && wep->query_hands() == W_BOTH)
    {
        brawler->LCATCH_MSG("Your disarming strike hit the left hand of ",
          ", so that "+PRONOUN(victim)+" loses the weapon completely!",victim);
        victim->catch_msg(BSN("Another blow, this time to your left hand, "+
          "causes you to lose your hold on the weapon completely!"));
        tell_room(ENV(victim), "The blow on the other hand causes "+
          QTNAME(victim) + " to lose "+POSSESSIVE(victim) + " weapon completely!\n",
            ({ brawler, victim }));
        victim->command("drop "+OB_NAME(wep));
        if (!rtime) rtime = 10;
        call_out("wield_wep_again",rtime);
        wait = 1;
        return;
    }
    else if (wep->query_hands() == W_BOTH)
    {
        brawler->LCATCH_MSG("Your blow was so successful that ", " loses " +
            "grip on " + POSSESSIVE(victim) + " weapon with " +
            POSSESSIVE(victim) + " right hand. " + CAP(PRONOUN(victim)) +
            " is able to hold the weapon in " + POSSESSIVE(victim) +
            " left hand though.", victim);
        victim->catch_msg(BSN("The blow on your right hand was so hard that " +
            "your hand loses its grip on the weapon completely. You manage " +
            "to hold it in your left hand though. You cannot do any harm to " +
            "an opponent now, for you need to wield it in both hands."));
        tell_room(ENV(victim), "The blow on the hand causes " +
            QTNAME(victim) + " to completely lose grip op the weapon with " +
            POSSESSIVE(victim) + " right hand. " + CAP(PRONOUN(victim)) +
            " manages to hold the weapon in " + POSSESSIVE(victim) +
            " left hand though.\n", ({ brawler, victim }) );

        if (!rtime) rtime = 10;
        twohanded = 1;
        call_out("wield_wep_again", rtime);
        return;
    }

    brawler->LCATCH_MSG("Your blow was so successful that ", " loses the " +
        "weapon completely!", victim);
    tell_room(ENV(victim), "The blow on the hand causes " + QTNAME(victim) +
        " to drop " + POSSESSIVE(victim) + " weapon completely!\n",
        ({ brawler, victim }) );
    victim->catch_msg(BSN("The blow to your hand was so hard that you drop " +
        "your weapon!"));

    FIX_EUID;

    victim->command("drop " + wep_name);

    if (!rtime) rtime = 10;
    call_out("get_wep_again", rtime);
}

void
do_disarm()
{
    if (!random(2))
      wep = (object)victim->query_weapon(W_RIGHT);
    else
      wep = (object)victim->query_weapon(W_LEFT);
    if (!objectp(wep))
    {
        wep = (object)victim->query_weapon(W_RIGHT);
    }
    if (!objectp(wep))
    {
        wep = (object)victim->query_weapon(W_LEFT);
    }
    if (!objectp(wep))
    {
        wep = (object)victim->query_weapon(W_BOTH);
    }
    if (!objectp(wep))
    {
        if (objectp(brawler))
        {
            brawler->catch_msg("Too late you realize that " + QTNAME(victim) +
                " does not wield a weapon!\n");
        }
        call_out("remove_object", 1);
        return;
    }

    FIX_EUID;

    wep_name = "weapon_" + OB_NUM(wep);
    if (!wep->id(wep_name))
        wep->add_name(wep_name); 

    victim->command("unwield " + wep_name);

    if (test_successful())
    {
        complete_disarm();
    }
    else 
    {
        if (!rtime)
            rtime = 10;
        call_out("wield_wep_again", rtime);
    }
}

void
wield_wep_again()
{
    if ((!objectp(victim)) || (victim->query_ghost()) || (!living(victim)))
    {
         return;
    }
    if (wait) return;

    TELL_ROOM(ENV(victim), victim, " manages to wield " +
        POSSESSIVE(victim) + " weapon again!", victim);

    set_this_player(victim);

    FIX_EUID;

  can_wield = 1;
    victim->command("wield " + wep_name);
/*
*/

    if (seen && !victim->query_attack())
    {
        victim->add_prop(LIVE_O_LAST_KILL, brawler);
        victim->command("kill " + brawler->query_real_name());
    }

    call_out("remove_object", 1);
}

void
get_wep_again()
{
    if ((!objectp(victim)) || (victim->query_ghost()) || (!living(victim)))
    {
        return;
    }

    FIX_EUID;

  can_wield = 1;
    victim->command("take " + wep_name);
    victim->command("wield " + wep_name);

    if (ENV(wep) != victim)
    {
        TELL_ROOM(ENV(victim), victim, " growls furiously as " +
            PRONOUN(victim) + " cannot find " + POSSESSIVE(victim)+
            " weapon again! " + CAP(PRONOUN(victim)) + " seems to have lost " +
            "interest in fighting." , victim);

        victim->command("growl");
        victim->command("get weapon");
        victim->command("wield all");
        victim->run_away();
    }
    else if (seen && !victim->query_attack())
    {
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
    call_out("do_disarm", 3);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (find_call_out("get_wep_again") != -1)
    {
      can_wield = 1;
        get_wep_again();
    }

    if (find_call_out("wield_wep_again") != -1)
    {
      can_wield = 1;
        wield_wep_again();
    }
}

no_wield()
{
  if (can_wield) return 0;
  write("No, your hand still hurts too much from the blow!\n");
  return 1;
}

no_take()
{
  if (can_wield) return 0;
  write("No, your hand still hurts too much from the disarming blow!\n");
  return 1;
}

init()
{
  ::init();
  add_action("no_wield","wield");
  add_action("no_take","take");
  add_action("no_take","get");
  add_action("no_take","give");
  add_action("no_take","pick");
}

query_twohanded() { return twohanded; }
