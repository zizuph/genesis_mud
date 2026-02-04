/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * This spell invokes a mystic poison on the mystic weapons
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <poison_types.h>
#include <cmdparse.h>

#define TP            this_player()
#define TO            this_object()
#define CAST_LIMIT    60
#define MANA_COST     100
#define SPELL_DIR     "/d/Terel/mecien/valley/guild/spells/"

/* Function name: venenare
 * Description:   make a mystic weapon poisoneous
 * Arguments:     str - weapon
 * Returns:       mixed (1/0 or failure msg string)
 */
nomask mixed
venenare(string str)
{
    object *obs;
    object where, weapon, poi;
    int mana_limit, suc, dur, strength, dam;
    int no_times;

    where = environment(TP);
    if (where->query_prop(ROOM_M_NO_MAGIC)) return 0;

    if (!str) return "Venenare what?\n";

    obs = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(obs)) return "Venenare what?\n";
    weapon = obs[0];
    if (!(weapon->query_prop("mystic_weapon")))
	return "Poisoning the "+weapon->short()+" doesn't work!\n";
    if (!(weapon->query_prop("poison_holder")))
	return "Poisoning the "+weapon->short()+" doesn't work!\n";
    if (weapon->query_poison())
	return "The "+weapon->short()+" is already poisoned!\n";

    mana_limit = MANA_COST + TP->query_skill(SS_ELEMENT_DEATH)/3;
    if (TP->query_mana() < mana_limit)
        return "You do not have the strength.\n";

    no_times = weapon->query_prop("poison_no_times");
    suc  = random(TP->query_skill(SS_SPELLCRAFT));
    suc += random(TP->query_skill(SS_ELEMENT_DEATH));
    if (suc < random(CAST_LIMIT) + 8*no_times) {
        TP->add_mana(-mana_limit / 3);
        return "Your call is not heard.\n";
    }

    TP->add_mana(-mana_limit);
    write("You invoke the ancient spirits.\n");
    say(QCTNAME(TP) + " intones a mystic chant.\n");

    seteuid(getuid(TO));
    poi = clone_object("/std/poison_effect.c");
    dur = 65 + 3*(TP->query_stat(SS_WIS));
    strength = 15 + TP->query_skill(SS_ELEMENT_DEATH);
    dam = 20 + TP->query_stat(SS_INT)/2;
    poi->set_time(dur);
    poi->set_interval(30);
    poi->set_strength(strength);
    poi->add_prop("mystic_poison", 1);
    poi->set_damage(({POISON_HP, dam, POISON_STAT, SS_CON}));

    weapon->set_poison(poi);
    if (no_times) {
        weapon->change_prop("poison_no_times", (no_times + 1));
    } else {
        weapon->add_prop("poison_no_times", 1);
    }
    write("Your "+weapon->short()+" has become more deadly.\n");

    return 1;
}
