//-*-C++-*-
// file name:   ~Avenir/common/dark/mon/worm_head.c
// creator(s):  Boriska, descriptions and special attacks messages by Grace.
// last update: Feb 1994 - attack/defence tuning /Boriska
//              May 1995 - wormie goes stronger as he's no challenge for
//                         people who manage to find it..
// purpose:     Part of worm NPC
// note:        Should be cloned and handled by master_worm object.
// bug(s):
// to-do:     

inherit "/d/Avenir/common/dark/mon/worm_part";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <money.h>
#include "/d/Avenir/include/worm.h"

#define H_LEFT_EYE 0
#define H_RIGHT_EYE 1
#define H_MOUTH 2
#define H_TONGUE 3

#define A_TEETH_0 0
#define A_TEETH_1 1

#define PEN_RAND 400
// random part of special attack pen

#define RAND 75+random(50)

object to = this_object();

void
create_creature ()
{
    if ( !IS_CLONE )
	return;

    set_name ("head");
    add_name ("worm");
    set_short ("worm head");
    add_adj (({"mottled", "worm"}));
    set_race_name ("head");
    set_long(
      "This looks like the head of one of the giant omnivorous\n" +
      "worms known to live in these tunnels. Dread fills you as\n" + 
      "you note its tremendous size. You find yourself wondering\n" +
      "just how many rooms long it is, and when it last ate.\n"
    );

    // need the same con for all parts for healing, otherwise
    // the part having lowest con will determine how good we heal.
    set_stats ( ({RAND, RAND, 150, RAND, RAND, RAND}) );
    set_skill (SS_DEFENCE, 100);
    set_skill (SS_UNARM_COMBAT, 100);

    set_gender (G_NEUTER );

    set_arrive ("You hear a low " + 
      ({"rasping", "scraping", "scratching", "grinding"})[random(4)] +
      " sound. A giant worm head crawls in!\n");

    set_aggressive (1);

    // here's something for F.Herbert's fans...
    add_cmd_item ("shai-hulud", "exa",
      "             Oh, worm of many teeth,\n" +
      "             Canst thou deny what has no cure?\n" +
      "             The flesh and breath which lure thee\n" +
      "             To the ground of all beginnings\n" +
      "             Feed on monsters twisting in a door of fire!\n" +
      "             Thou hast no robe in all thy attire\n" +
      "             To cover intoxications of divinity\n" +
      "             Or hide the burnings of desire!\n" );

    //This is a Wormsong from F.Herbert's 'Dune Messiah'
    // Has a couple of hints on leftovers and tooth-knife by accident :)

    set_attack_unarmed(A_TEETH_0, 70, 40, W_IMPALE, 100, "teeth");
    set_attack_unarmed(A_TEETH_1, 80, 40, W_IMPALE, 50,  "teeth");

    set_hitloc_unarmed(H_LEFT_EYE,  25, 10, "left eye"  );
    set_hitloc_unarmed(H_RIGHT_EYE, 25, 10, "right eye" );
    set_hitloc_unarmed(H_MOUTH,     40, 50, "mouth"     );
    set_hitloc_unarmed(H_TONGUE,    40, 30, "tongue"    );

    add_prop (NPC_I_NO_RUN_AWAY, 1);
    // don't move on ourselves, only when master_worm says to do that :)
    add_prop (LIVE_I_SEE_DARK,1); // head can see in dark, other parts cannot
    add_prop (CONT_I_WEIGHT, 654321);
    add_prop (CONT_I_VOLUME, 543210);

    add_leftover ( LEFT_OBJ, TOOTH_LEFTOVER, 1,0,0,1);
    add_leftover ( LEFT_OBJ, HEAD_LEFTOVER,  1,0,0,1);
    // Note : all worm parts contain the same leftover object
    // with different features based on organ name.
    // Make sure that second argument is processed properly
    // in SKIN code.

    // give it funny sum of money
    MONEY_MAKE_CC(5)->move(to);
    MONEY_MAKE_SC(4)->move(to);
    MONEY_MAKE_GC(3)->move(to);
    MONEY_MAKE_PC(2)->move(to);
}

// Texts for special attacks
static string *attack_msg = ({
  "spits a little foul saliva on ",
  "vomits some fetid jelly on ",
  "spews some putrid slime at ",
  "retches a lot of poisonous slime on ",
  "belches a lot of pasty bile on ",
  "disgorges a stream of clotted spittle on ",
  "squirts a stream of thick foam on ",
  "sprays a jet of acidic froth at "
});

// used to pick the appopriate desc from array
int attack_ratio = PEN_RAND / sizeof (attack_msg);

static string *dmg_msg = ({
  "parched by the worm!\n",
  "scorched by the worm!\n",
  "burned by the worm!\n",
  "roasted by the worm!\n",
  "liquified by the worm!\n"
}); 

// used to pick the appopriate desc from array
int dmg_ratio = 100 / sizeof (dmg_msg);

static mixed *pain_msg = ({
  ({ " wince", " in irritation.\n" }),
  ({ " stagger", " in discomfort.\n"}),
  ({ " reel", " in pain!\n" }),
  ({ " writhe", " in torment!\n"}),
  ({ " convulse", " in agony!\n"})
});

// used to pick the appopriate desc from array
int pain_ratio = 100 / sizeof (pain_msg);

// do something interesting sometimes
int
special_attack(object victim)
{
    int pen;
    mixed *hit_result;
    int rand;  // random part of pen
    int att, res, pain;

    if ( victim->query_prop (OBJ_M_NO_ATTACK) || random (3) )
	return 0;

    if (victim->query_not_attack_me(to, -1))
    {
        return 0;
    }

    rand = random(PEN_RAND);
    pen = 300 + rand;
    pen -= pen * victim->query_magic_res (MAGIC_I_RES_ACID);


    if (!query_special_did_hit(to, victim))
    {
        pen = 0;
    }

    att = rand / attack_ratio;

    // attack message
    tell_watcher ( "The worm " + attack_msg[att] + QNAME (victim) +"!\n",
      to,victim);
    victim->catch_msg ("The worm " + attack_msg[att] + "you!\n");

    hit_result = victim->hit_me(pen, MAGIC_DT, to ,-1);
    res = hit_result[0] / dmg_ratio;

    // hit result message
    tell_watcher ( QNAME(victim) + " is " + dmg_msg[res], to, victim);
    victim->catch_msg ( "You are " + dmg_msg[res]);

    pain = hit_result[0] / pain_ratio;

    // pain message
    tell_watcher( QNAME(victim) + pain_msg[res][0] +"s"+ pain_msg[res][1],to,
      victim);
    victim->catch_msg ( "You" + pain_msg[res][0]  + pain_msg[res][1]);

    if ( victim->query_hp() <= 0 ) {
	tell_watcher (QNAME(victim) + " spurts blood from all orifices as " +
	  victim->query_pronoun() + "is splattered by the worm.\n",
	  to, victim);
	victim->catch_msg(
	  "You spurt blood from all orifices as you are splattered by the worm.\n");
	victim->do_die();
    }
    return 0;  // yes, I want other attacks to happen too.
}


// write nice message only for new attacker
void
aggressive_attack(object ob)
{
    if (member_array (ob, query_enemy (-1) ) < 0 ) {
	ob->catch_msg ("Horrible cave worm slowly turns its head toward you...\n");
	::aggressive_attack (ob);
    }
}
