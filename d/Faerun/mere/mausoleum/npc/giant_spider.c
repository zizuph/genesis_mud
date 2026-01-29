/* /d/Faerun/??/??/giant_spider.c
 *
 * Giant spider.
 *
 * Nerull 2017.
 */


inherit "std/monster";

#include "../dungeon_defs.h";
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

#define TYPE ({"menacning", "monstrous", "venemous", "lithe", \
"hulking", "towering"})
#define PHYS ({"eight-legged", "bulbous", "oozing", "poisnous", \
"disgusting", "forest", "bulging"})
#define EYES ({"soulless", "black", "grey", "white", "crimson"})


/*
 * Function name: create_monster()
 * Description  : Randomly selects monster type and sets the descriptors
 *                and stats for the monster.
 */
nomask void create_monster()
{
	string type, phys, eyes, skin, hair, hair2;
    int i;

    seteuid(getuid());

	type = one_of_list(TYPE);
	phys = one_of_list(PHYS);
	eyes = one_of_list(EYES);

	string npc_name = "spider";

	add_adj(type);
	add_adj(phys);
	add_prop(LIVE_I_NEVERKNOWN, 1);
	add_prop(LIVE_I_SEE_DARK, 1);

	// In lair, the spider has blindsight due to web
	// vibrations.
	add_prop(LIVE_I_SEE_INVIS, 99);

	add_prop(NPC_I_NO_FEAR, 1);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_NO_GENDER_DESC, 1);
	set_race_name("spider");
	set_gender(G_NEUTER);
	add_name(npc_name);
    add_name("_tomb_monster_");

	set_long("This " + phys + " " + type + " spider is a native dweller "
		+ "of the Mere of Dead Men. " + capitalize(query_pronoun()) + " has "
		+ "giant fangs that drip venom and " + eyes + " eyes. Known for "
		+ "their "
		+ "bloodlust and hatred of those who enter "
		+ "their forest realm, these spiders are not to be "
		+ "trifled with.\n");

	add_prop(CONT_I_WEIGHT, 110000);
	add_prop(CONT_I_HEIGHT, 180);

	set_stats(({ 150, 150, 150,
		         150, 150, 150 }));

	set_hitloc_unarmed(A_HEAD,  40, 15, "head");
	set_hitloc_unarmed(A_NECK,  40, 10, "coxa");
	set_hitloc_unarmed(A_BODY,  40, 10, "abdomen");
	set_hitloc_unarmed(A_WAIST, 40, 45, "thorax");
	set_hitloc_unarmed(A_LEGS,  40, 20, "legs");

	set_attack_unarmed(W_BOTH, 50, 50, W_IMPALE,
		100, "venomous fangs");
		
	set_attack_unarmed(W_LEFT, 40, 40, W_BLUDGEON,
		0, "left front foot");
	set_attack_unarmed(W_RIGHT, 40, 40, W_BLUDGEON,
		0, "right front foot");
	set_attack_unarmed(W_FOOTR, 40, 40, W_BLUDGEON,
		0, "right back foot");
	set_attack_unarmed(W_FOOTL, 40, 40, W_BLUDGEON,
		0, "left back foot");

	set_skill(SS_UNARM_COMBAT, 90);
	set_skill(SS_DEFENCE, 90);
	set_skill(SS_AWARENESS, 100);

	set_act_time(7);

	set_act_time(7);
    add_act("emote rubs its front legs against its mandibles.");
    add_act("glare");

    add_cact("emote glares at you with its set of black eyes.");

    add_cact("emote jumps at you!");

    add_cact("emote manoeuvers behind you!");

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    add_name("_tomb_monster");
	add_name("_tomb_spider");

	set_aggressive(1);
}















