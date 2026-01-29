/*
 * Alchemist for the Thwil potion shop
 * Ckrik July 2014
 * Fix me: Add Wizard of Roke specials and spells
 */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <composite.h>
#include "defs.h"
inherit "/d/Earthsea/lib/intro";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/std/monster";

void create_earthsea_monster()
{
	set_name("jora");
	set_race_name("human");
	set_living_name("_herbalist_");
	set_title("of Ossikil, Senior Wizard Apprentice");
	add_name("alchemist");
	add_name("apprentice");
	add_adj(({"dour", "short"}));
	set_gender(G_MALE);
	set_height("short");
	set_width("lean");
	set_long("A dour short apprentice of the Wizard's " +
			"School of Roke. He is one of the older apprentices " +
			"and more seasoned in the arts of Roke wizardry. " +
			"Master Herbal has put him in charge of the " +
			"school's potion store.\n");
	add_prop(OBJ_M_NO_ATTACK, QCTNAME(this_object()) + " looks at you " +
			"strangely, and you feel suddenly embarrassed.\n");
	add_prop(OBJ_M_NO_MAGIC_ATTACK, "Your spell is dissipated by the magic " +
			"cast in this room.\n");
	set_default_answer(QCTNAME(this_object()) + " says: I don't understand "+
			"your question.\n");
	add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
	set_stats(({100, 140, 100, 145, 145, 140}));
	set_all_hitloc_unarmed(50);
	set_hp(query_max_hp());
	set_skill(SS_DEFENSE, 60);
	set_skill(SS_PARRY, 50);
	set_skill(SS_WEP_POLEARM, 90);
	set_skill(SS_UNARM_COMBAT, 80);
	set_skill(SS_AWARENESS, 35);
	set_skill(SS_BLIND_COMBAT, 50);
	set_alignment(1000);
	set_act_time(50);

	add_act("emote casts a spell and a shadow of gloom appear behind him.");
	add_act("say Roke magic is the oldest and most respected " +
			"in all the realms.");
	add_act("say Wizards trained by Roke serve different lands all " +
			"throughout the realms.");
	add_act("emote studies a dark mirky potion carefully.");
}
