/* 
 * The Innkeeper at the Forsaken Inn, east of Bree.
 * Cloned by /d/Shire/eastroad/fors_inn.c
 */

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

create_monster()
{
	if (!IS_CLONE)
		return;

	set_name("scoffer");
	add_name(({"innkeeper", "_forsaken_innkeeper_"}));
	set_title("Renowned thief and brewer");
	set_race_name("human");
	set_adj(({"squint-eyed", "ignoring"}));
	set_long(
		"This appears to be the innkeeper here at the Forsaken Inn. "+
		"He serves thieves, scoundrels and those whom dare enter this "+
		"this place drinks. He makes most of the drinks you can find "+
		"on the menu all by himself. He looks lazy, and almost completely "+
		"ignoring. He has a bloodied mark around his left eye, and lacks "+
		"hair completely. He is chewing on something.\n");
	default_config_npc(50);
	set_base_stat(SS_DIS, 60);
	set_base_stat(SS_DEX, 40);

	set_skill(SS_UNARM_COMBAT, 50);
	set_skill(SS_DEFENCE, 40);
	set_skill(SS_AWARENESS, 50);

	add_prop(CONT_I_WEIGHT, 100*1000); //100 Kg's.
	add_prop(CONT_I_HEIGHT, 170);		//170 cm tall.
	add_prop(NPC_I_NO_LOOKS, 1);	//looks ugly.
	
	set_act_time(2);
	add_act("fart");
	add_act("emote spits some brown, thick liquid into the bucket.");
	add_act("burp");
	add_act("shout BUY MY SPECIAL BREW FOR A SPECIAL PRICE!");
	add_act("emote doesn't seem to pay attention to you at all.");
	add_act("say What business have you in here?");
	add_act("say I don't like the looks of you!");
	add_act("emote spits in a glass.");
	add_act("stretch");

}

