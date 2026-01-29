/*
	*Fishing hobbit
	*Altrus, June 2005
*/
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/fishing/defs.h"

inherit SHIRE_MONSTER;

void create_shire_monster()
{
	set_name("lucky");
	set_title("Bolger");
	set_race_name("hobbit");
	add_adj(({"amiable","lazy"}));
	set_long("This little fellow seems like a friendly chap. He seems to be enjoying himself, fishing away the day in solitude.\n");
	
	set_gender(0);
	set_appearance(60);
	set_alignment(300 + random(100));
	set_stats(({90, 80, 90, 40, 50, 25}));
	add_prop(CONT_I_WEIGHT, 35000);
	add_prop(CONT_I_HEIGHT, 500);
	
	set_act_time(9);
	add_act("stretch");
	add_act("emote looks like he is trying to keep his heavy-lidded eyes open.");
	add_act("whistle merrily");
	add_act("emote casts a line into the pond.");
	add_act("emote pulls on his line for a moment.");
	add_act("grin sheepishly");
	
	set_chat_time(8);
	add_chat("Ah! Nothin' like fishin' the day away!");
	add_chat("I don't suppose you like to fish?");
	add_chat("Don't trust anyone who doesn't like to fish.");
	add_chat("I oughta head over to the Brandywine, see if'n I can land me a nice fat channel cat.");
	add_chat("Heard the perch were biting over at the lake.");
	add_chat("Can't beat fishin' when the cares of the world get to heavy.");
	
	//add_ask(({""}), VBFC_ME(""));
	//add_ask(({""}), VBFC_ME(""));
	//add_ask(({""}), VBFC_ME(""));
	
	set_introduce(1);
	
	clone_object(OBJ_DIR + "shirt")->move(TO);
	clone_object(OBJ_DIR + "pants")->move(TO);
	clone_object(OBJ_DIR + "vest")->move(TO);
	clone_object(OBJ_DIR + "hat")->move(TO);
	clone_object(OBJ_DIR + "hobbit_pole")->move(TO);
	
	command("wear armours");
	command("wield weapons");
}
