/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/potion";
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define CAST_LIMIT    80  /* The limit for this to become a success */
#define TP            this_player()
#define ETP           environment(TP)

/* Function name: sanare
* Description:   heals target of divine wound
* Arguments:     str -
* Returns:       1/0
*/
nomask mixed
sanare(string str)
{
    object who, *inv;
    int mana_limit, suc, i, strength;
    string *types;

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

    mana_limit = 80;
    if (who == TP) /* Costs more to heal yourself */
        mana_limit = 100;

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
    say(QCTNAME(TP) + " kneels down and prays.\n");
    who->heal_hp(100 + TP->query_skill(SS_ELEMENT_LIFE) + random(200));
    who->catch_msg("A divine power touches you.\n");
    who->catch_msg("You have been healed.\n");
    
    inv = all_inventory(who);
    strength = 200;
    types = ({ "all" });

    for (i=0; i<sizeof(inv); i++)
    {
        if (function_exists("cure_poison", inv[i]) == "/std/poison_effect")
        {
            inv[i]->cure_poison(types, strength);
            strength = strength / 2;
        }
    }

    return 1;
}
