/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * This spell turns the player into an animal.
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP            this_player()
#define TO            this_object()
#define CAST_LIMIT    50
#define MANA_COST     (["bear":120, "cricket":100, "wolf":60,\
                        "owl":40, "serpent":250])
#define IMMUTO_DIR    (SPELL_DIR + "immuto/")

/* Function name: immuto
 * Description:   transform a player into an animal for a while
 * Arguments:     str - animal
 * Returns:       mixed (1/0 or failure msg string)
 */
nomask mixed
immuto(string str)
{
    object animal, control, room, who;
    int mana_limit, suc, dur;
    string dum;

    if (!str) return "Immuto into what?\n";

    who = TP;
    if (TP->query_wiz_level()) {
        if (parse_command(str, environment(TP),
            " %o [into] %s ", who, dum)) {
            str = dum;
        } else {
            if (sscanf(str, "into %s", dum)==1) str = dum;
        }
        if (!interactive(who)) return "Immuto who?\n";
    } else {
        if (sscanf(str, "into %s", dum)==1) str = dum;
    }

    if (NPMAGIC(who))
        return "Somehow your spell fails.\n";

    if (file_size(IMMUTO_DIR + str + ".c") == -1 ||
        file_size(IMMUTO_DIR + "soul_" + str + ".c") == -1) {
        if (who == TP)
            return "Immuto into what?\n";
        else
            return "Immuto "+who->query_name()+" into what?\n";
    }

    if (str == "serpent" &&
          !(TP->query_wiz_level() > 0 ||
            TP->query_mystic_rank() == MYSTIC_PATRIARCH))
        return "Immuto into what?\n";

    mana_limit = MANA_COST[str];
    if (TP->query_mana() < mana_limit)
        return "You do not have the strength.\n";

    suc  = random(TP->query_skill(SS_FORM_TRANSMUTATION));
    suc += random(TP->query_skill(SS_ELEMENT_LIFE));
    if (who != TP) suc -= who->query_skill(SS_FORM_ABJURATION);
    if (suc < random(CAST_LIMIT)) {
        TP->add_mana(-mana_limit / 3);
        return "Your call is not heard.\n";
    }

    TP->add_mana(-mana_limit);
    write("You invoke the ancient spirits.\n");
    say(QCTNAME(TP) + " intones a mystic chant.\n");

    seteuid(getuid(TO));
    control = clone_object(IMMUTO_DIR + "transf_npc");
    animal  = clone_object(IMMUTO_DIR + str);
    room    = clone_object(IMMUTO_DIR + "void");

    dur = 60 + TP->query_stat(SS_INT) + TP->query_stat(SS_WIS) +
          random(10);
    if (who != TP) dur -= who->query_skill(SS_FORM_ABJURATION);
    control->set_duration(dur);
    control->set_void_room(room);

    animal->set_animal_soul(IMMUTO_DIR + "soul_" + str);
    animal->set_player_link(who, control);
    
    return 1;
}
