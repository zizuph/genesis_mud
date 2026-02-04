/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* 
 * lumen.c
 *
 * This is a very simple spell that adds 1 light factor to the room
 * the player casting the spell is in. How long the rooms will be
 * lit depends on the intelligence of the caster, and success on the
 * wisdom. The skill in spellcraft is counted in.
 *
 * The formula is: duration = random(int / 5) + random(skill / 3) + 35
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/spells/spells.h"

#define TP       this_player()

/* Function name: lumen
 * Description:   Will light up the room if it's a success with 1 factor
 *                It costs equal mana on success or failure.
 * Arguments:     str - the string from the light spell casted, must be 'room'
 * Returns:       1/0
 */
nomask mixed
lumen(string str)
{
    object ob;

    if (TP->query_mana() < LUMEN_MANA_COST)
        return "You do not have the strength.\n";

    if (random(TP->query_skill(SS_FORM_ENCHANTMENT) +
        TP->query_skill(SS_SPELLCRAFT)) < random(LUMEN_CAST_LIMIT))
    {
        TP->add_mana(-LUMEN_MANA_COST / 3);
        return "Your prayer is not heard.\n";
    }

    TP->add_mana(-LUMEN_MANA_COST);

    write("You sing the prayer of the sacred light.\n");
    say(QCTNAME(TP) + " sings a prayer.\n");

    seteuid(getuid());

    ob = clone_object(SPELL_DIR + "light_obj");
    ob->set_duration(DURATION(TP->query_stat(SS_INT), 
        TP->query_skill(SS_SPELLCRAFT),
        LUMEN_MIN_DURATION));
    ob->move(environment(TP));

    return 1;
}
