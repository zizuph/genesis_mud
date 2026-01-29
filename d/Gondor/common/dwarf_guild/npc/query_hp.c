/*
 * /d/Gondor/common/dwarf_guild/query_hp.c
 *
 * This module is inherited into the Dwarves in the Rockfriend Guild.
 * When they get too hurt, they run away into a void, unreachable for
 * players.
 *
 * /Mercade, 30 August 1994
 *
 * Revision history:
 */

#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define PERCENTAGE 25
#define VOID       (DWARF_DIR + "virtual")

/* Global variable, it will not be saved.
 */
static int retreat_alarm_id = 0;

/*
 * Function name: query_hp
 * Description  : This is a mask of the original query_hp function. When
 *                the Dwarf is too hurt, he will flee into a void.
 * Returns      : int - the original hp-value.
 */
public int
query_hp()
{
    int hp = ::query_hp();

    if (!retreat_alarm_id && (hp < (PERCENTAGE * query_max_hp() / 100)))
    {
	set_alarm(2.0, 0.0, "retreat_to_void");
    }

    return hp;
}

/*
 * Function name: retreat_to_void
 * Description  : When the dwarf is too hurt, he will run away and hide
 *                from his enemies.
 */
nomask static void
retreat_to_void()
{
    retreat_alarm_id = 0;

    TELL_ROOM(ENV(), TO, " runs as far as " + POSSESSIVE(TO) +
	" legs can possibly carry " + OBJECTIVE(TO) + ".", TO);

    move_living("M", VOID, 1, 1);
}
