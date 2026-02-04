/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* This spells summons a magic shield to protect a player. It works as
 * a forcefield protecting from blows. The duration of the shield depends
 * on the intelligence of the caster. Defence spell skill and wisdom
 * controls if this is a success. The magic shiled has an ac of 10.
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TP this_player()
#define CAST_LIMIT    50   /* The limit for this to become a success */

/* Function name: circa
 * Description:   summons spiritual protectors, they will increase armour
 * Arguments:     str - 
 * Returns:       1/0
 */
nomask mixed
circa(string str)
{
    object who, ob;
    int mana_limit, sum;

    if (str)
        who = present(lower_case(str), environment(this_player()));
    if (!who)
    {
        if (!str || (str == "me"))
            who = this_player();
        else
    return "Where shall you call forth the circle?\n";
    }

    if (NPMAGIC(who)) /* See if it is possible to cast a magic spell on obj. */
        return "Something prevents you from cast this spell.\n";

    if (present("white_circle", who))
   return "The circle is already protecting.\n";

    mana_limit = 25;
    if (who == this_player()) /* Costs more to shield another person. */
        mana_limit = 20;

    if (this_player()->query_mana() < mana_limit)
        return "You do not have the strength.\n";

    if (random(this_player()->query_skill(SS_FORM_CONJURATION) +
        this_player()->query_skill(SS_ELEMENT_LIFE)) < random(CAST_LIMIT))
    {
        write("Your call is not heard.\n");
        this_player()->add_mana(-mana_limit / 3);
        return 1;
    }
   if(!present(MYSTIC_ROBE, TP)) return "You will need the white robe.\n";

    this_player()->add_mana(-mana_limit);
   write("You call upon the white circle, tracing the edge of your robe in a circle about yourself.\n");
   say(QCTNAME(TP) + " traces the air in a circle with the edge of " +
   TP->query_possessive() + " robe.\n");

    seteuid(getuid(this_object()));
    ob = clone_object(SPELL_DIR + "circa_obj");
    ob->set_duration(random(this_player()->query_stat(SS_WIS) / 2) +
        random(this_player()->query_skill(SS_SPELLCRAFT) / 2) + 300);
    ob->move(who);
    return 1;
}
