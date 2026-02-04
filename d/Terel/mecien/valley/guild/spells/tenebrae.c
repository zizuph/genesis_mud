/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define MANA_LIMIT      10  /* How much mana does it cost to cast this spell? */
#define CAST_LIMIT      10 /* How wise and skilled must the caster be? */
#define SPELL_DIR	"/d/Terel/mecien/valley/guild/spells/" /* Where is our spell dir? */

/* Function name: tenebrae
 * Description:   Will light up the room if it's a success with 1 factor
 *                It costs equal mana on success or failure.
 * Arguments:     str - the string from the light spell casted, must be 'room'
 * Returns:       1/0
 */
nomask mixed
tenebrae(string str)
{
    object ob;

    if (this_player()->query_mana() < MANA_LIMIT)
        return "You do not have the strength.\n";

    this_player()->add_mana(-MANA_LIMIT);

    if (random(this_player()->query_skill(SS_FORM_ENCHANTMENT) +
        this_player()->query_skill(SS_SPELLCRAFT)) < random(CAST_LIMIT))
    {
        write("Your invocation is not heard.\n");
        return 1;
    }

    write("You invoke the mystery of the ancient darkness.\n");
    say(QCTNAME(this_player()) + " is draped with a fog of darkness.\n");

    seteuid(getuid(this_object()));
    ob = clone_object(SPELL_DIR + "dark_obj");
    ob->set_duration(random(this_player()->query_stat(SS_INT) / 2) +
        random(this_player()->query_skill(SS_SPELLCRAFT) / 3) + 45);
    ob->move(environment(this_player()));
    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */

