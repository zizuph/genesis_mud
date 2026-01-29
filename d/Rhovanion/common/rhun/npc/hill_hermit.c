inherit "/d/Rhovanion/lib/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include <composite.h>

void
enter_inv(object ob, object from)
{
        int n;
	string *names;

	::enter_inv(ob, from);
	if (!from)
		return;
	names = ob->query_names();
	if(names[sizeof(names) - 1] == "food") /* /std/food */
	   set_alarm(2.0, 0.0, "yummy", ({
		TP, ob
		}));
}

void
yummy(object player, object ob)
{
	player->add_prop("_i_have_given_food_",1);
	tell_room(environment(), QCTNAME(TO) + " eats the " + COMPOSITE_DEAD(({
		ob
	})) + ".\n");
	command("say Yummy!");
}

void
create_monster()
{
	object          ob;

	set_race_name("human");
	set_name("Zonk");
	set_adj("wise");
	add_adj("philosophical");
	add_adj("old");
	set_short("wise old human");

	set_alignment(800);
	set_gender(0);
	set_long("You've heard of hermits living in the mountains before, but this one really takes the"
		 + " price. He seems to live here, free of cares.\n");
	add_prop(CONT_I_WEIGHT, 72 * 1000);
	add_prop(CONT_I_VOLUME, 74 * 1000);
	add_prop(CONT_I_HEIGHT, 174);
	add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
	set_stats(({
		30, 30, 30, 150, 150, 30
	}));
	set_hp(query_max_hp());

	set_skill(SS_UNARM_COMBAT, 34);
	set_skill(SS_DEFENCE, 32);
	set_pick_up(43);

	set_act_time(5);
	add_act("emote admires the view.");
	add_act("emote ponders about the meaning of life.");
	add_act("eyebrow");
	add_act("say Knowledge is the greatest treasure of all.");
	add_act("say The wind tells me things no mortal know...");
	add_act("say Shared knowledge is double knowledge.");

	add_ask("shadowlord", VBFC_ME("hq_shadowlord"));
	add_ask("gemstone", VBFC_ME("hq_gemstone"));
	add_ask(({
		"coin", "obsidian coin"
	}), VBFC_ME("hq_coin"));
	add_ask("hag", VBFC_ME("hq_hag"));
	add_ask(({
		"Easterling", "Balchoths", "easterling", "balchoths "
	}), VBFC_ME(" hq_easterling "));
	add_ask("castle", VBFC_ME("hq_castle"));
	add_ask("ointment", VBFC_ME("hq_ointment"));
	add_ask(({
		"Spellweavers", "spellweavers"
	}), VBFC_ME("hq_spellweavers"));
}

string
hq_shadowlord()
{
	if (TP->query_prop("_i_have_given_food_"))
		command("say " +
			"The shadowlord lives in the castle. I know that it is so because I have seen him myself." +
			" He searches for an item of great worth that would increase his power manyfold." +
			" Sometimes he leaves the castle at night, searching, but never finding.");
	else
		command("say I am a bit hungry you know, if you give me some food I'll answer your question.");
	TP->remove_prop("_i_have_given_food_");
	return "";
}


string
hq_gemstone()
{
	if (TP->query_prop("_i_have_given_food_"))
		command("say " +
			"The gemstone is what the shadowlord seeks. It is a thing of the shadows, and yet shadow is but a part" +
			" of darkness. The wind whisper to me at night sometimes about its resting place. West of the Mirkwood," +
			" east of the Misty Mountains, blows the wind.");
	else
		command("say I am a bit hungry you know, if you give me some food I'll answer your question.");
	TP->remove_prop("_i_have_given_food_");
	return "";
}

string
hq_hag()
{
	if (TP->query_prop("_i_have_given_food_"))
		command("say " +
			"Ahh, the birds have told me of the hag. She has strayed from the path of good and lost herself" +
			" in the labyrinth of evil. She seeks an obsidian coin, an obsession the birches say.");
	else
		command("say I am a bit hungry you know, if you give me some food I'll answer your question.");
	TP->remove_prop("_i_have_given_food_");
	return "";
}

string
hq_coin()
{
	if (TP->query_prop("_i_have_given_food_"))
		command("say " +
			"Many years ago an eager young noble, fascinated by the lure of darkness, passed through here. Headed for the" +
			"castle, he was, but he stopped here, foolishly thinking I could assist him in attaining dark forces." +
			" When I told him I would not assist him in such matters, he proffered to pay me an obsidian coin, an" +
			" object of incalculable worth he said. I refused and he left, not wishing to fight me on such a narrow" +
			" ledge. He continued on to the castle to the west, and I never saw him again.");
	else
		command("say I am a bit hungry you know, if you give me some food I'll answer your question.");
	TP->remove_prop("_i_have_given_food_");
	return "";
}

string
hq_easterling()
{
	if (TP->query_prop("_i_have_given_food_"))
		command("say " +
			"The Easterlings have a tower in the southern part of the Taur Romen. It acts as their base of operations when" +
			" they raid the land around the Sea of Rhun.");
	else
		command("say I am a bit hungry you know, if you give me some food I'll answer your question.");
	TP->remove_prop("_i_have_given_food_");
	return "";
}

string
hq_spellweavers()
{
	if (TP->query_prop("_i_have_given_food_"))
		command("say " +
			"The Spellweavers are a secretive fellowship of evil sorcerers. They serve dark powers, which in turn" +
			" serve them. The origin of the guild is lost to most people, and now even their existence is unknown of" +
			" in many parts of Rhovanion.");
	else
		command("say I am a bit hungry you know, if you give me some food I'll answer your question.");
	TP->remove_prop("_i_have_given_food_");
	return "";
}

string
hq_ointment()
{
	if (TP->query_prop("_i_have_given_food_"))
		command("say " +
			"Such ointments are sometimes used to make the usage of runes easier for those not familiar with them.");
	else
		command("say I am a bit hungry you know, if you give me some food I'll answer your question.");
	TP->remove_prop("_i_have_given_food_");
	return "";
}

string
hp_castle()
{
	if (TP->query_prop("_i_have_given_food_"))
		command("say " +
			"Many a nights have I watched the castle spreading it's lurking evil across the land. The shadowlord resides" +
			" there.\n");
	else
		command("say I am a bit hungry you know, if you give me some food I'll answer your question.");
	TP->remove_prop("_i_have_given_food_");
	return "";
}










