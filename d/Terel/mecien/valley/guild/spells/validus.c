/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define CAST_LIMIT    30   /* The limit for this to become a success */
#define SPELL_DIR	"/d/Terel/mecien/valley/guild/spells/"

/* Function name: validus
 * Description:   grants temporary strength
 * Arguments:     str - 
 * Returns:       1/0
 */
nomask mixed
validus(string str)
{
    object who;
    int mana_limit, sum;

    if (str)
        who = present(lower_case(str), environment(this_player()));
    if (!who)
    {
        if (!str || (str == "me"))
            who = this_player();
        else
            return "To whom shall this power be called?.\n";
    }

    if (NPMAGIC(who)) /* See if it is possible to cast a magic spell on obj. */
        return "Something prevents you from cast this spell.\n";

    mana_limit = 30;
    if (who == this_player()) /* Costs more to heal yourself */
        mana_limit = 40;

    if (this_player()->query_mana() < mana_limit)
        return "You do not have the strength to call out.\n";

    if (random(this_player()->query_skill(SS_ELEMENT_LIFE) +
        this_player()->query_skill(SS_FORM_ENCHANTMENT)) < random(CAST_LIMIT))
    {
        write("Your call is not heard.\n");
        this_player()->add_mana(-mana_limit / 3);
        return 1;
    }

    this_player()->add_mana(-mana_limit);
  write("You pray to the forces of might, from deep within\n"
    + "you feel the strength of the Ancients.\n");
  say("Falling to the ground, " + QCTNAME(this_player()) + " prays aloud.\n");
  tell_room(environment(this_player()),
   "The air seems to grow warm about you, a trembling all about\n"
   + "the area. A wild sense of power, might and fortitude.\n");
   who->add_tmp_stat(SS_STR, random(10) + 1, 10);
  who->catch_msg("The spirits of mystic strength dwell within you.\n");
    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */

