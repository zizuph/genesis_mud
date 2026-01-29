/* Patrol 'K-9' Turtle by Karath */

inherit "/d/Emerald/std/emerald_guard_creature";

#include "/d/Emerald/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define ECLIPSIA_OBJ "/d/Emerald/eclipsia/obj/"

void
create_emerald_creature()
{
	set_race_name("sea-turtle");
	add_name("turtle");


/* randomly male or female */
	set_gender(random(2));
	add_adj( ({ "giant", "sea", "spotted" }) );
	set_short("giant spotted sea-turtle");
	set_long("This gentle giant of the sea floats peacefully "+
		"through the waters. It seems to bear no malice to "+
		"any living thing, yet when you look into it's eyes, "+
		"you see no laziness, only watchful alertness. "+
		"Despite it's unagressivness, you make a point to "+
		"not provoke it.\n");

/* quite strong, mediocre dex, quite healthy, low int/wis med dis */
	set_stats( ({ 150, 50, 150, 35, 35, 50 }) );

	add_prop(LIVE_I_SEE_DARK, 1);
	add_prop(LIVE_I_NEVERKNOWN, 1);

/* emeraldian...trained by elves...and posesses a bit of innate */
/* resistance to water magic					*/
	add_prop(MAGIC_I_RES_WATER, 10);

/* Not really...but can hold breath indefinately for purposes */
/* of playibility					      */
	add_prop(MAGIC_I_BREATH_WATER, 1);

	set_skill(SS_DEFENCE, 30);
	set_skill(SS_BLIND_COMBAT, 60);
	set_skill(SS_AWARENESS, 50);
	set_skill(SS_UNARM_COMBAT, 70);

	set_hitloc_unarmed(1, 60, 45, "hard shell");
	set_hitloc_unarmed(2, 20, 20, "head");
	set_hitloc_unarmed(3, 5, 10, "underbelly");
	set_hitloc_unarmed(4, 10, 6, "left frontal flipper");
	set_hitloc_unarmed(5, 10, 6, "right frontal flipper");
	set_hitloc_unarmed(6, 10, 6, "left dorsal flipper");
	set_hitloc_unarmed(7, 10, 6, "right dorsal flipper");
	set_hitloc_unarmed(8, 1, 1, "tail");

	set_attack_unarmed(1, 30, 50, W_IMPALE|W_SLASH, 76, "snapping jaws");
	set_attack_unarmed(2, 40, 20, W_BLUDGEON, 12, "left frontal flipper");
	set_attack_unarmed(3, 40, 20, W_BLUDGEON, 12, "right frontal flipper");

	set_act_time(4);
	add_act("emote slowly swims next to you.");
	add_act("emote watches you with vague interest.");
	add_act("emote slowly decends to grab a piece of kelp floating in "+
		"the water");

	add_leftover(ECLIPSIA_OBJ + "turtle_shell");
}

void
assist(object enemy)
{
    command("stare impat at " + enemy->query_real_name());
    tell_room(environment(TO), "The " + short() + " joins the fray!\n");
}
