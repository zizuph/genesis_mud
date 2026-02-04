/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * imago.c
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"
#include "/d/Terel/mecien/valley/guild/spells/spells.h"

#define TP       this_player()
#define ETP      environment(TP)

/* Function name: imago
 * Description:   looks at the spiritual aura of the target
 * Arguments:     str - name of target
 * Returns:       failure string or 1
 */
nomask mixed
imago(string str)
{
    object who, *obs;
    int mana_limit, align, suc;
    string aura;

    if (!str) return "Whom shall you focus upon?\n";

    if (str == "me" || str == "myself")
        who = TP;
    else {
        if (!parse_command(lower_case(str), ETP, " %l ", obs))
            return "Whom shall you focus upon?\n";
        if (sizeof(obs) <= 1)
            return "Whom shall you focus upon?\n";
        else {
            who = obs[1];
            if (!CAN_SEE(TP, who)) return "Whom shall you focus upon?\n";
        }
    }

    if (NPMAGIC(who)) /* Are we allowed to cast a magic spell? */
        return "Some other power prevents you.\n";

    if (who == TP) /* Costs less to see your own aura. */
        mana_limit = IMAGO_SELF_MANA;
    else
        mana_limit = IMAGO_OTHER_MANA;

    if (TP->query_mana() < mana_limit)
        return "You do not have the strength to look within.\n";

    suc  = TP->query_skill(SS_FORM_DIVINATION);
    suc += TP->query_stat(SS_WIS);
    if (who != TP)
        suc -= who->query_skill(SS_FORM_ABJURATION);
    if (random(suc) < random(IMAGO_CAST_LIMIT))
    {
        TP->add_mana(-mana_limit/3);
        return "You were unable to see within.\n";
    }

    TP->add_mana(-mana_limit);

    write("You seek the inner visions of the soul.\n");
    say(QCTNAME(TP) + " gazes upwards with eyes glazed over with "
      +"a luminous white glow.\n");
    if (who != TP)
        who->catch_msg(QCTNAME(TP) + " looks within your soul.\n");

    if (who->query_wiz_level() <= TP->query_wiz_level()) {
        switch (who->query_alignment())
        {
            case -9999..-750:
                aura = "jet-black abyssmal"; break;
            case -749..-500:
                aura = "perilous black and purple"; break;
            case -499..-300:
                aura = "dreadful crimson"; break;
            case -299..-100:
                aura = "corrupted yellow"; break;
            case -99..-30:
                aura = "darkened gray"; break;
            case -29..29:
                aura = "gray"; break;
            case 30..99:
                aura = "soft pleasant green"; break;
            case 100..299:
                aura = "sparkling blue"; break;
            case 300..499:
                aura = "graceful pale silvery"; break;
            case 500..749:
                aura = "luminous golden"; break;
            case 750..9999:
                aura = "pure brilliant white"; break;
            default:
                aura = "strange unfathomable"; break;
        }
    } else {
        aura = "strange unfathomable";
    }
    if (who == TP)
        TP->catch_msg("A " + aura + " aura emanates from you.\n");
    else
        TP->catch_msg("A " + aura + " aura emanates from within " +
            QTNAME(who) + ".\n");
    if (who->query_skill(CURSED)) {
        TP->catch_msg("The soul of " + QTNAME(who) +
                      " bears the curse of the Ancients.\n");
    }

    return 1;
}
