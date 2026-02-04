/* Creative rights reserved to Mecien (Jeff Babcock) and team. */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define CAST_LIMIT    30   /* The limit for this to become a success */
#define SPELL_DIR     "/d/Terel/mecien/valley/guild/spells/"
#define TP            this_player()
#define ETP           environment(TP)

/* Function name: mederi
 * Description:   heals target of small wound
 * Arguments:     str -
 * Returns:       1/0
 */
nomask mixed
mederi(string str)
{
    object who;
    int mana_limit, suc;

    if (str)
        who = present(lower_case(str), ETP);
    if (!who)
    {
        if (!str || str == "myself" || str == "me")
            who = TP;
        else
            return "Who shall you heal?\n";
    }
    
    if (who != TP && !CAN_SEE(TP, who))
        return "Who shall you heal?\n";

    if (NPMAGIC(who)) /* See if it is possible to cast a magic spell on obj. */
        return "Something prevents you from cast this spell.\n";

    mana_limit = 30;
    if (who == TP) /* Costs more to heal yourself */
        mana_limit = 40;

    if (TP->query_mana() < mana_limit)
        return "You do not have the strength to call out.\n";

    suc = TP->query_skill(SS_FORM_ABJURATION) +
          TP->query_skill(SS_ELEMENT_LIFE);
    if (random(suc) < random(CAST_LIMIT))
    {
        write("Your call is not heard.\n");
        TP->add_mana(-mana_limit / 3);
        return 1;
    }

    TP->add_mana(-mana_limit);
    write("You invoke the healing powers of the Ancients.\n");
    say(QCTNAME(TP) + " speaks a mystic word.\n");
    who->heal_hp(25 + random(TP->query_skill(SS_ELEMENT_LIFE)/2));
    who->catch_msg("You receive a small healing.\n");
    return 1;
}
