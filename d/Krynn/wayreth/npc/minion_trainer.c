/*
 * Lenz the Aide of Wayreth,
 * trainer of mage skills for WoHS
 * modified from Gelnor of Wayreth
 * by Kentari
 * January,'97
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE

inherit "/std/act/domove";     /* Allows Lenz to move */
inherit "/std/act/action";     /* Allows Lenz to act  */

public void
create_krynn_monster()
{
    string str;

    set_name("legulgoth");
    set_living_name("legulgoth");
    set_race_name("minion");
    set_title("the Spectral Weaponsmaster of Wayreth");
    set_long("Before you stands the spirit of a warrior human from times long past, " +
       "a spectral minion who died with a vow of protecting his wizard charge " +
       "unfulfilled. In death this minion is still bound to his vow, and trains " +
       "Wizards of High Sorcery in the basics of defence and knife skills.\n"); 

    set_adj("spectral");
    set_gender(G_NEUTER);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
   add_prop(LIVE_I_UNDEAD, 10);
   add_prop(LIVE_I_NO_CORPSE, 1);

    set_stats(({100,120,100,100,200,100}));
    set_skill(SS_DEFENCE,        100);
    set_skill(SS_BLIND_COMBAT,   100);
    set_skill(SS_AWARENESS,      150);
    set_skill(SS_UNARM_COMBAT,   100);
  
    set_default_answer("The spectral minion responds in a long-dead language that " +
         "you cannot understand.\n");
   
    add_ask(" [about] 'training' / 'defence' / 'knife' / 'vow' / 'skills'",
        "say I am bound by my vow to defend the Wizards of this Tower, even " +
        "in death. I will train the basics of defence. And on orders of the " +
        "Conclave, after the great sacrifice of the Red Robe Magius, I will " +
        "train the art of knife fighting... a final resort when ones magic " +
        "is exhausted.", 1);

    set_act_time(5);
    add_act("emote fades slightly from sight.");
    add_act("say I am bound by my vows, even in death!");
    add_act("say The martial arts are a last resort for a wizard. I hope you " +
      "rarely have to use them.");
    add_act("say Would you care to train in the martial arts?");
    add_act("emote patiently waits to help you where possible.");
    add_act("emote floats about the courtyard with the patience of the dead.");
    
    set_cact_time(4);
    add_cact("say Odd, you shouldn't be able to attack me, please " +
	"make a bug report about this to the Immortal Wizards of " +
	"the Tower.\n");
}  


