/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define MANA_LIMIT      35  /* How much mana does it cost to cast this spell? */
#define CAST_LIMIT      50 /* How wise and skilled must the caster be? */
#define SPELL_DIR	"/d/Terel/mecien/valley/guild/spells/" 

/* Function name: panis
 * Description:   call a loaf of mystic bread from the Ancients
 *                
 * Arguments:     str - the string from the light spell casted, must be 'room'
 * Returns:       1/0
 */
nomask mixed
panis(string str)
{
    object bread;

    if (this_player()->query_mana() < MANA_LIMIT)
        return "You do not have the strength to call out.\n";

    this_player()->add_mana(-MANA_LIMIT);

    if (random(this_player()->query_skill(SS_FORM_CONJURATION) +
        this_player()->query_skill(SS_ELEMENT_LIFE)) < random(CAST_LIMIT))
    {
        write("Your call was unheard.\n");
        return 1;
    }

    write("You call out to the Ancient powers.\n");
    write("A spirit descends from above and delivers a loaf of bread.\n");
    write("The spirit returns amidst a flash of white light.\n");
    say(QCTNAME(this_player()) + " raises a hand and calls out.\n");

    seteuid(getuid(this_object()));
    bread = clone_object(SPELL_DIR + "bread");
    bread->set_duration(random(this_player()->query_stat(SS_INT) / 5) +
        random(this_player()->query_skill(SS_SPELLCRAFT) / 3) + 45);
    bread->move(this_player());
    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */

