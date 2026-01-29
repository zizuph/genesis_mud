/*
 * Farmer Maggot - Altrus, April 2005
 * Cotillion - 2020-09-29
 * - Fixed type confusion
 */
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

#define MUSH_PROP "_gathering_mushrooms"
#define ROOM_DIR "/d/Shire/maggot/rooms/"
#define ARM_DIR "/d/Shire/maggot/arm/"
#define WEP_DIR "/d/Shire/maggot/wep/"
#define NPC_BLOCK "_cant_go_there"

inherit SHIRE_MONSTER;

void create_shire_monster()
{
	set_name("maggot");
	add_name("_maggot");
	set_title("the turnip farmer");
	add_name("farmer maggot");
	set_race_name("hobbit");
	add_adj(({"stout","hard-working"}));
	set_long("This hobbit looks worn from years of hard labor in the fields, but not weak. He appears to be a stout, dour fellow. Best not give him any nonsense!\n");

	set_gender(0);
	set_appearance(60);
	set_alignment(200 + random(100));
	set_stats(({110, 80, 155, 70, 90, 60}));
	add_prop(CONT_I_WEIGHT, 35000);
	add_prop(CONT_I_HEIGHT, 600);
	add_prop("_cant_go_there", 1);

	set_skill(SS_DEFENCE, 50);
	set_skill(SS_PARRY, 20);
	set_skill(SS_UNARM_COMBAT, 60);
	set_skill(SS_WEP_POLEARM, 70);

	set_act_time(9);
	add_act("grumble .");
	add_act("peer suspiciously");
	add_act("stretch");
	add_act("mumble");

	set_chat_time(6);
	add_chat("Pesky kids, they're always after my mushrooms.");
	add_chat("Hmm... Looks like rough weather's in the makin'.");
	add_chat("No Bagginses here, I told him. Didn't like the look o' that one.");
	add_chat("If I catch just one more person trespassing...");

	add_ask(({"mushrooms"}), VBFC_ME("ask_quest_info"));

	set_introduce(1);

	equip(({
        ARM_DIR + ({"shirt_c", "shirt_h", "shirt_w"})[random(3)],
	    ARM_DIR + ({"pants_c", "pants_h", "pants_r"})[random(3)],
	    ARM_DIR + ({"vest_h", "vest_s", "vest_w"})[random(3)],
        WEP_DIR + ({"m_pitchfork", "m_hoe"})[random(2)],
    }));
}

public int introduce_me(string who)
{
	who = lower_case(who);
	if (!interactive(present(who,ENV(TO))))
		return 0;

	if(TP->query_prop(MUSH_PROP))
	{
		command("say Oh, so you are looking for those mushrooms Mrs. Maggot wants.");
		command("nod politely " + who);
		command("say Well, I wish I had them, but I caught one o' them kids walking through my fields again and had to chase him off.");
		command("say I am a bit winded at the moment. Do you mind gathering some for me?");
		command("say If you do, just run them back to Mrs. Maggot for me.");
		command("say They grow just inside the grove of trees at the southern end of my fields.");
	}

	else
	{
		command("shout Hey you! You're trespassing!");
		command("shout Get off my land!");
		TP->catch_msg("The dogs start running for you fast! Barking and growling they chase you out of the field.\n");
		say("The dogs chase " + QCTNAME(TP) + " right out of the field!\n");
		tell_room(ROOM_DIR + "maggotlane05", QCTNAME(TP) + " runs in from west, with three angry dogs in close pursuit.\n");
		TP->move_living("M", ROOM_DIR +"maggotlane05",1);
	}

	return 1;
}

string ask_quest_info()
{
	if(TP->query_prop(MUSH_PROP))
	{
		command("say Oh, so you are looking for those mushrooms Mrs. Maggot wants.");
		command("nod politely");
		command("say Well, I wish I had them, but I caught one o' them kids walking through my fields again and had to chase him off.");
		command("say I am a bit winded at the moment. Do you mind gathering some for me?");
		command("say If you do, just run them back to Mrs. Maggot for me.");
		command("say They grow just inside the grove of trees at the southern end of my fields.");
	}

	else
	{
		command("shout Hey you! You're trespassing!");
		command("shout Get off my land!");
		TP->catch_msg("The dogs start running for you fast! Barking and growling they chase you out of the field.\n");
		say("The dogs chase " + QCTNAME(TP) + " right out of the field!\n");
		tell_room(ROOM_DIR + "maggotlane05", QCTNAME(TP) + " runs in from west, with three angry dogs in close pursuit.\n");
		TP->move_living("M", ROOM_DIR +"maggotlane05",1);
	}

	return "";
}
