/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * This spell makes the player/npc faster or slower in combat
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <comb_mag.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP              this_player()
#define ETP             environment(TP)
#define TO              this_object()
#define CAST_LIMIT      50
#define MANA_COST       20
#define MANA_COST_OTHER 30
#define SNAME           "Vires"
#define STD_RET         (SNAME+" how on who?\n")

/* Function name: vires
 * Description:   increase/decrease combat speed for a while
 * Arguments:     str - who how
 * Returns:       mixed (1/0 or failure msg string)
 */
nomask mixed
vires(string str)
{
    object speed, who=0;
    object *ob;
    int mana_cost, suc, dur, sign, quick;
    string dum="who", how;

    if (!str) return STD_RET;

    if (sscanf(str, "%s on %s", how, dum) == 2)
        if (dum == "me" || dum == "myself") who = TP;

    if (!who) {
        if (!parse_command(str, ETP, " %w 'on' %l ", how, ob))
            return STD_RET;
        if (sizeof(ob) <= 1)
            return STD_RET;
        else {
            who = ob[1];
            if (!CAN_SEE(TP, who)) return STD_RET;
        }
    }

    if (how == "more" || how == "increase") {
        sign = 1;
    } else if (how == "less" || how == "decrease") {
        sign = -1;
    } else {
        return SNAME+" how on "+dum+"?\n";
    }

    if (NPMAGIC(who)) return "Somehow your spell fails.\n";
    
    if (sign == -1 && NPMATTACK(who))
        return "Somehow your spell fails.\n";

    if (who == TP) {
        mana_cost = MANA_COST;
    } else {
        mana_cost = MANA_COST_OTHER;
    }

    if (TP->query_mana() < mana_cost)
        return "You do not have the mental strength.\n";

    suc  = random(TP->query_skill(SS_SPELLCRAFT));
    suc += random(TP->query_skill(SS_ELEMENT_LIFE));
    if (who != TP && sign == -1)
        suc -= who->query_skill(SS_FORM_ABJURATION);
    if (suc < random(CAST_LIMIT)) {
        TP->add_mana(-mana_cost / 3);
        return "Your call is not heard.\n";
    }
    TP->add_mana(-mana_cost);
    if (who == TP) {
        write("You invoke the ancient energy on yourself.\n");
    } else {
        TP->catch_msg("You invoke the ancient energy on " +
                      QTNAME(who) + ".\n");
    }
    say(QCTNAME(TP) + " mumbles something.\n");

    seteuid(getuid());
    speed = clone_object(SPELL_DIR + "speed_obj");

    dur = 20 + TP->query_stat(SS_INT) + TP->query_stat(SS_WIS);
    if (who != TP) dur -= who->query_skill(SS_FORM_ABJURATION);
    speed->set_duration(dur);

    if (sign == 1) {
        quick = TP->query_skill(SS_ELEMENT_LIFE)/4;
        quick++;
    } else {
        quick = -(TP->query_skill(SS_ELEMENT_DEATH))/4;
        quick--;
    }
    speed->set_quickness(quick);

    speed->move(who);
    if (sign == -1 && !interactive(who) && random(2) == 0)
        who->command("kill " + TP->query_real_name());
    return 1;
}
