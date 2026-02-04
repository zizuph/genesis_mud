/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/*
 * This spell creates a fake weapon.
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <language.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP            this_player()
#define TO            this_object()
#define ETP           environment(TP)
#define CAST_LIMIT    50
#define MANA_COST     21
#define FAKE_DIR      SPELL_DIR + "fake/"
#define FAKE_PROP     "_mystic_fake_"

/* Function name: simulacrum
 * Description:   a player creates a fake weapon
 * Arguments:     str - weapon type (i.e. knife, sword, etc.)
 * Returns:       mixed (1/0 or failure msg string)
 */
nomask mixed
simulacrum(string str)
{
    object weapon;
    int mana_limit, no_times, suc, dur;

    if (!str) return "Create what?\n";

    if (file_size(FAKE_DIR+"f_"+str+".c") == -1) return "Create what?\n";

    mana_limit = MANA_COST;
    if (TP->query_mana() < mana_limit)
        return "You do not have the strength.\n";
    if (NPMAGIC(TP))
        return "Somehow your spell fails.\n";

    no_times = TP->query_prop(FAKE_PROP);
    suc  = random(TP->query_skill(SS_FORM_ILLUSION));
    suc += random(TP->query_skill(SS_ELEMENT_EARTH));
    if (!T_WIZ(TP)) suc /= (no_times + 1);
    if (suc < random(CAST_LIMIT)) {
        TP->add_mana(-mana_limit / 3);
        return "Your call is not heard.\n";
    }

    TP->add_mana(-mana_limit);
    write("You invoke the ancient spirits.\n");
    say(QCTNAME(TP) + " intones a mystic chant.\n");

    dur = 30 + 3*(random(TP->query_skill(SS_FORM_ILLUSION)) +
                  TP->query_stat(SS_WIS));
    seteuid(getuid());
    weapon = clone_object(FAKE_DIR + "f_" + str);
    weapon->set_duration(dur);
    write(capitalize(LANG_ADDART(weapon->short())) + " forms in your hand.\n");
    if (weapon->move(TP)) {
        weapon->move(ETP);
        write("The "+weapon->short()+
              " is too heavy for you. You drop it.\n");
        say(QCTNAME(TP) + " drops " + LANG_ADDART(weapon->short()) + ".\n");
    }
    if (no_times) {
        TP->change_prop(FAKE_PROP, (no_times + 1));
    } else {
        TP->add_prop(FAKE_PROP, 1);
    }
    return 1;
}
