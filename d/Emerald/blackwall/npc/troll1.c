/* A typical troll, liable to be found in the Blackwall mountains.
   Code (c) 1999 Damian Horton. BKA Casimir. */

#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/std/troll";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Emerald/sys/paths.h"

// prototypes for their special attack
int charge(object enemy);

void
create_troll()
{
    set_adj(({ "powerful", "horrible", "tough" })[random(3)]);
    set_long("A hulking humanoid which stands considerably taller than the "+
	   "average man and much broader. Its blackened skin lends it the "+
	   "appearance of having been carved out of stone. Moreover, if "+
	   "one is so foolish as to strike at this creature, one will "+
	   "discover that appearance is not the only characteristic it "+
	   "shares with the rock of the mountains!\n");
    
    config_troll(70 + random(20));
    set_alignment(-200);

    set_cact_time(6);
    add_cact("emote roars violently in defiance.\n");
    add_cact("emote smashes some nearby trees in anger.\n");

    // Attacks players 50% of the time.
    set_aggressive(&random(2));
    set_special_attack_percent(8);
    add_special_attack(charge, 100, "charge");
 
    if (random(2))
    {
        add_equipment(BLACKWALL_DIR + "wep/tree_branch");
    }
} 

int
charge(object enemy)
{
    mixed *hitresult;
    string how;
    
    if ((enemy->query_stat(SS_INT) + enemy->query_stat(SS_DEX) + 
	 enemy->query_skill(SS_DEFENCE)) < (random(500) + query_stat(SS_INT) +
	 query_stat(SS_DEX)))
    {
        hitresult = enemy->hit_me(150 + random(350), W_BLUDGEON,
            this_object(), -1);
	  
        if (enemy->query_hp() <= 0)
        {
	    enemy->catch_tell("The " + short() + " steps back and then " +
                "charges right into you!\nYou feel a crushing pain in your "+
                "chest as you are sent flying through the air. You lose " +
                "consciouness before striking the ground....\n");
  	    tell_watcher("The " + short() + " charges directly into " +
                QTNAME(enemy) + ", sending " + enemy->query_objective()+
                " hurtling through the air!\n" +
                capitalize(enemy->query_pronoun()) + " lands in a bloody " +
                "and crumpled heap, several feet from where " +
                enemy->query_pronoun() + " had been standing.\n");
  	    enemy->do_die(this_object());
        }
        else
        {
            how = ({ "dazed",
                     "winded", 
                     "crushed",
                     "pulverized" })[min(3, hitresult[0] / 20)];

	    enemy->catch_tell("The "+ short() + " steps back, and then " +
                "charges right into you!\nYou are " + how + "!\n");
	    tell_watcher("The "+ short() + " charges directly into " +
                enemy->query_the_name(this_object())+"!\n" +
                capitalize(enemy->query_pronoun()) + " is " + how+ 
                " by the attack!\n", enemy);
	    enemy->add_attack_delay(2 + random(8), 1); // briefly dazed
        }
    }
    else
    {
        enemy->catch_tell("The " + short() + " steps back and then charges " +
            "right at you!\nFortunately, your lightning quick reflexes " +
	    "allow you to dive out of its way.\n");
        tell_watcher("The " + short() + " charges at " + QTNAME(enemy) + 
            ", but " + enemy->query_pronoun() + " dives to the side and " +
            "escapes unharmed!\n", enemy);
    }

    return 1;
}


