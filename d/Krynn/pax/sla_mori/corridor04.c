/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 * 
 * Navarre: January 28th 2014: Removed if (!random(4)){ ... } around cloning 
 *                             The slug, he shouldn't be rare.
 */
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit PAXINROOM;

int gSlug_found = 0, gPaper_found = 0;
object gSlug;

void
reset_pax_room()
{
    gSlug_found = 0;
    gPaper_found = 0;
}

void
create_pax_room()
{
    set_short("West end of corridor");
    set_long("You are at the west end of a corridor, it has been caved in " +
	"by the Cataclysm. Boulders the size of houses are wedged together " +
	"to form an impenetrable wall. The corridor extends further to " +
	"the east. The air in the corridor is stale and musty, loose boulders " +
	"and stones litter the floor, a wide path runs down the center of the " +
	"corridor to the east.\n");

    add_item(({"stone", "boulder", "boulders"}), "@@my_boulder");

    add_item("path", "This path is free of any speck of dust and stones.\n");

    add_exit(PSLA + "corridor03", "east");

    add_prop(ROOM_I_LIGHT, 0);

    seteuid(getuid());
    enable_reset(120);
}

static void
wound_player(object who, object attacker)
{
    who->heal_hp(-100 - random(50));

    if (who->query_hp() == 0)
	who->do_die(attacker);
}

public string
my_boulder()
{
    object paper, key, enemy;

    enemy = TP;

    if (!gSlug_found)
    {
	gSlug = clone_object(PMONSTER + "slug");
	gSlug->move(TO);

	gSlug_found = 1;

        set_alarm(1.0, 0.0, "wound_player", enemy, gSlug);

        tell_room(TO, "A giant slug slither out from behind on " +
                "of the boulders and attacks " + QCTNAME(enemy) +
                "\n", enemy);

	gSlug->attack_object(enemy);

        enemy->catch_msg("As you are feeling around one of the " +
            "boulders, you feel a great pain in your right arm. " +
            "Something has biten you! Suddenly a giant slug " +
            "slithers out from behind one of the boulders " +
            "and attacks you!\n");
        return "";
    }

    if (!gPaper_found)
    {
	gPaper_found = 1;

	paper = clone_object(POBJ + "paper");
	paper->move(enemy);

	key = clone_object(POBJ + "final_key");
	key->move(enemy);

        TELL_ROOM(TO, enemy, " finds something behind a boulder.", enemy);

	enemy->catch_msg("When looking behind one of the big boulders " +
            "you find a piece of paper and a silver key.\n");

        return "";
    }

    return "The boulders looks quite normal, " +
	"big but normal.\n";
}
