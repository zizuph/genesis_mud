// file name:        /d/Avenir/drow/npc/drider._std.c
// creator(s):       Nikklaus, March'97`
// revision history:
// purpose:          combat_extern for driders, should emulate humunarmed to
//                   some degree
// note:
// to-do:
// bug(s):
/*
 * Re-patriated code back to the Kalad domain.
 * Commented out Guild related code as it is never
 * returning to Kalad or Avenir.
 * 	- Lucius, June 2017
 */
# pragma strict_types
# pragma no_clone

#include "drider.h"
#include "/d/Kalad/defs.h"

inherit "/std/npc";
inherit "/std/combat/unarmed";

inherit "/std/act/action";
inherit "/std/act/asking";

#if 0
inherit "/std/act/domove";
inherit "/std/act/chat";
inherit "/std/act/ranpick";
inherit "/std/act/attack";
inherit "/std/act/add_things";
#endif

inherit CPASS(drow/npc/npc_std);

static int *
random_stat()
{
    int i;
    int *rndstat = allocate(6);

    for (i = 5; i >= 0 ; i--)
	rndstat[i] = 90 + random(60);
    return rndstat;
}

public void
create_drider()
{
}

public nomask void
create_npc()
{
    set_race_name("drow");
    add_name("drider");
    set_default_answer("You get no response from the drider.\n");
    set_extra_long("He has the jet-black skin of the Drow.\n");
    set_skill(SS_LANGUAGE, 80);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    seteuid(getuid());
    create_drider();
    guard_enable();
}

void
reset_drider() { }

nomask void
reset_monster()
{
    ::reset_npc();
    reset_drider();
}

public nomask void
create_greater_drider()
{
    add_prop(CONT_I_VOLUME, 164000);
    add_prop(CONT_I_WEIGHT, 207500);
    add_prop(LIVE_I_SEE_INVIS, 30);
    add_prop(LIVE_I_SEE_DARK, 2);
    set_drow_rank(4);
    add_prop(LIVE_I_QUICKNESS, 300);
    set_stats(({192, 200, 175, 90, 90, 200}));
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 90);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_alignment(-1000);
    set_knight_prestige(1000);

    cr_reset_attack(W_RIGHT);
    cr_reset_attack(W_LEFT);
    cr_reset_attack(W_FLEGS);
    cr_reset_attack(W_MLEGS);
    set_hitloc_unarmed(A_CARAPACE, ({100,150,75}), 22, "carapace");
    set_hitloc_unarmed(A_BODY, 1, 20, "torso");
    set_hitloc_unarmed(A_HEAD, 1, 8, "head");
    set_hitloc_unarmed(A_LEGS, ({70, 100, 50}), 42, "leg");
    set_hitloc_unarmed(A_R_ARM, 1, 8, "right arm");
    set_hitloc_unarmed(A_L_ARM, 1, 8, "left arm");
    set_short(this_object()->short() + " drider");
}

public nomask void
create_lesser_drider()
{
    add_prop(CONT_I_VOLUME, 123000);
    add_prop(CONT_I_WEIGHT, 346000);
    set_drow_rank(3);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(LIVE_I_SEE_INVIS, 10);
    add_prop(LIVE_I_SEE_DARK, 1);
    set_stats(random_stat());
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 70);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 100);
    set_alignment(-1000);
    set_knight_prestige(750);
    cr_reset_attack(W_RIGHT);
    cr_reset_attack(W_LEFT);
    cr_reset_attack(W_FOOTR);
    cr_reset_attack(W_FOOTL);
    set_short(this_object()->query_short()+ " drider");
}

public void
attack_object(object enemy)
{
    TO->command("emote screams: Dosst elghinn zhah usstan belbol lueth "+
	"ssinssrigg!");
    ::attack_object(enemy);

    if (npc_guard_enabled && !guarded_actions)
	TO->set_follow(enemy->query_real_name(), 1);
}

public string
query_combat_file()
{
    return "/std/combat/chumanoid";
}

#if 0
public void
do_die(object killer)
{
    drow_die(killer);
    ::do_die(killer);
}

/* Function name: adjust_combat_on_move
 * Description  : Someone just left combat. This sets an alarm that will check
 *                the remaining attackers.
 */
public void
adjust_combat_on_move(int move)
{
    ::adjust_combat_on_move();
    if (!ZHAH_DOEBLEND(TO))
	TO->check_attackers();
}
#endif

public void
init_living()
{
    ::init_living();
    init_std();
}

public nomask void
cr_reset_attack(int aid)
{
    int wchit, wcpen, uskill;
    mixed att;

    ::cr_reset_attack(aid);

    if (!sizeof(query_ua_attack(aid)))
    {
	wchit = W_HAND_HIT;
	wcpen = W_HAND_PEN;
	if (uskill = this_object()->query_skill(SS_UNARM_COMBAT))
	{
	    wchit += F_UNARMED_HIT(uskill, this_object()->query_stat(SS_DEX));
	    wcpen += F_UNARMED_PEN(uskill, this_object()->query_stat(SS_STR));
	}

	if (uskill < 1)
	    uskill = -1;

	switch(aid)
	{
	case W_RIGHT:
	    QEXC->cb_add_attack(wchit, wcpen, W_BLUDGEON, 25, aid, uskill + 6);
	    break;
	case W_LEFT:
	    QEXC->cb_add_attack(wchit, wcpen, W_BLUDGEON, 25, aid, uskill + 6);
	    break;
	case W_BOTH:
	    /*
	     * We use the hands separately in unarmed combat
	     */
	    QEXC->cb_add_attack(0, 0, W_BLUDGEON, 0, aid, uskill + 6);
	    break;
	case W_FOOTR:
	    QEXC->cb_add_attack(3 * wchit / 2, 3 * wcpen / 2,
	      (random(100)<80 ? W_BLUDGEON : W_IMPALE),
	      25, aid, uskill + 8);
	    break;
	case W_FOOTL:
	    QEXC->cb_add_attack(3 * wchit / 2, 3 * wcpen / 2,
	      (random(100)<80 ? W_BLUDGEON : W_IMPALE),
	      25, aid, uskill);
	default:
	    if (sizeof(att) >= 4)
		QEXC->cb_add_attack(att[0], att[1], att[2], att[3], aid);
	}
    }
}

/*
* Function name: cr_attack_desc
* Description:   Gives the description of a certain unarmed attack slot.
* Arguments:     aid:   The attack id
* Returns:       string holding description
*/
public nomask string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case W_RIGHT:return (random(100)<80 ? "right fist" : "right elbow");
    case W_LEFT:return (random(100)<80 ? "left fist" : "left elbow");
    case W_BOTH:return "joined hands";
    case W_FOOTR:
	return (random(100)<50 ? "right front leg" : "left front leg");
    case W_FOOTL:
	return (random(100)<50 ? "right middle leg" : "left middle leg");
    default:
	return "mind"; /* should never occur */
    }
}

int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;
    me = this_object();
    if(random(15))
	return 0;

    if (QEXC->cb_tohit(-1, TO->query_skill(SS_UNARM_COMBAT), enemy) < 1)
	return 0;
    hitresult = enemy->hit_me(300 + random(me->query_stat(SS_STR)), W_IMPALE, me, -1);
    switch (hitresult[0])
    {
    case 0..5:
	how = "";
	break;
    case 6..10:
	how = " bruisingly";
	break;
    case 11..15:
	how = " painfully";
	break;
    case 16..20:
	how = " very painfully";
	break;
    case 21..25:
	how = " painfully hard";
	break;
    case 26..30:
	how = " incredibly hard";
	break;
    case 31..35:
	how = " with devastating effectiveness";
	break;
    default:
	how = " with a fatal blow";
	break;
    }

    me->catch_msg("You attempt to hit your opponent in a vital spot!\n" +
      capitalize(enemy->query_pronoun()) + " is hit" + how + ".\n");
    tell_object(enemy, me->query_The_name(enemy) +
      " crouches on his back legs, then leaps forward, thrusting his " +
      "front legs into your body!\n" +
      "You are hit" + how + ".\n");
    tell_watcher(QCTNAME(me) + " feints back on his legs from " +
      QTNAME(enemy) + ", then rears, thrusting his front legs straight at "+
      QTNAME(enemy) + "'s body!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}

/*
 * Function name: cr_configure
 * Description:   Configures basic values for this humanoid.
 */
public nomask void
cr_configure() 
{
    ::cr_configure();

    if (query_attackuse())
	QEXC->cb_set_attackuse(query_attackuse());
    else
	QEXC->cb_set_attackuse(100);
}

/*
 * Function name: update_procuse()
 * Description:   use this to update the percent usage of attacks
 */
public nomask void
update_procuse()
{
    QEXC->cb_modify_procuse();
}
