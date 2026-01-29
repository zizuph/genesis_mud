//-*-C++-*-
// file name:   ~Avenir/common/holm/mon/snake_head.c
// creator(s):  Lilith Jan 1997 
// purpose:     The head portion of the anaconda living in the jungle.
// note:        (Inherits altered form of Boriska's Worm code)
//              Should be cloned and handled by snake_master object.
// bug(s):
// to-do:     
// last update: 
inherit "/d/Genesis/specials/npc/stat_based_specials";
inherit "/d/Avenir/common/dark/mon/worm_part";
inherit "/std/act/ranpick";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <money.h>
#include "../holm.h"

#define H_LEFT_EYE 0
#define H_RIGHT_EYE 1
#define H_MOUTH 2
#define H_SCALE 4

#define A_TEETH_0 0
#define A_TEETH_1 1
#define RAND 165+random(50)

static object to = this_object();

void
create_creature ()
{
    if (!IS_CLONE)
       return;

    set_name("head");
    add_name(({"snake", "anaconda", "boa"}));
    set_short("giant anaconda");
    add_adj (({"giant", "anaconda", "green"}));
    set_race_name ("serpent");
    set_long("This is the head portion of a giant anaconda. Its large "+
        "scales are mottled shades of green with dark round splotches. "+
        "The underbelly has smaller bright yellow and black scales. It "+
        "has long narrow fangs with needle-sharp points. The eyes are "+
        "as large as your fist, black, and unblinking.\n"); 

  // need the same con for all parts for healing, otherwise
  // the part having lowest con will determine how good we heal.
  
    set_stats ( ({RAND, RAND, 150, RAND, RAND, RAND}) );
    set_skill (SS_DEFENCE, 100);
    set_skill (SS_UNARM_COMBAT, 100);
    set_skill (SS_BLIND_COMBAT, 75);
    set_gender (G_NEUTER );
    set_attack_chance(60);
    set_pick_up(50);
    set_arrive ("You hear a rustling in the leaves and a subtle rasping " + 
        "sound.\nThe head of a giant anaconda slithers in!\n");
    set_attack_unarmed(A_TEETH_0,   70, 40, W_IMPALE, 50, "fangs");
    set_attack_unarmed(A_TEETH_1,   80, 40, W_IMPALE, 50, "fangs"); 

    set_hitloc_unarmed(H_LEFT_EYE,  25, 10, "left eye");
    set_hitloc_unarmed(H_RIGHT_EYE, 25, 10, "right eye");
    set_hitloc_unarmed(H_MOUTH,     40, 40, "snout");
    set_hitloc_unarmed(H_SCALE,     40, 40, "bright green scale");  

    add_prop (NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop (LIVE_I_SEE_DARK, 5); // head can see in dark, other parts cannot
    add_prop (CONT_I_WEIGHT, 654321);
    add_prop (CONT_I_VOLUME, 543210);

    set_act_time(15);
      add_act("emote tastes the air with its flickering tongue.");
      add_act("emote weaves its head back and forth hypnotically.");
      add_act("emote opens its jaws wide, startling you.");
      add_act("emote shifts its coils beneath it in a constant, "+
         "sinuous glide.");

  // give it funny sum of money
  MONEY_MAKE_SC(4)->move(to);
  MONEY_MAKE_GC(3)->move(to);
}

/* ********* Special attack ********** */

int 
mesmer(object victim)
{
    object *people;
    object enemy;
    int num;

    if (!present(victim), ENV(TO))
        return 0;
    
    enemy = victim;
    num = ( (victim->query_stat(SS_DIS)/2 ) -
            (TO->query_stat(SS_DIS)/3) + random(50) );

    if (num < 100)
    {
        if (CAN_SEE(TO, victim) && CAN_SEE(victim, TO))
        {
            tell_object(victim, "Your eyes are caught and held by "+
                "the unblinking stare of the giant anaconda.\n"); 
            tell_room(ENV(TO), QCTNAME(victim) +" is mesmerized by " + 
                "the anaconda's gaze.\n", victim);
            victim->add_attack_delay(30);
            victim->stop_fight(TO);
            TO->stop_fight(victim);
         
            people = filter(all_inventory(ENV(TO)), interactive); 
            people -= ({ enemy }); // all players but the one mesmerized
            set_alarm(4.0,0.0, &aggressive_attack(people[random(sizeof(people))]));
            return 1;
        }
    return 1;
    }
}

int
strike_3(object victim)
{
    int hit, how;
    mixed arm;
    string str, where;
    string *randwhere = ({ "right arm", "left arm", "right hand", 
                           "right leg", "left leg", "left hand" });

    if (!present(victim), ENV(TO))
        return 0;

    // Choose power of hit based on mob stat size.
    mixed* hitresult = do_stat_based_attack(TO, victim, W_IMPALE);
	
	// The attack was evaded
	if (intp(hitresult))
		return 1;
	
    hit = hitresult[0];
    where = hitresult[1];

    if (hit <= 0)
    {
      tell_object(victim, "The giant anaconda strikes with incredible "+
          "speed and accuracy, closing its powerful jaws on your "+
          where +" and barely missing you!\n");
      tell_watcher("The giant anaconda strikes with incredible speed "+
          "and accuracy, nearly closing its powerful jaws on "
          + QPNAME(victim) +" "+ where +"!\n", victim);
        return 1;
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
 
    tell_object(victim, "The giant anaconda strikes with incredible "+
        "speed and accuracy, closing its powerful jaws on your "+
        where +" and hurting you "+ str +"!\n");
    tell_watcher("The giant anaconda strikes with incredible speed "+
        "and accuracy, closing its powerful jaws on "+ QPNAME(victim) 
        +" "+ where +"!\n", victim);

    if (victim->query_hp() <= 0) 
    {
        tell_watcher(QNAME(victim) + " screams horribly and thrashes "+
            "weakly as "+victim->query_pronoun() + " is crushed in the "+
            "jaws of the anaconda.\n", victim);
        victim->catch_msg("An awful scream tears from your throat "+
            "as you are mercilessly crushed to death in the jaws "+
            "of the anaconda!\n");
        victim->do_die();
        set_alarm(3.0, 0.0, monster_do_pick);
    }
    /* Hopefully this should prevent anymore freak deaths */
    this_object()->stop_fight(victim);
    victim->stop_fight(this_object());
    return 1;
}

int 
strike_2(object victim)
{
    if (!present(victim), ENV(TO))
        return 0;

    if ((TO->query_stat(SS_DEX) + random(200)) > (victim->query_stat(SS_DEX)))
        strike_3(victim);
    else
    {
        tell_object(victim,"You manage to anticipate the anaconda's next "+
            "move and evade its strike.\nThe anaconda's jaws close on "+
            "empty air.\n");
        tell_watcher(QCTNAME(victim) +" seems to anticipate the where the "+
            "anaconda will strike and dives out of the way!\nThe anaconda"+
            "'s jaws close on empty air!\n", victim);
    }
    return 1;
}

int
strike_1(object victim)
{
    if (!present(victim), ENV(TO))
        return 0;

    tell_watcher("The giant anaconda rises up on its coils.\nThe giant "+
        "anaconda weaves its head and opens its jaw wide in preparation "+
        "to strike!\n");
    set_alarm(1.0, 0.0, "strike_2", victim);
    return 1;
}
    

// do something interesting sometimes
int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
	  return 1;
    }

    switch (random(5))
    {
        case 0: mesmer(victim);
            return 0;
        case 1: strike_1(victim); 
            return 1;
    }
}


// write nice message only for new attacker
void
aggressive_attack(object ob)
{
    if (member_array (ob, query_enemy (-1) ) < 0 ) 
    {
        ob->catch_msg ("The giant anaconda gathers coils beneath it and "+
            "raises its head to strike!\n");
        ::aggressive_attack (ob);
    }
}

