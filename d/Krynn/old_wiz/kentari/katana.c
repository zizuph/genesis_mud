inherit "/std/weapon.c";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
	set_name(({ "katana", "sword", "blade" }));
	set_pname(({ "katanas", "swords", "blades" }));
	set_adj(({ "ancient", "silver-hilted"}));
	set_short("ancient silver-hilted katana");
	set_pshort("ancient silver-hilted katanas");
	set_long("This exquisite, single-edged weapon is of foreign " +
		"make and has a slight curve along the tempered blade. " +
		"The hilt is made of finely crafted silver, displaying " +
		"scenes of meditation and tranquility. Obviously this " +
		"katana is made for the exotic and wealthy adventurer, " + 
		"and you can only hope to be worthy of its use.\n");

/* This exquisite, single-edged weapon is of foreign make and has a
 * slight curve along the tempered blade.  The hilt is made of finely
 * crafted silver, displaying scenes of meditation and tranquility.
 * Obviously this katana is made for the exotic and wealthy adventurer,
 * and you can only hope to be worthy of its use.
 */

	set_default_weapon(54, 50, W_SWORD, W_SLASH | W_IMPALE, W_RIGHT);

	update_prop_settings();
	set_wf(TO);
	add_prop(OBJ_M_NO_BUY, 1);
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	add_prop(OBJ_S_WIZINFO,
		"This katana allows the wielder attain a state of " +
		"extreme calm and clarity, thereby abling them to " +
		"both have higher awareness, location sense, appraise " +
		"enemy, find and remove traps, tracking, and slight " +
		"blindfighting in order to fight with a calm " +
		"perfection.\n");
	add_prop(MAGIC_AM_ID_INFO,
                ({"This weapon is magically enchanted.\n", 5,
		    "This weapon emanates calm and clarity.\n", 25}));
	add_prop(MAGIC_AM_MAGIC,({90,"enchantment"}));
	add_prop(OBJ_I_VOLUME, 7500);
	add_prop(OBJ_I_WEIGHT, 7500);
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(54,50) + 2500);
}

/* This checks to see if they have enough dis to use a sword that is
 * different than anything they've ever seen before.  Its too foreign for
 * those without the balls to use it (no offense ladies)
 */

mixed
wield(object wep)
{
	if (TP->query_stat(SS_DIS) > 60 && TP->query_stat(SS_WEP_SWORD) >
		50)
	{
		write("As you take hold of the tooled hilt, a sense of " +
			"deep calm and tranquility comes over you and " +
			"clears your mind of everything besides your " +
			"trained instincts.\n" +
			"You feel accutely aware of your environment.\n");
		TP->set_skill_extra(110, 30);
		TP->set_skill_extra(106, 20);
		TP->set_skill_extra(100, 20);
		TP->set_skill_extra(53, 10);
		TP->set_skill_extra(107, 10);
		TP->set_skill_extra(22, 10);
		set_alarm(10.0,0.0,"katana");	
		return 0;
	}

	return "You just don't feel confident enough to " +             
		"try and wield this weapon that looks so foreign, " +
		"despite its obviously exceptional quality.\n";
}

katana(object ob)
{
	 if(!query_wielded(TO))
           {
	   write("The fleeting feeling of peaceful serenity you felt " +
		"for the short time you wielded the blade beckons to you.\n");
	   return 1;
	   }
		
   write("Taking and letting out a deep breath, all worries and stress "
	+ "fade and you feel a new confidence in yourself and your " 
	+ "abilities.\n");
   say(QCTNAME(TP) + " lets out a deep breath and looks more calm and " + 
        "confident than ever before.\n");   
   TP->command("say I shall succeed, for my mind has been set in motion "
	+ "and my body follows faithfully\n");
   set_alarm(10.0,0.0,"assure");
   return 1;
}

mixed
unwield(object wep)
{
	write("As you release your grip, the clamour and chaos " +
		"of everyday life once more envelops your thoughts " +
		"and the details of your surroundings becomes less " +
		"clear.\n");
	TP->set_skill_extra(110, 0);
	TP->set_skill_extra(106, 0);
	TP->set_skill_extra(100, 0);
	TP->set_skill_extra(53, 0);
	TP->set_skill_extra(107, 0);
	TP->set_skill_extra(22, 0);
	return 0;
}

assure()
{
	if(!query_wielded(TO))
	   {
	   write("You look over the katana again and wonder why you " +
		"don't make use of such a superior weapon.\n");
	   return 1;
	   }
	write("Feeling more comfortable with this exotic blade, you take "
		+ "a couple of practice swings.  As you do so, you get " 
		+ "the impression that the katana has become an extension" 
		+ " of your arm, and of your spirit.\n");
	say(QCTNAME(TP) + " takes a couple of practice swings, showing "
		+ "a remarkable mastery of the exotic blade " 
		+ TP->query_pronoun()
		+" wields.\n");
	TP->command("peer know");
	return 1;
}
