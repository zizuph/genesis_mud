// -*-C++-*-
// file name:   worm_body.c
// creator(s):  Boriska, descriptions and special attacks messages by Grace.
// last update: Boriska, Mar 24 1995
// purpose:     Part of worm NPC
// note:        Should be cloned and handled by master_worm object.
//              Special attack code calls finctions in master_worm.
// bug(s):
// to-do:     
// Revision history:
// Sept 1994 - Updated to use LIVE_I_STUNNED instead of LIVE_I_ATTACK_DELAY
// --Boriska

inherit "/d/Avenir/common/dark/mon/worm_part";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Avenir/include/worm.h"

#define A_SKIN 0
#define A_ANOTHER_SKIN 1

#define H_FLESH 0
#define H_UNDERSIDE 1
#define H_RING 2

#define RAND (125+random(50))

private void do_bang(object victim);
private void do_push(object victim);

void
create_creature ()
{
    if ( !IS_CLONE )
	return;

    set_name ("body");
    add_name ("worm");
    set_short ("worm body");
    add_adj ( ({"monstrous" ,"scaled"}) );
    set_long (
      "This looks like a section of one of the giant omnivorous\n" +
      "worms known to live in these tunnels. Dread fills you\n"+ 
      "as you note its tremendous size. Each segment is the\n"+ 
      "length of a tall man, and there are a half-dozen within\n"+
      "view. You find yourself wondering just how long it is,\n" + 
      "and when it last ate.\n"
    );

    set_race_name("worm body");  

    set_stats( ({RAND, RAND, 150, RAND, RAND, RAND}) );
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    set_gender(G_NEUTER);
    set_arrive(
      "With a low scraping sound the monstrous cave worm body moves by you!\n");

    set_aggressive(1);

    set_attack_unarmed(A_SKIN,         90, 40, W_SLASH, 100, "hard skin");
    set_attack_unarmed(A_ANOTHER_SKIN, 90, 40, W_SLASH, 50, "hard skin");

    set_hitloc_unarmed(H_FLESH,     20, 10, "soft fleshy place between rings");
    set_hitloc_unarmed(H_UNDERSIDE, 35, 40, "underside" );
    set_hitloc_unarmed(H_RING,      40, 50, "scaled ring" );

    add_prop(NPC_I_NO_RUN_AWAY, 1); // only master_worm can move
    add_prop(CONT_I_WEIGHT, 654321);
    add_prop(CONT_I_VOLUME, 543210);

    add_leftover( LEFT_OBJ, BODY_LEFTOVER, 1, 0 ,0, 1);
    // Note : all worm parts contain the same leftover object
    // with different features based on organ name.
    // Make sure that second argument is processed properly
    // in SKIN code.

    // give it funny sum of money
    MONEY_MAKE_CC(5)->move(this_object());
    MONEY_MAKE_SC(4)->move(this_object());
    MONEY_MAKE_GC(3)->move(this_object());
    MONEY_MAKE_PC(2)->move(this_object());
}

// following are arrays of descrs fo attacks and their damage
// keep their size the same when modifying

// attack message
static string *att_msg = ({
  " presses ",
  " bangs ",
  " slams ",
  " grinds "
});

static int att_msg_len = sizeof (att_msg);

// damage message
static string *dmg_msg = ({
  "scraped",
  "smashed",
  "crushed",
  "squashed"
});

// effect as watcher sees it
static string *side_eff_msg = ({
  " seems a bit disoriented.\n",
  " cannot seem to catch a breath.\n",
  " collapses to the floor, gasping in pain!\n",
  " is knocked momentarily unconscious!\n"
});

// effect for beaten person :)
static string my_eff_msg = ({
  "You seem to be a bit disoriented.\n",
  "You cannot seem to catch a breath.\n",
  "You collapse to the floor, gasping in pain!\n",
  "You are knocked momentarily unconscious!\n"
});

// special attack - stop attacker from hitting and do some hp damage too
int
special_attack(object victim)
{
    if (victim->query_prop (OBJ_M_NO_ATTACK))
	return 0;

    if ( !victim->query_prop (LIVE_I_STUNNED) && !random (4))
	do_bang (victim);
    if (!random (3))  // pick some enemy (not victim) and push him out
	do_push (victim);
    return 0;
}

private void
do_bang(object victim)
{
    int att = random (att_msg_len);

    tell_watcher ("Monstrous cave worm" + att_msg[att] + QNAME(victim) +
      " against the wall!\n",this_object(), victim);
    victim->catch_msg ("Monstrous cave worm" + att_msg[att] +
      "you against the wall!\n");
    tell_watcher (QNAME(victim) + side_eff_msg[att], this_object(), victim);
    victim->catch_msg (my_eff_msg[att]);

    victim->add_stun();
    // master worm object removes stun from victim as worm_body could be dead
    // before stun removal
    master->remove_delay(att+1, victim);
}

private void
do_push (object ob)
{
    // pick one of my attackers and push to another room

    mixed enemies = query_enemy(-1); 
    object victim;
    string *exit_cmds;
    string exit, dest;
    int ind;

    enemies -= ({ob});
    enemies = filter (enemies,"filter_present_living","/sys/global/filters",
      this_object());

    if (!environment() || !sizeof(enemies))
	return;

    victim = enemies[random(sizeof(enemies))];

    exit_cmds = environment()->query_exit_cmds();
    if (!sizeof(exit_cmds))
	return;

    ind = random(sizeof(exit_cmds));
    exit = exit_cmds[ind];
    dest = (environment()->query_exit_rooms())[ind];

    tell_watcher(
      "A sinious wave of flexing and relaxing muscles runs under\n" +
      "worm's skin! It catches " + QNAME(victim) + " attempting to push " +
      victim->query_objective() + " " + exit + "!\n", this_object(), victim);

    victim->catch_msg (
      "A sinious wave of flexing and relaxing muscles runs under\n" +
      "worm's skin. It catches you attempting to push you " + exit + "!\n" );

    if (victim->resolve_task (TASK_DIFFICULT, ({TS_STR, TS_DEX})) > 0) {
	tell_watcher(
	  QNAME(victim) +
	  " manages to grasp the rocky wall and stays on the place.\n",
	  this_object(), victim);
	victim->catch_msg(
	  "You manage to grasp the rocky wall and stay on the place.\n");
    }
    else 
	victim->move_living(exit, dest, 1);
}

void
aggressive_attack (object ob )
{
    if (member_array (ob, query_enemy (-1) ) < 0 ) {
	ob->catch_msg
	( "With deadly grace cave worm unfolds the loops of its body...\n");
	::aggressive_attack (ob);
    }
}
