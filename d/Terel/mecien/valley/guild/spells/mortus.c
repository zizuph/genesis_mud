/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define CAST_LIMIT    30   /* The limit for this to become a success */
#define SPELL_DIR	"/d/Terel/mecien/valley/guild/spells/"

/* Function name: mederi
 * Description:   heals target of small wound
 * Arguments:     str - 
 * Returns:       1/0
 */
nomask mixed
mortus(string str)
{
    object who;
    int mana_limit, sum, life;

    if (str)
        who = present(lower_case(str), environment(this_player()));
    if (!who)
    {
        if (!str || (str == "myself") || (str == "me"))
            who = this_player();
        else
            return "Who shall you sentence to death?.\n";
    }

    if (NPMAGIC(who)) /* See if it is possible to cast a magic spell on obj. */
        return "Something prevents you from cast this spell.\n";

    mana_limit = 30;
    if (who == this_player()) /* Costs more to heal yourself */
        mana_limit = 40;

    if (this_player()->query_mana() < mana_limit)
        return "You do not have the strength to call out.\n";

    if (random(this_player()->query_skill(SS_FORM_ABJURATION) +
        this_player()->query_skill(SS_ELEMENT_LIFE)) < random(CAST_LIMIT))
    {
        write("Your call is not heard.\n");
        this_player()->add_mana(-mana_limit / 3);
        return 1;
    }

    this_player()->add_mana(-mana_limit);
    say(QCTNAME(this_player()) + " calls upon the powers of the abyss.\n");
  tell_room(environment(this_player()), "A dark shape takes form " +
   "around " + who->query_name() + ".\n", who);
   who->catch_msg("An ancient power siezes your soul.\n");
  who->set_hp(0);
   who->do_die(this_player());
    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */

