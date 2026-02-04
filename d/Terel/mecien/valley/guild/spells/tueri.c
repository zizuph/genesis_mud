/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/* This spells summons a magic shield to protect a player. It works as
 * a forcefield protecting from blows. The duration of the shield depends
 * on the intelligence of the caster. Defence spell skill and wisdom
 * controls if this is a success. The magic shiled has an ac of 10.
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define CAST_LIMIT    50   /* The limit for this to become a success */
#define TP            this_player()

/* Function name: tueri
 * Description:   summons spiritual protectors, they will increase armour
 * Arguments:     str -
 * Returns:       1/0
 */
nomask mixed
tueri(string str)
{
    object who, ob;
    int mana_limit, suc, dur, strength;

    if (str)
        who = present(lower_case(str), environment(TP));
    
    if (!who || !living(who))
    {
        if (!str || (str == "me"))
            who = TP;
        else
            return "Who shall you summon the guardians to?\n";
    }

    if (NPMAGIC(who)) /* See if it is possible to cast a magic spell on obj. */
        return "Something prevents you from cast this spell.\n";

    if (present("mag_shield_prot", who))
        return "The guardians are already there.\n";

    mana_limit = 40;
    if (who == TP) /* Costs more to shield another person. */
        mana_limit = 30;

    if (TP->query_mana() < mana_limit)
        return "You do not have the strength.\n";

    suc = random(TP->query_skill(SS_FORM_CONJURATION) +
          TP->query_skill(SS_ELEMENT_LIFE));
    if (suc < random(CAST_LIMIT))
    {
        write("Your call is not heard.\n");
        TP->add_mana(-mana_limit / 3);
        return 1;
    }

    TP->add_mana(-mana_limit);
    
    dur = 100 + random(TP->query_stat(SS_WIS)) +
          TP->query_skill(SS_ELEMENT_LIFE);
    
    strength = 5 + TP->query_skill(SS_ELEMENT_LIFE)/3;
    
    write("You invoke the ancient spirits.\n");
    say(QCTNAME(TP) + " intones a mystic chant.\n");

    seteuid(getuid(this_object()));
    ob = clone_object(SPELL_DIR + "guardians_obj");
    ob->set_duration(dur);
    ob->set_strength(strength);
    ob->move(who);
    return 1;
}
