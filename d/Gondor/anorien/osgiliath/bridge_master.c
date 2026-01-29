/*
 *	/d/Gondor/anorien/osgiliath/bridge_master.c
 *
 *      This room is not in use at present, but should be left in
 *      place since several workrooms have exits to here.
 *
 *	This file steers the fight for Osgiliath.
 *
 *	Outline:
 *	Starting on June 20th, 3018, the Morgul army attacks Osgiliath.
 *	The objective is to take the city, to secure the bridge, and
 *	to form a bridge-head on the west bank of the Anduin.
 *
 *	The Gondorian forces start in defensive positions on the east
 *	bank. If they have to retire beyond the Anduin, they have to
 *	destroy the bridge to prevent the Morgul army of following them
 *	and forming a bridge-head on the west bank.
 *
 *	In the standard scenario, the Morgul army overruns the
 *	defensive positions of the Gondorian army on the east bank,
 *	the Gondorian forces retreat back over the Anduin and succeed
 *	in destroying the bridge.
 *
 *	In the 'Morgul' scenario, the Morgul army overruns the Gondorian
 *	forces on the east bank and manages to secure both the bridge
 *	and a bridge-head on the west bank.
 *
 *	In this scenario, it is now a quest to destroy the bridge.
 *	Once the bridge has been destroyed, the forces of the Morgul
 *	army holding the bridge-head will not receive any reinforcements
 *	from the east bank any more. Technically, this will mean that
 *	on reset, they will not be recloned.
 *
 *	In the 'Gondor' scenarion, the Gondorian forces succeed in
 *	holding their positions on the east bank.
 *
 *	In this scenarion the attack will be resumed within 7 days.
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"
#include "/d/Gondor/anorien/osgiliath/bridge.h"

#define SAVE			"/d/Gondor/anorien/osgiliath/bridge"
#define ATTACK_THRESHOLD	50


int     Bridge_State,
        Attack_Wave;

static  int     Attack_Alarm,
                Attack_Stage,
                Attack_Success;

private int
set_bridge_state(int i, int decrease = 0)
{
     if ((i > Bridge_State) || decrease)
     {
         Bridge_State = i;
         log_file("osgiliath", "Bridge state changed to "
           + Bridge_State + ". "+ctime(time())+"\n");
         save_object(SAVE);
         return Bridge_State;
     }
     return 0;
}

private int
reset_bridge_state()
{
    if (find_object(CLOCK)->query_rq_stage() == 0)
    {
        Bridge_State = 0;
        Attack_Wave  = 0;
        save_object(SAVE);
        return 1;
    }
    return 0;
}

public void
create_room()
{
    set_short("the master room controlling the Battle for Osgiliath");
    set_long("@@long_desc@@");

    add_exit(ANO_DIR + "osgiliath/wbridge1",    "west", 0, 0);
    add_exit(ITH_DIR + "osgiliath/eosgbridge",  "east", 0, 0);
    add_exit(GONDOR_DIR + "workroom", "gondor", 0, 0);
    add_exit(MORGUL_DIR + "blackrider", "nazgul", 0, 0);

    restore_object(SAVE);
    // Frequent resets.
    enable_reset(200);

    add_item(({"clock", "time", }), VBFC_ME("exa_clock"));
}

/*
 * Function name: exa_clock
 * Description:   VBFC for the description of the clock in this room.
 * Returns:       the description
 */
string
exa_clock()
{
    return RING_QUEST_MASTER->exa_clock();
}

public void
remove_object()
{
    save_object(SAVE);

    ::remove_object();
}

private int
check_bridge_state()
{
    object  clock = find_object(CLOCK);
    int     rq_stage = clock->query_rq_stage();

    if ((Bridge_State == OSG_BRIDGE_NO_ATTACK) &&
        (rq_stage >= RQ_OSGILIATH_ATTACK))
        set_bridge_state(OSG_BRIDGE_ATTACK_IMMINENT);

    return Bridge_State;
}

public int
query_bridge_state()
{
    check_bridge_state();
    return Bridge_State;
}

public string
long_desc()
{
    string  desc =
        "This is the master room controlling the Battle for Osgiliath. "
      + "A clock on the wall shows the time and Middle Earth.";

    switch (query_bridge_state())
    {
    case OSG_BRIDGE_NO_ATTACK:
        desc += " The bridge crossing the Anduin has not been destroyed yet. "
             +  "The army of Gondor is still holding a bridge-head on the "
             +  "east bank. There have been no attacks on Osgiliath yet.";
        break;
    case OSG_BRIDGE_ATTACK_IMMINENT:
        desc += " The bridge crossing the Anduin has not been destroyed yet. "
             +  "The army of Gondor is still holding a bridge-head on the "
             +  "east bank. The Morgul army is preparing the first attack "
             +  "on Osgiliath.";
        break;
    case OSG_BRIDGE_ATTACK:
        desc += " The bridge crossing the Anduin has not been destroyed yet. "
             +  "Osgiliath is presently under attack by the Morgul army. "
             +  "The attack is advancing ";
        if (Attack_Success > ATTACK_THRESHOLD)
            desc += "better than";
        else if (Attack_Success < -ATTACK_THRESHOLD)
            desc += "worse than";
        else
            desc += "as";
        desc += "expected.";
        break;
    case OSG_BRIDGE_GONDOR_HEAD:
        desc += " The bridge crossing the Anduin has not been destroyed yet. "
             +  "The army of Gondor is still holding a bridge-head on the "
             +  "east bank. There "
             +  ((Attack_Wave == 1) ? "has been one attack " :
                "have been "+LANG_WNUM(Attack_Wave)+" attacks ")
             +  "on Osgiliath already.";
        break;
    case OSG_BRIDGE_MORGUL_HEAD:
        desc += " The bridge crossing the Anduin has not been destroyed yet. "
             +  "The Morgul army is holding a bridge-head on the west bank. "
             +  "The army of Gondor is trying to destroy the bridge.";
        break;
    case OSG_BRIDGE_BRIDGE_BROKEN:
        desc += " The bridge crossing the Anduin has been destroyed.";
        break;
    }

    return BSN(desc);
}

/*
 * Function name: attack_action
 * Description:   handles the attack
 */
public void
attack_action()
{
    if (Attack_Stage >= 999)
    {
        remove_alarm(Attack_Alarm);

        if (Attack_Success > ATTACK_THRESHOLD)
            set_bridge_state(OSG_BRIDGE_MORGUL_HEAD);
        else if (Attack_Success < -ATTACK_THRESHOLD)
            set_bridge_state(OSG_BRIDGE_GONDOR_HEAD);
        else
            set_bridge_state(OSG_BRIDGE_BRIDGE_BROKEN);

        log_file("osgiliath", "Attack ended. Result: "
          + Attack_Success + ". "+ctime(time())+"\n");
        Attack_Alarm = 0;
        Attack_Stage = 0;
        Attack_Success = 0;
    }

    switch (Attack_Stage++)
    {
    case 0:
        break;
    case 1:
        Attack_Stage = 999;
        break;
    }
}

/*
 * Function name: start_attack
 * Description:   start an attack of the Morgul army on Osgiliath
 */
private void
start_attack()
{
    // We don't want to have two attacks at the same time!
    if (Attack_Alarm && sizeof(get_alarm(Attack_Alarm)))
    {
        log_file("osgiliath", "ERROR: Attempt to start second attack! "
          + ctime(time()) + "\n");
        return;
    }

    log_file("osgiliath", "Attack started! Old state: "
      + Bridge_State + ". "+ctime(time())+"\n");
    Attack_Stage = 0;
    Attack_Success = 0;
    Attack_Wave++;
    Attack_Alarm = set_alarm(30.0, 30.0, attack_action);

    // This is the only situation except for reset where we may
    // decrease the value of Bridge_State!
    set_bridge_state(OSG_BRIDGE_ATTACK, 1);
}

public void
reset_room()
{
    switch (query_bridge_state())
    {
    case OSG_BRIDGE_ATTACK_IMMINENT:
        start_attack();
        break;
    case OSG_BRIDGE_GONDOR_HEAD:
        if (!random(5))
            start_attack();
        break;
    }
}

/*
			OSG_BRIDGE_NO_ATTACK
				|
			if rq_stage >= RQ_OSGILIATH_ATTACK
				|
				V
			OSG_BRIDGE_ATTACK_IMMINENT
				|
			on next reset
				|
				V
			OSG_BRIDGE_ATTACK
	________________________|________________________
	|			|			|
	V			V			V
OSG_BRIDGE_GONDOR_HEAD	OSG_BRIDGE_BRIDGE_BROKEN  OSG_BRIDGE_MORGUL_HEAD
        |			|			|
        V			|			V
OSG_BRIDGE_ATTACK		|		Quest to destroy the
        |			|		bridge active
        V			|			|
    see above			|			V
         			|		OSG_BRIDGE_BRIDGE_BROKEN
         			V
         		static until reset

 */
