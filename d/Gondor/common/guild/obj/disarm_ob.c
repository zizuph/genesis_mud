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
 * Olorin, 22-Feb-1997: Changed test_successful to use of resolve_task().
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define RANGER_I_NO_DISARM_DROP    "_ranger_m_no_disarm_drop"
#define SUCCESS_FUNCTION (40 + random(30))

int     rtime,
        Two_Handed,
        Seen = 0,
        Can_Wield = 0,
        wwa_aid = 0,
        gwa_aid = 0;
object  Victim_Wep,
        brawler,
        victim;

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
    rtime = i;
}

public void
set_seen()
{
    Seen = 1;
}

public void
set_brawler(object ob)
{
    brawler = ob;
}

private int
test_successful()
{
    if (!objectp(brawler) || !objectp(victim))
        return 0;

    return brawler->resolve_task(TASK_ROUTINE + 150, 
				 ({ SS_BRAWLING, TS_STR, }), 
				 victim, ({ SS_PARRY, TS_STR }) );
}

public void
complete_disarm()
{
    if (victim->query_prop(RANGER_I_NO_DISARM_DROP))
        return;
    if (Victim_Wep->query_hands() == W_BOTH)
    {
	if (!Two_Handed)
	{
	    brawler->LCATCH_MSG("Your blow was so successful that ", 
		" loses grip on " + POSSESSIVE(victim) + " weapon with " +
                POSSESSIVE(victim) + " right hand. " + CAP(PRONOUN(victim)) +
                " is able to hold the weapon in " + POSSESSIVE(victim) +
                " left hand though.", victim);
	    victim->catch_msg(BSN("The blow on your right hand was so hard that " +
                "your hand loses its grip on the weapon completely. You manage " +
                "to hold it in your left hand though. You cannot do any harm to " +
                "an opponent now, for you need to wield it in both hands."));
	    tell_room(ENV(victim), "The blow on the hand causes " +
                QTNAME(victim) + " to completely lose grip of the weapon with " +
                POSSESSIVE(victim) + " right hand. " + CAP(PRONOUN(victim)) +
                " manages to hold the weapon with " + POSSESSIVE(victim) +
                " left hand though.\n", ({ brawler, victim }) );

	    if (!rtime)
		rtime = 10;
	    wwa_aid = set_alarm(itof(rtime), 0.0, wield_weapon_again);
	    Two_Handed = 1;
	    return;
	}
	else
	{
	    brawler->LCATCH_MSG("Your disarming strike hit the left hand of ",
	        ", so that "+PRONOUN(victim)+" loses the weapon completely!",victim);
	    victim->catch_msg(BSN("Another blow, this time to your left hand, "+
                "causes you to lose your hold on the weapon completely!"));
	    tell_room(ENV(victim), "The blow on the other hand causes "
                + QTNAME(victim) + " to lose "+POSSESSIVE(victim) 
                + " weapon completely!\n", ({ brawler, victim }));
	    Two_Handed = 0;
	}
    }
    else
    {
	brawler->LCATCH_MSG("Your blow was so successful that ", " loses the " +
            "weapon completely!", victim);
	tell_room(ENV(victim), "The blow on the hand causes " + QTNAME(victim) +
            " to drop " + POSSESSIVE(victim) + " weapon completely!\n",
            ({ brawler, victim }) );
	victim->catch_msg(BSN("The blow to your hand was so hard that you drop " +
            "your weapon!"));
    }

    FIX_EUID;
    victim->command("$drop " + OB_NAME(Victim_Wep));
    if (remove_alarm(wwa_aid))
	wwa_aid = 0;
    if (!rtime) 
	rtime = 10;
    gwa_aid = set_alarm(itof(rtime), 0.0, get_weapon_again);
}

public void
do_disarm()
{
    int     s;
    object *mwep;
    string  wep_name;

    if (!objectp(victim))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    mwep = victim->query_weapon(-1);

    if ((s = sizeof(mwep)) == 1)
	Victim_Wep = mwep[0];
    else if (s > 1)
	Victim_Wep = mwep[random(s)];

    if (!s || !objectp(Victim_Wep))
    {
        if (objectp(brawler) && !interactive(brawler))
        {
            brawler->catch_msg("Too late you realize that " + QTNAME(victim) +
			       " does not wield a weapon!\n");
            set_alarm(1.0, 0.0, remove_object);
            return;
        }
        else if (objectp(brawler))
        {
            if (!rtime)
                rtime = 10;
            wwa_aid = set_alarm(itof(rtime), 0.0, wield_weapon_again);
            return;
        }
        else
        {
            set_alarm(1.0, 0.0, remove_object);
            return;
        }
    }

    wep_name = OB_NAME(Victim_Wep);
    if (!Victim_Wep->id(wep_name))
        Victim_Wep->add_name(wep_name); 

/*
        if (Victim_Wep->id("sceptre"))
            victim->command("$ungrip sceptre");
*/

    victim->command("$unwield " + wep_name);

    if ((test_successful() >= 1) && !victim->query_prop(RANGER_I_NO_DISARM_DROP))
    {
        complete_disarm();
    }
    else 
    {
        if (!rtime)
            rtime = 10;
        wwa_aid = set_alarm(itof(rtime), 0.0, wield_weapon_again);
    }
}

public void
wield_weapon_again()
{
    object  t_wep;
    string  wep_name;

    remove_alarm(wwa_aid);
    wwa_aid = 0;

    if (!objectp(victim) || victim->query_ghost() ||
	!living(victim) || !objectp(Victim_Wep) || 
	(ENV(Victim_Wep) != victim))
    {
	set_alarm(1.0, 0.0, remove_object);
	return;
    }

    wep_name = OB_NAME(Victim_Wep);

    FIX_EUID;
    set_this_player(victim);

    Can_Wield = 1;
    /* If the victim is a player, we let them decide when to try to
     * rewield their weapon themselves, whereas npcs will be 'helped'
     */
    if (interactive(victim))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }
    // This will fail if the victim cannot see the weapon because he
    // has been blinded: LIVE_I_SEE_INVIS == -1
    victim->command("wield " + wep_name);
    if (Victim_Wep->query_wielded() != victim)
    {
	// wield attempt failed!
	TELL_ROOM(ENV(victim), victim, " tries to wield " +
		  POSSESSIVE(victim) + " weapon again, but fails!",
		  victim); 
	// Do not remove this object.
	// wield_weapon_after_blinded() will be called from Ranger
	// blind_ob! 
        wwa_aid = set_alarm(120.0, 0.0, wield_weapon_again);
	return;
    }

    TELL_ROOM(ENV(victim), victim, " manages to wield " +
        POSSESSIVE(victim) + " weapon again!", victim);

    if (Seen && !objectp(victim->query_attack()))
    {
        brawler->attack_object(victim);
    }

    set_alarm(1.0, 0.0, remove_object);
}

public void
get_weapon_again()
{
    string  wep_name;

    remove_alarm(gwa_aid);
    gwa_aid = 0;

    if (!objectp(victim) || victim->query_ghost() ||
	!living(victim) || !objectp(Victim_Wep))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    Can_Wield = 1;
    /* If the victim is a player, we let them choose what to do
     * themselves now that the disarm-effect ends.
     */
    if (interactive(victim))
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    wep_name = OB_NAME(Victim_Wep);
    victim->command("take " + wep_name);
    victim->command("wield " + wep_name);

    if ((ENV(Victim_Wep) != victim))
    {
	if (objectp(victim->query_attack()))
	{
            TELL_ROOM(ENV(victim), victim, " growls furiously as " +
        	PRONOUN(victim) + " cannot find " + POSSESSIVE(victim)+
          " weapon again!", victim);

            victim->command("get weapons");
            victim->command("wield all");
	}
    }
    else if (Victim_Wep->query_wielded() != victim)
    {
	// wield attempt failed!
	TELL_ROOM(ENV(victim), victim, " tries to wield " +
		  POSSESSIVE(victim) + " weapon again, but fails!",
		  victim); 
	// Do not remove this object.
	// wield_weapon_after_blinded() will be called from Ranger
	// blind_ob! 
        wwa_aid = set_alarm(30.0, 0.0, wield_weapon_again);
	return;
    }
    else if (Seen && !objectp(victim->query_attack()))
    {
        victim->add_prop(LIVE_O_LAST_KILL, brawler);
        victim->command("$kill " + OB_NAME(brawler));
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

    victim = to;
    set_alarm(0.5, 0.0, do_disarm);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (gwa_aid)
    {
        Can_Wield = 1;
        get_weapon_again();
    }

    if (wwa_aid)
    {
        Can_Wield = 1;
        wield_weapon_again();
    }
}

int
no_wield()
{
    if (Can_Wield)
        return 0;
    write("No, your hand still hurts too much from the blow!\n");
    return 1;
}

int
no_take()
{
    if (Can_Wield)
        return 0;
    write("No, your hand still hurts too much from the disarming blow!\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(no_wield, "wield");
    add_action(no_wield, "mdraw");
    add_action(no_wield, "draw");
    add_action(no_wield, "grip");
    add_action(no_take,  "take");
    add_action(no_take,  "get");
    add_action(no_take,  "give");
    add_action(no_take, "pick");
    add_action(no_take, "steal");
}

public int     query_two_handed() { return Two_Handed; }

/*
 * Function name: wield_weapon_after_blinded
 * Description:   Called from the Ranger blind_ob to make npcs rewield
 *                their weapons if the rewield attempt failed because
 *                they were blinded.
 */
public void
wield_weapon_after_blinded()
{
    if (!Can_Wield)
	return;

    if (gwa_aid)
	get_weapon_again();
    if (wwa_aid)
	wield_weapon_again();
}

