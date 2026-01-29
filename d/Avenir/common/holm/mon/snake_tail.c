// -*-C++-*-
//              /d/Avenir/common/holm/mon/snake_tail.c
// file name:   ~Avenir/common/dark/mon/worm_tail.c
// creator(s):  Boriska, descriptions by Grace.
// last update: Boriska, Mar 24 1995
// purpose:     Part of worm NPC
// note:        Should be cloned and handled by master_worm object.
//              can't be brawled (no eyes)
// bug(s):
// to-do:     
// Revision history:  Feb 1997 -Lilith-
//     
inherit "/d/Avenir/common/dark/mon/worm_part";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include <const.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../holm.h"

#define A_SKIN 0
#define A_TAIL 1

#define H_FLESH 0
#define H_ORIFICE 1
#define H_SEGMENT 2

#define RAND 150+random(50)

static object to = this_object();

void
create_creature ()
{
    if ( !IS_CLONE )
        return;
  
    set_name("tail");
    add_name(({"snake", "anaconda", "boa", "body"}));
    add_adj(({"giant", "anaconda" ,"green"}));
    set_race_name("serpent");
    set_short("tail-end of a giant anaconda");
    set_long("This is the tail end of a very large serpent. It's scales "+
	"are mottled shades of green, with numerous leopard-like dark "+
        "spots. In some places you can see the underbelly scales, "+
        "vibrantly yellow with oblong black markings. As big around "+
        "as a giant's thigh, the prehensile tail tapers to a blunted "+
        "point.\n");

    set_stats (({RAND, RAND, 150, RAND, RAND, RAND}));
    set_skill (SS_DEFENCE, 100);
    set_skill (SS_UNARM_COMBAT, 100);
    set_skill (SS_BLIND_COMBAT, 100);
    set_attack_chance(60);

    set_gender (G_NEUTER);
    set_arrive("The tail of a giant anaconda slithers toward you!\n");
    set_depart("The tail of a giant anaconda slithers away.\n");

    set_hitloc_unarmed ( H_FLESH,    20, 10, "soft yellow underbelly");
    set_hitloc_unarmed ( H_ORIFICE,  35, 20, "blunted end");
    set_hitloc_unarmed ( H_SEGMENT,  40, 70, "greenish scale");

    set_attack_unarmed ( A_SKIN, 70, 40, W_BLUDGEON, 50, "gargantuan coil");
    set_attack_unarmed ( A_TAIL, 80, 40, W_BLUDGEON, 50, "blunted end");

    add_prop("_ranger_i_not_brawl", 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop (NPC_I_NO_RUN_AWAY, 1); // only master_worm can move
    add_prop (CONT_I_WEIGHT, 654321);
    add_prop (CONT_I_VOLUME, 543210);

    set_act_time(15);
      add_act("emote shifts in a constant, sinuous glide.");
      add_act("emote produces an almost inaudible rasp as the "+
         "coils slide past one another.");
      add_act("emote flails the air.");        

    // give it funny sum of money
    MONEY_MAKE_CC(5)->move(to);
    MONEY_MAKE_SC(4)->move(to);
    MONEY_MAKE_GC(3)->move(to);
    MONEY_MAKE_PC(2)->move(to);    
    clone_object(DARK + "obj/bones")->move(TO, 1);
}


void
flail_3(object victim)
{
    int hit, how;
    mixed where, arm;
    string str;
    string *randwhere = ({ "right side", "left side", "right shoulder", 
                           "left shoulder", "head" });

    if (ENV(victim) != ENV(TO))
        return;

    // Choose power of hit based on mob stat size.
    mixed* hitresult = do_stat_based_attack(TO, victim, W_IMPALE);
	
	// The attack was evaded
	if (intp(hitresult))
		return;
	
    hit = hitresult[0];
    where = hitresult[1];

    if (hit <= 0)
    {
        tell_object(victim, "The club-like tail strikes at you on the "+
            where +" with incredible power, barely missing you!\n");
        tell_watcher("The club-like tail of the anaconda strikes "+ 
            QCTNAME(victim) + " a blow at the "+ where +", barely missing "+
            OBJECTIVE(victim) +" "+ str +"!\n", victim);
        return;
    }

    if (hit < 10) 
        str = "just a bit";
    else if (hit < 20) 
        str = "only a little";
    else if (hit < 30) 
        str = "badly";
    else if (hit < 40) 
        str = "quite badly";
    else
        str = "horribly";
  
    tell_object(victim, "The club-like tail strikes you on the "+
        where +" with incredible power, hurting you "+ str +"!\n");
    tell_watcher("The club-like tail of the anaconda strikes "+ 
        QCTNAME(victim) + " a blow on the "+ where +", hurting "+
        OBJECTIVE(victim) +" "+ str +"!\n", 
        victim);

    if (victim->query_hp() <= 0) 
    {
        tell_watcher(QNAME(victim) + "'s scream is cut off in mid-cry "+
            "as "+victim->query_pronoun() + " is bludgeoned to death "+
            "by the tail of the anaconda.\n", victim);
        victim->catch_msg("An awful scream tears from your throat "+
            "as you are struck a mortal blow by the tail of the "+
            "anaconda!\n");
        victim->do_die();
    }
}

void 
flail_2(object victim)
{
    if (ENV(victim) != ENV(TO))
        return;

    if (random(400) > (victim->query_stat(SS_DEX)))
        flail_3(victim);
    else
    {
        tell_object(victim,"You dodge the enormous club-like end of the "+
            "giant anaconda's tail. It lands in the brush with an earth-"+
            "shaking thud!\n");
        tell_watcher("At the last possible moment, "+ QCTNAME(victim) +
            " ducks under the swing of the giant anaconda's tail! It "+
            "crashes into the brush with earth-shaking violence!\n",
            victim);
    }
}

void
flail_1(object victim)
{
    if (ENV(victim) != ENV(TO))
        return;
    tell_watcher("The giant anaconda tail flails the air above your "+
        "head!\n");
    set_alarm(1.0, 0.0, "flail_2", victim);
}
    

int
special_attack (object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
	  return 1;
    }

    switch (random(5))
    {
        case 1: flail_1(victim); 
            return 1;
    }

}

void
aggressive_attack (object ob)
{
    if (member_array (ob, query_enemy (-1) ) < 0 ) 
    {
        write("You hear a rasping slither and feel the whoosh "+
            "of air as something BIG bears down on your head!\n");
        ::aggressive_attack (ob);
    }
}
