/*
 * /d/Gondor/guilds/rangers/obj/disarm_ob.c
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
 * Olorin, 22-Feb-1997: Changed test_successful to use of resolve_task().
 * /Gwyneth, 6 May 2004, changed commands for wield, unwield and kill
 *                       to the actual calls: command_wield(),
 *                       command_unwield, attack_object().
 * Tigerlily, July 5, 2004--fixed bug, added 309
 * Tigerlily, March 9, 2005-fixed typo using TELL_ROOM function, took out
 * Tigerlily, June 2006--correct problem of 'attacking' when ranger not 
 *                       in room, causing an error 
 */
inherit "/std/object.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define RANGER_I_NO_DISARM_DROP     "_ranger_m_no_disarm_drop"
#define SUCCESS_FUNCTION            (40 + random(30))

int     gRtime,
        gTwoHanded,
        gSeen = 0,
        gCanWield = 0,
        gWieldAgainAlarm = 0,
        gGetWepAlarm = 0;
object  gVictimWep,
        gBrawler,
        gVictim;

/* Prototypes */
public void    do_disarm();
public void    wield_weapon_again();
public void    get_weapon_again();

public void
create_object()
{
    set_name("Ranger_Disarm_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

public void
set_time(int i)
{
    gRtime = i;
}

public void
set_seen()
{
    gSeen = 1;
}

public void
set_brawler(object ob)
{
    gBrawler = ob;
}

private int
test_successful()
{
    if (!objectp(gBrawler) || !objectp(gVictim))
        return 0;

    return gBrawler->resolve_task(TASK_ROUTINE + 150, 
        ({ SS_BRAWLING, TS_STR, }), gVictim, ({ SS_PARRY, TS_STR }) );
}

public void
complete_disarm()
{
    if (gVictim->query_prop(RANGER_I_NO_DISARM_DROP))
        return;

    if (gVictimWep->query_hands() == W_BOTH)
    {
        if (!gTwoHanded)
        {
            gBrawler->catch_tell("Your blow was so successful that " +
                gVictim->query_the_name(gBrawler) + " loses " +
                POSSESSIVE(gVictim) + " grip on " + POSSESSIVE(gVictim) +
                " weapon with " + POSSESSIVE(gVictim) + " right hand. " +
                CAP(PRONOUN(gVictim)) + " is able to hold the weapon in " +
                POSSESSIVE(gVictim) + " left hand though.\n");
            gVictim->catch_tell("The blow on your right hand was so hard " +
                "that your hand loses its grip on the weapon completely. " +
                "You manage to hold it in your left hand though. You " +
                "cannot do any harm to an opponent now, for you need to " +
                "wield it in both hands.\n");
            tell_room(ENV(gVictim), "The blow on " + POSSESSIVE(gVictim) +
                " hand causes " + QTNAME(gVictim) + " to completely lose " +
                POSSESSIVE(gVictim) + " grip on the weapon with " +
                POSSESSIVE(gVictim) + " right hand. " + 
                CAP(PRONOUN(gVictim)) + " manages to hold the weapon with " + 
                POSSESSIVE(gVictim) + " left hand though.\n", 
                ({ gBrawler, gVictim }) );
            if (gVictim->query_npc())
                gVictim->command("emote roars with rage!");
            if (present(gBrawler, environment(gVictim)) && gVictim->query_npc())
                gVictim->command("$kill " + gBrawler->query_real_name());
            if (!gRtime)
                gRtime = 10;

            gWieldAgainAlarm = set_alarm(itof(gRtime), 0.0, wield_weapon_again);
            gTwoHanded = 1;
            return;
        }
        else
        {
            gBrawler->catch_tell("Your disarming strike hit the left hand " +
                "of " + gVictim->query_the_name(gBrawler) +
                ", so that " + PRONOUN(gVictim) +
                " loses the weapon completely!\n");
            gVictim->catch_tell("Another blow, this time to your left hand, " +
                "causes you to lose your hold on the weapon completely!\n");
            tell_room(ENV(gVictim), "The blow on " + POSSESSIVE(gVictim) +
                " other hand causes " + QTNAME(gVictim) + " to lose " +
                POSSESSIVE(gVictim) + " weapon completely!\n",
                ({ gBrawler, gVictim }));
            gTwoHanded = 0;
        }
    }
    else
    {
        gBrawler->catch_tell("Your blow was so successful that " +
            gVictim->query_the_name(gBrawler) +
            " loses the weapon completely!\n");
        tell_room(ENV(gVictim), "The blow on " + POSSESSIVE(gVictim) +
            " hand causes " + QTNAME(gVictim) + " to drop " +
            POSSESSIVE(gVictim) + " weapon completely!\n",
            ({ gBrawler, gVictim }) );
        gVictim->catch_tell("The blow to your hand was so hard that you " +
            "drop your weapon!\n");
    }

    FIX_EUID;

    gVictim->command("$drop " + OB_NAME(gVictimWep));
    if (remove_alarm(gWieldAgainAlarm))
        gWieldAgainAlarm = 0;

    if (!gRtime) 
        gRtime = 10;

    gGetWepAlarm = set_alarm(itof(gRtime), 0.0, get_weapon_again);
}

public void
do_disarm()
{
    int s;
    object *mwep;
    string wep_name;

    if (!objectp(gVictim))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    mwep = gVictim->query_weapon(-1);

    s = sizeof(mwep);
    if (s == 1)
        gVictimWep = mwep[0];
    else if (s > 1)
        gVictimWep = mwep[random(s)];

    if (!s || !objectp(gVictimWep))
    {
        if (objectp(gBrawler) && !interactive(gBrawler))
        {
            gBrawler->catch_tell("Too late you realize that " + 
                gVictim->query_the_name(gBrawler) +
                " does not wield a weapon!\n");
            set_alarm(1.0, 0.0, remove_object);
            return;
        }
        else if (objectp(gBrawler))
        {
            if (!gRtime)
                gRtime = 10;

            gWieldAgainAlarm = set_alarm(itof(gRtime), 0.0, wield_weapon_again);
            return;
        }
        else
        {
            set_alarm(1.0, 0.0, remove_object);
            return;
        }
    }

    gVictimWep->command_unwield();

    if ((test_successful() >= 1) && 
      !gVictim->query_prop(RANGER_I_NO_DISARM_DROP))
    {
        complete_disarm();
    }
    else 
    {
        if (!gRtime)
            gRtime = 10;

        gWieldAgainAlarm = set_alarm(itof(gRtime), 0.0, wield_weapon_again);
    }
}

public void
wield_weapon_again()
{
    object  t_wep;
    string  wep_name;

    remove_alarm(gWieldAgainAlarm);
    gWieldAgainAlarm = 0;

    if (!objectp(gVictim) || gVictim->query_ghost() ||
      !living(gVictim) || !objectp(gVictimWep) || 
      (ENV(gVictimWep) != gVictim))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    FIX_EUID;
    set_this_player(gVictim);

    gCanWield = 1;
    /* If the victim is a player, we let them decide when to try to
     * rewield their weapon themselves, whereas npcs will be 'helped'
     */
    if (interactive(gVictim))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }
    gVictim->command("get weapon");
    gVictim->command("$wield " + OB_NAME(gVictimWep));

    /* This will fail if the victim cannot see the weapon because he */
    /* has been blinded: LIVE_I_SEE_INVIS == -1 */
    if (gVictimWep->query_wielded() != gVictim)
    {
        /* wield attempt failed! */
        tell_room(ENV(gVictim), QCTNAME(gVictim) + " tries to wield " +
            POSSESSIVE(gVictim) + " weapon again, but fails!\n", gVictim);

        /* Do not remove this object. */
        /* wield_weapon_after_blinded() will be called from Ranger */
        /* blind_ob! */
        gWieldAgainAlarm = set_alarm(120.0, 0.0, wield_weapon_again);
        return;
    }

    tell_room(ENV(gVictim), QCTNAME(gVictim) + " manages to wield " +
        POSSESSIVE(gVictim) + " weapon again!\n", gVictim);

/* remove--'ranger's rescue' bug--also re check for presence
  and let npc figure out when to attack again
    if (gSeen && !objectp(gVictim->query_attack()))
        gBrawler->attack_object(gVictim);
*/
    if (present(gBrawler, environment(gVictim)) && gVictim->query_npc())
    {
        gBrawler->reveal_me(1);
        gVictim->command("$kill " + gBrawler->query_real_name());
    }

    set_alarm(1.0, 0.0, remove_object);
}

public void
get_weapon_again()
{
    string  wep_name;

    remove_alarm(gGetWepAlarm);
    gGetWepAlarm = 0;

    if (!objectp(gVictim) || gVictim->query_ghost() ||
      !living(gVictim) || !objectp(gVictimWep))
    {
    //the remove_object alarm was missing--I added again--TL-July, 2004
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    gCanWield = 1;
    /* If the victim is a player, we let them choose what to do */
    /* themselves now that the disarm-effect ends. */
    if (interactive(gVictim))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    wep_name = OB_NAME(gVictimWep);
    gVictim->command("take " + wep_name);
    gVictim->command("wield " + wep_name);

    if ((ENV(gVictimWep) != gVictim))
    {
        if (objectp(gVictim->query_attack()))
        {
            tell_room(ENV(gVictim), QCTNAME(gVictim) + " growls furiously " +
                "as " + PRONOUN(gVictim) + " cannot find " +
                POSSESSIVE(gVictim) + " weapon again!\n", gVictim);

            gVictim->command("$get weapons");
            gVictim->command("$wield all");
        }
    }
    else if (gVictimWep->query_wielded() != gVictim)
    {
        /* wield attempt failed! */
        tell_room(ENV(gVictim), QCTNAME(gVictim) + " tries to wield " +
            POSSESSIVE(gVictim) + " weapon again, but fails!\n", gVictim); 
        /* Do not remove this object. */
        /* wield_weapon_after_blinded() will be called from blind_ob! */
        gWieldAgainAlarm = set_alarm(30.0, 0.0, wield_weapon_again);
        return;
    }
/* Let npc figure out when to attack again
    else if (gSeen && !objectp(gVictim->query_attack()))
    {
        gVictim->attack_object(gBrawler);
        gVictim->add_prop(LIVE_O_LAST_KILL, gBrawler);
    }
*/
    if (present(gBrawler, environment(gVictim)) && gVictim->query_npc())
    {
        gBrawler->reveal_me(1);
        gVictim->command("$kill " + gBrawler->query_real_name());
    }

    set_alarm(1.0, 0.0, remove_object);
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    if (!living(to))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    gVictim = to;
    set_alarm(0.5, 0.0, do_disarm);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (gGetWepAlarm)
    {
        gCanWield = 1;
        get_weapon_again();
    }

    if (gWieldAgainAlarm)
    {
        gCanWield = 1;
        wield_weapon_again();
    }
}

int
no_wield()
{
    if (gCanWield)
        return 0;

    write("No, your hand still hurts too much from the blow!\n");
    return 1;
}

int
no_take()
{
    if (gCanWield)
        return 0;

    write("No, your hand still hurts too much from the disarming blow!\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(no_wield, "wield");
    add_action(no_wield, "draw");
    add_action(no_wield, "mdraw");
    add_action(no_take,  "take");
    add_action(no_take,  "get");
    add_action(no_take,  "give");
    add_action(no_take,  "pick");
    add_action(no_take,  "steal");
    add_action(no_take,  "borrow");
}

public int
query_two_handed()
{
    return gTwoHanded;
}

/*
 * Function name: wield_weapon_after_blinded
 * Description  : Called from the Ranger blind_ob to make npcs rewield
 *                their weapons if the rewield attempt failed because
 *                they were blinded.
 */
public void
wield_weapon_after_blinded()
{
    if (!gCanWield)
        return;

    if (gGetWepAlarm)
        get_weapon_again();

    if (gWieldAgainAlarm)
        wield_weapon_again();
}

