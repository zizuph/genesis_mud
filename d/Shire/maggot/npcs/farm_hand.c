/*
 * Farm hand on Maggot's farm
 * Altrus, April 2005
 *
 * Cotillion - 2020-09-29
 * - Fixed type confusion
*/
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

#define ROOM_DIR "/d/Shire/maggot/rooms/"
#define ARM_DIR "/d/Shire/maggot/arm/"

inherit SHIRE_MONSTER;

string get_adjective_one();
string get_adjective_two();

void create_shire_monster()
{
	set_name("hobbit");
	set_race_name("hobbit");
	set_adj(({get_adjective_one(), get_adjective_two()}));
	set_long("This hobbit looks like he has been working on the farm for many a year and still appears to be in high spirits.\n");

	set_gender(0);
	set_appearance(70);
	set_alignment(200 + random(100));
	set_stats(({70 + random(20), 125 + random(50), 50 + random(25), 70 + random(10), 90 + random(10), 60 + random(10)}));
	add_prop(CONT_I_WEIGHT, 35000 +random(500));
	add_prop(CONT_I_HEIGHT, 600 + random(20));

	set_skill(SS_DEFENCE, 50);
	set_skill(SS_PARRY, 20);
	set_skill(SS_UNARM_COMBAT, 60);

	set_act_time(7);
	add_act("whistle");
	add_act("time");
	add_act("stretch");
	add_act("hum");
	add_act("sigh tiredly");

	set_chat_time(6);
	add_chat("Well now, couldn't ask for a better day.");
	add_chat("The boss tells me what to do, and I do it. Can't get an easier life than that.");
	add_chat("Workin' the farm is hard on the body, but it's great for the appetite!");
	add_chat("We don't want any trouble from strangers out here.");

	add_ask(({"mushrooms"}), VBFC_ME("ask_quest_info"));

	set_introduce(0);

	equip(({
        ARM_DIR + ({"shirt_c", "shirt_h", "shirt_w"})[random(3)],
	    ARM_DIR + ({"pants_c", "pants_h", "pants_r"})[random(3)],
	    ARM_DIR + ({"vest_h", "vest_s", "vest_w"})[random(3)],
    }));

    // changes messages for moving in and out of rooms
	set_m_out("ambles");
    set_m_in("ambles in");

}

string ask_quest_info()
{
	command("say I wouldn't be knowing where the boss keeps his mushrooms. He likes to keep that a secret.");
	command("apologize .");
	command("say You should probably to talk to him about it, but I reckon that he wont be takin' to kindly to you for it.");
	return "";
}

public string get_adjective_one()
{
	string *adjectives, adj;

	adjectives = ({"sandy-haired", "proud", "merry", "smiling", "nimble", "cheerful", "blue-eyed", "curly-haired","chatty", "small", "good-natured", "friendly", "sharp-eyed", "green-eyed", "hungry", "short", "brown-eyed", "round-faced", "ruddy-faced", "happy", "tired", "agile", "jolly", "energetic", "cheerful", "nimble", "inquisitive","jovial"});

	adj = adjectives[random(sizeof(adjectives))];

	return adj;
}

public string get_adjective_two()
{
	string *adjectives, adj;

	adjectives = ({"hard-working", "industrious", "sweat-stained", "sun-burned", "rugged", "stout"});

	adj = adjectives[random(sizeof(adjectives))];

	return adj;
}
