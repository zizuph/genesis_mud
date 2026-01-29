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

    set_name("lenz");
    set_living_name("lenz");
    set_race_name("aide");
    set_title("the Aide of Wayreth");
    set_long("This magical creature is more of a presence than a physical " +
	"being. Created and sustained for the purpose of aiding Wizards " +
	"in their search for arcane knowledge and skill, this aide will " +
	"train you in your magical arts and answer a few questions you " +
	"may have. Though not the most advanced, this aide radiates " +
	"strong magic, and you wonder at the intracacies needed to " +
	"conjure such a thing.\n"); 
    add_name(({"ethereal","creature","being"}));
    set_adj("ethereal");
    set_gender(G_NEUTER);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);

    set_stats(({100,120,100,100,200,100}));
    set_skill(SS_DEFENCE,        100);
    set_skill(SS_BLIND_COMBAT,   100);
    set_skill(SS_AWARENESS,      150);
    set_skill(SS_UNARM_COMBAT,   100);
  
    set_default_answer("The aide says: I'm sorry, but that is beyond " +
        "my knowledge and duties.\n");
   
    add_ask(" [about] 'element' / 'fire' / 'air' / 'earth' / " +
	"'water' / 'death' / 'life' / 'elements'",
            "say The ability to harness the various " +
	"elements is key to casting potent spells and spells of " +
	"high difficulty. Every spell uses the elements, and the " +
	"more proficient you are at controlling them, the better " +
	"you'll be able to cast spells. Without careful training " +
	"though, you could be consumed, for the elements are the " +
	"raw magical material of the universe.", 1);
    add_ask(" [about] 'form' / 'forms' / 'abjuration' / 'conjuration' / " +
	"'enchantment' / 'transmutation' / 'illusion'", 
	"say The forms of magic constitute the type of spell, " +
	"and proficiency within a certain form makes it all the more " +
	"powerful. The different Orders of the Wizards of High Sorcery " +
	"train different forms of magic to varying degrees. The forms " +
	"a Wizard is adept in is a strong indicator of what kind of " +
	"magic that Wizard concentrates on.", 1);
    add_ask(" [about] 'herbalism' / 'herbs'", 
	"say Identifying herbs and knowing how to use them " +
	"is an important skill for any caster of magic, for unless " +
	"you wish to spend your days waiting for your mental energies "+
	"to heal, a knowledge of the local fauna is essential.", 1);
    add_ask(" [about] 'spells' / 'spellcraft'",
	"It says: The most basic of a Wizard's skill, being " +
	"proficient in spellcraft allows control of more powerful spells, " +
	"more potent spells, and spells becoming less taxing on the mind.\n");
    add_ask(" [about] 'quest' / 'task'",
	"say I thank you for your offer, but I am but " +
	"a lowly servant here and have no needs.", 1);

    set_act_time(5);
    add_act("say Please don't touch the books in this room. " +
	"Unpleasant things have been known to occur.");
    add_act("say Though seemingly weak when starting out, a " +
	"Wizard's magical prowess grows with time, to unparalled " +
	"heights!");
    add_act("say Magic is dependant on its fathers, the Moon-gods " +
	"Solinari, Lunitari, and Nuitari.");
    add_act("say The skills you can learn here are the heart of " +
	"a Wizard's power, second only to one's intellect.");
    add_act("say Would you care to train in the arcane arts?");
    add_act("emote patiently waits to help you where possible.");
    add_act("emote floats about, tidying the desks in preparation " +
	"of a studious Wizard.");
    
    set_cact_time(4);
    add_cact("say Odd, you shouldn't be able to attack me, please " +
	"make a bug report about this to the Immortal Wizards of " +
	"the Tower.\n");
}  

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Lenz (shouldn't be killable)", killer);
    return 0;
}
