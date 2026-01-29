//              /d/Avenir/common/holm/mon/snake_coil.c
// file name:   snake_coil.c
// creator(s):  Boriska, descriptions and special attacks messages by Grace.
// creator(s):  Lilith, ???/??
// last update: Boriska, Mar 24 1995
//		Denis, May'00: Fixed push random target selection.
// purpose:     Part of worm NPC
// note:        Should be cloned and handled by master_snake object.
//              Can't be brawled (no eyes)
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
#include "../holm.h"

#define A_SKIN 0
#define A_ANO_SKIN 1

#define H_FLESH 0
#define H_UNDERSIDE 1
#define H_RING 2

#define RAND (135+random(50))

#define DEBUG
#ifdef DEBUG
#define D(x) find_player("lilith")->catch_msg((x))
#else
#define D(x) ;
#endif

string captive;
string query_captive()  {   return captive;   }
void set_captive(string str)  {   captive = str;   }

private void do_bang(object victim);
private void do_push(object victim);

void
create_creature ()
{
    if (!IS_CLONE)
        return;

    set_name("coil");
    add_name(({"snake", "coils", "anaconda", "boa", "body"}));
    set_short("coiled body of a giant anaconda");
    add_adj(({"giant", "anaconda" ,"green"}) );
    set_race_name("serpent");
    set_long("This is just one part of an extremely large serpent. "+
	  "There are several coils here, as big around as a giant's "+
        "thigh. The large scales on the coils are mottled shades "+
        "of green, with numerous leopard-like dark spots. In some "+
        "places you can see the underbelly scales, vibrantly "+
        "yellow with oblong black markings.\n");

    set_stats( ({RAND, RAND, 150, RAND, RAND, RAND}) );
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_attack_chance(60);

    set_gender(G_NEUTER);
    set_arrive("The coiled body of a giant anaconda glides silently "+
       "past you!\n");

    set_attack_unarmed(A_SKIN,     90, 40, W_SLASH, 50, "green scale");
    set_attack_unarmed(A_ANO_SKIN, 45, 20, W_SLASH, 50, "yellow underbelly");
 
    set_hitloc_unarmed(H_FLESH,     35, 24, "greenish scale");
    set_hitloc_unarmed(H_UNDERSIDE, 25, 20, "soft yellow underbelly" );
    set_hitloc_unarmed(H_RING,      40, 60, "gargantuan coil" );

    add_prop("_ranger_i_not_brawl", 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1); /* only master_worm can move */
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 654321);
    add_prop(CONT_I_VOLUME, 543210);
    
    set_act_time(15);
      add_act("emote shifts in a constant, sinuous glide.");
      add_act("emote produces an almost inaudible rasp as the "+
         "coils slide past one another.");
      add_act("emote suddenly shifts position.");

    seteuid(getuid());
    // give it funny sum of money
    MONEY_MAKE_CC(5)->move(this_object());
    MONEY_MAKE_GC(6)->move(this_object());
    MONEY_MAKE_PC(1)->move(this_object());
    if (random(3))
        clone_object(HOLM +"mon/deer")->move(TO, 1);
    
}

// following are arrays of descrs for attacks and their damage
// keep their size the same when modifying attack message
static string *att_msg = ({ " presses "," slaps "," slams ",  
                            " bludgeons " });
static int att_msg_len = sizeof (att_msg);
// damage message
static string *dmg_msg = ({ "scraped","smashed","crushed",
                            "squashed" });
// effect as watcher sees it
static string *side_eff_msg = ({ 
    " seems a bit disoriented.\n",
    " cannot seem to breathe.\n", 
    " collapses to the ground, gasping for air!\n",
    " is knocked momentarily unconscious!\n"
});

// effect for beaten person :)
static string my_eff_msg = ({
    "You seem to be a bit disoriented.\n",
    "You cannot seem to catch your breath.\n",
    "You collapse to the ground, gasping for air!\n",
    "You are knocked momentarily unconscious!\n"
});

// special attack - stop attacker from hitting and do some hp damage too
int
special_attack(object victim)
{
    if (victim->query_prop (OBJ_M_NO_ATTACK))
        return 0;
  
    if (!victim->query_prop (LIVE_I_STUNNED) && !random (4))
        do_bang (victim);
    if (!random (3))  // pick some enemy (not victim) and push him out
        do_push (victim);
    return 0;
}

private void
do_bang(object victim)
{
    int att = random (att_msg_len);
  
    tell_watcher ("The giant anaconda" + att_msg[att] + QNAME(victim) +
        " with one of its coils!\n",this_object(), victim);
    victim->catch_msg("The giant anaconda" + att_msg[att] +
		     "you with one of its coils!\n");
    tell_watcher(QNAME(victim) + side_eff_msg[att], this_object(), victim);
    victim->catch_msg(my_eff_msg[att]);
  
    victim->add_stun();
    // master worm object removes stun from victim as worm_body 
    // could be dead before stun removal
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
  
    tell_watcher("The giant anaconda thrashes some coils about.\nOne of " +
        "the coils slams into " + QNAME(victim) + " and sweeps " +
        victim->query_objective() + " toward the " + exit + "!\n", 
        this_object(), victim);
  
    victim->catch_msg("The giant anaconda thrashes some coils about.\n" +
        "The coils slam into you and sweep you toward the " + exit + "!\n" );
  
    if (victim->resolve_task (TASK_FORMIDABLE, ({SS_ACROBAT, TS_DEX})) > 0) 
    {
        tell_watcher(QNAME(victim) +" vaults over the coil and lands "+
            "at your side.\n", this_object(), victim);
        victim->catch_msg("You jump and push off against the giant coil, "+
            "vaulting yourself out of the coil's path.\n");
    }
    else 
        victim->move_living(exit, dest, 1);
}

void
aggressive_attack (object ob )
{
    if (member_array (ob, query_enemy (-1) ) < 0 ) 
        ::aggressive_attack (ob);
}
