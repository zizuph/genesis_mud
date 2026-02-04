/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* 
 * audire.c
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define TP       this_player()
#define TO       this_object()
#define BSN(xx)  break_string(xx + "\n", 72)

#define SPIRIT   "/d/Terel/mecien/valley/guild/spells/me"

#define MIN_WIS    55
#define MANA_COST  30
#define CAST_LIMIT 70

/* 
 * Function name: audire
 * Description:   summon a spirit (mystical ear)
 */
nomask mixed
audire(string str)
{
    int i, suc;
    object where, what;

    if (str) return "What?\n";

    if (TP->query_stat(SS_WIS) < MIN_WIS)
        return "You are not of high enough stature to attempt this yet.\n";

    if (TP->query_mana() < MANA_COST)
	return "You do not have the strength.\n";

    where = environment(TP);
    if (where->query_prop(ROOM_M_NO_MAGIC))
	return "This place seems to be protected.\n";

    suc = random(TP->query_skill(SS_FORM_CONJURATION));
    suc += random(TP->query_skill(SS_ELEMENT_AIR));
    if (suc < random(CAST_LIMIT))
    {
        write("Your call of summons to the mystic ear has failed.\n");
        TP->add_mana(-MANA_COST/3);
        return 1;
    }

    TP->add_mana(-MANA_COST);

    write("You invoke the spirit.\n");
    say(QCTNAME(TP) + " intones an ancient song.\n");

    seteuid(getuid());

    what = clone_object(SPIRIT);

    what -> set_caster(TP);
    what -> set_duration(60 + 2*(TP->query_stat(SS_WIS)));
    what -> move_living("M", where);

    return 1;
}
