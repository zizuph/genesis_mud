/*
Boromir Feb 95
*/

/* This file is /d/Gondor/minas/npc/std_gondor_guard.c */
/*                                                     */
/* some routines follow /doc/examples/mobiles/troll.c  */
/*                                                     */
/* Borrowed from /d/Gondor/morgul/npc/ithil_monster,   */
/* By Olorin 14-july-93                                */
/* This file stolen by Dunstable, Mar 94               */
/* Modified significantly by Auberon, Dec. '00         */

/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above regardless of any policy to the contrary.
 */

#include "/d/Gondor/defs.h"
inherit "/std/monster";
inherit LIB_DIR + "logkill.c";
inherit LIB_DIR + "make_money.c";

#include <composite.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../locals.h"
#include "attackers.c"

#define BOOZE	(RANGER_DIR + "obj/wine")

string alignlook();

int     attack_alarm = 0;
int     officer = 0;  /* man not officer */
int		hf_aid;

void 
create_monster()
{
    int rnd;
    seteuid(getuid(TO));

    add_name("_thornlin_mili");
    set_name(({"man", "guard", }));
    set_short("militia man");
    set_pshort("militia men");
    set_pname(({"men", "guards", "militia men"}));
    set_adj("brown-skinned");
    add_adj(alignlook());
    add_adj("militia");
    set_race_name("human");
    rnd = random(10);
    set_stats(({ 110+rnd,140+rnd,120+rnd,95,95,90+rnd }));
    add_prop("_live_m_attack_thief", 1);
    set_whimpy(35+rnd);

    set_skill(SS_WEP_POLEARM, 50);

    set_skill(SS_AWARENESS,   50);
    set_skill(SS_HIDE,        25);
    set_skill(SS_DEFENCE,     50);
    set_skill(SS_PARRY,       50);
    set_skill(SS_APPR_MON,     50);

    add_prop(LIVE_I_NEVERKNOWN,1);
    set_alignment(300 + random(100));
    set_intoxicated(intoxicated_max()/2);

    set_act_time(2);
    add_act("@@get_booze@@");
    add_act("hide me");
    add_act("reveal all");

    get_money();
}

public void
arm_me()
{
    object arm,wep,wep2;
    seteuid(getuid(TO));
    wep = clone_object(THORN_DIR + "obj/spear");
    wep->move(TO);
    command("wield all");
    arm = clone_object(THORN_DIR + "obj/shield");
    arm->move(TO);
    arm = clone_object(THORN_DIR + "obj/cloak");
    arm->move(TO);
    arm = clone_object(THORN_DIR + "obj/hauberk");
    arm->move(TO);
    arm = clone_object(THORN_DIR + "obj/gauntlets");
    arm->move(TO);
    command("wear all");
}

int thornlin_guard_filter(object guard) { return (guard->id("_thornlin_mili")); }

void
call_for_friends(object ob)
{
    int     i;
    object  room = ENV(TO),
    *arr = all_inventory(room);

    arr = filter(arr,"thornlin_guard_filter",TO);
    for (i = 0; i < sizeof(arr); i++)
	arr[i]->notify_ob_attacked_me(TO,ob);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    call_for_friends(ob);
}

int query_not_attack_me(object att, int att_id)
{
    if (!random(10))
	call_for_friends(att);
    if (att->query_average_stat() > 70 && !random(10)) {
	command("shout Gather up and HELP!");
    }
    return 0;
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (objectp(query_attack())) return;
    set_alarm(1.0 + 3.0*rnd(), 0.0, "help_friend", attacker, friend);
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object attacker, object friend)
{
    if (objectp(attacker) && !objectp(query_attack()) &&
      present(attacker, ENV(TO)) && CAN_SEE_IN_ROOM(TO) &&
      CAN_SEE(TO, attacker))
    {
	if (!random(4))
	    command("shout Attacking us, are we foul "
	      + attacker->query_race_name() + "!?!?");
	if (!sizeof(get_alarm(attack_alarm)))
	    attack_alarm = set_alarm(1.0 + 3.0*rnd(), 0.0, "do_attack", attacker);
    }
}

void
do_attack(object victim)
{
    if (sizeof(get_alarm(attack_alarm)))
	remove_alarm(attack_alarm);
    attack_alarm = 0;

    if (objectp(query_attack()))
	return;
    if (victim->query_npc())
	return;
    if (!present(victim, ENV(TO)) || !CAN_SEE_IN_ROOM(TO) ||
      !CAN_SEE(TO, victim))
    {
	command("peer suspiciously");
	return;
    }
    command("kill "+victim->query_real_name());
    if (!random(4))
	command("shout I will kill you, "+victim->query_race_name()
	  + ", murderer of women and children!");
}

string
alignlook() 
{
    return ONE_OF_LIST(
      ({"noble", "stern", "dark-haired", "scarred","battle-tested",
	"strong", "lean", "stout", "friendly", "aged", "tough"}));
}

public void
init_attack()
{
    if(query_attack())
	return;
}


void
order_attack_enemy(object commander, object victim)
{
    if (objectp(query_attack()))
	return;
    if (!sizeof(get_alarm(attack_alarm)))
	attack_alarm = set_alarm(1.0 + 3.0*rnd(), 0.0, "do_attack", victim);
}

int
query_knight_prestige() { return -80; }

public string
query_nonmet_name()
{
    return query_short();
}

string
get_booze()
{
    command("drink all");
    if (!present("wine", TO))
    {
	FIX_EUID
	clone_object(BOOZE)->move(TO);
    }
}


void
set_officer()
{
    officer = 1;  /* man officer */
}

/*
 * This is necessary for the line corpse->set_pshort("corpses of militia men");
 * as /std/corpse doesn't handle this properly due to the inability of LANG_PNAME
 * to convert "militia man" properly to the plural.
 */
public object
make_corpse()
{
    object  corpse;

    corpse = clone_object("/std/corpse");
    corpse->set_name(query_name());
    corpse->set_pname("corpses of " + query_pname());
    corpse->set_pshort("corpses of militia men");
    corpse->change_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
    corpse->change_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
    corpse->add_prop(CORPSE_S_RACE, query_race_name());
    corpse->add_prop(CONT_I_TRANSP, 1);
    corpse->change_prop(CONT_I_MAX_WEIGHT,
      query_prop(CONT_I_MAX_WEIGHT));
    corpse->change_prop(CONT_I_MAX_VOLUME,
      query_prop(CONT_I_MAX_VOLUME));
    corpse->set_leftover_list(query_leftover());

    return corpse;
}

