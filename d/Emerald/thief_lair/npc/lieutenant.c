/* /d/Emerald/thief_lair/npc/lieutenant.c
   
   Gregarry, the second in command of the bandits of the Blackwall
   mountains. Found in /thief_lair/cave7.
   Code (c) 1999 Damian Horton. BKA Casimir.
*/

#pragma strict_types
#pragma save_binary 

#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <options.h>
#include "/d/Emerald/defs.h"

inherit THIEF_LAIR_DIR + "/npc/leader";
inherit THIEF_LAIR_DIR + "/npc/intro"; // Allows him to introduce himself.

// Special attack prototypes.
//int s_attack(object enemy);

void
create_bandit()
{
    set_name("gregarry");
    add_name("_gregarry"); // unique name
    set_title("brigand");
    set_race_name("human");
    set_adj("dark-haired");
    add_adj("scar-faced");
    set_long("This human's face is marred by a long, jagged scar, which "+
	     "extends from temple to chin across his left cheek. "+
	     "Though otherwise handsome, he is of an unkempt and dirty "+
	     "appearance, suggesting that he lives in the wilderness.\n");
 
    set_appearance(-10);
    add_prop(CONT_I_HEIGHT, 175);
    add_prop(CONT_I_WEIGHT, 83000);
    add_prop(CONT_I_VOLUME, 83000);
    
    set_stats(({100, 108, 96, 95, 90, 90}));
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 65);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_AWARENESS, 70);
    set_alignment(- 500);
    set_exp_factor(150); // Nasty specials, and part of an extremly dangerous
                         // group.

    add_equipment(({THIEF_LAIR_DIR + "wep/gregs_sword", 
		      THIEF_LAIR_DIR + "wep/gregs_knife",
		      THIEF_LAIR_DIR + "arm/elf_chainmail",
		      THIEF_LAIR_DIR + "arm/quilt_leggings",
		      THIEF_LAIR_DIR + "arm/iron_helm"}));

    set_act_time(10);
    add_act("emote appears concerned about your presence.");
    add_act("emote inspects you suspiciously with his gaze.");
    
    set_cact_time(10);
    add_cact("say Terribly sorry, but I must kill you now.");
    add_cact("say I couldn't have you living to report our location to "+
	     "the patrols.");

    set_special_attack_percent(30);
    add_special_attack(s_attack, 100, "s_attack");
    ::create_bandit_leader();
}
 
/* sets unarmed combat off, giving more knife and sword attacks */

int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}






