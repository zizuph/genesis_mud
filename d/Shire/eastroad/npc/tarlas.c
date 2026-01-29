/* 
 * The Innkeeper at The Foaming Mug, in Waymeet.
 * Cloned by /d/Shire/eastroad/foam_mug.c
 */

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

create_monster()
{
	if (!IS_CLONE)
		return;

	set_name("tarlas");
	add_name(({"innkeeper", "_foaming_mug_innkeeper_"}));
	set_title("Innkeeper of the Foaming Mug");
	set_race_name("hobbit");
	set_adj(({"fat", "happy"}));
	set_long(
		"This merry hobbit stands behind the bar in the inn, "+
		"serving all the thirsty travellers.  He is wearing a dirty "+
		"apron, that he occasionally uses to polish glasses with.\n");
	default_config_npc(30);
	set_base_stat(SS_DIS, 40);
	set_base_stat(SS_DEX, 40);

	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_DEFENCE, 30);
	set_skill(SS_AWARENESS, 20);
	set_alignment(200 + random(50));

	add_prop(CONT_I_WEIGHT, 60*1000); //100 Kg's.
	add_prop(CONT_I_HEIGHT, 100);		//170 cm tall.
	
	set_act_time(2);
	add_act("smile");
	add_act("emote polishes a glass with his apron.");
	add_act("laugh");
	add_act("emote carefully arranges the bottles behind the bar.");
	add_act("emote smiles at you.");
	add_act("say What can I get you to drink?");

}

