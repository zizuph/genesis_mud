/* 
* Nubes (mystic fog)
* Mystic can summon a bank of fog in which he will be able
* to hide and escape enemies.
*
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "spells.h"

/* Function name: nubes
 */
nomask int
nubes(string str)
{
    object ob;

    notify_fail("You do not have the strength.\n");
    if (this_player()->query_mana() < NUBES_MANA_COST)
        return 0;

    if (random(this_player()->query_skill(SS_ELEMENT_AIR) +
        this_player()->query_skill(SS_FORM_CONJURATION)) < random(NUBES_CAST_LIMIT))
    {
        this_player()->add_mana(-NUBES_MANA_COST / 3);
        write("Your prayer is not heard.\n");
        return 1;
    }

    this_player()->add_mana(-NUBES_MANA_COST);

   write("You call out and beckon in the mysterious shadows.\n");
   say(QCTNAME(this_player()) + " raises a hand and calls out.\n");
   tell_room(environment(this_player()), "A gloom descends upon this place.\n");
   tell_room(environment(this_player()), "A eerie fog rolls in.\n");
    
    seteuid(getuid(this_object()));

    ob = clone_object(SPELL_DIR + "fog");
    ob->set_duration(DURATION(this_player()->query_stat(SS_WIS), 
        this_player()->query_skill(SS_SPELLCRAFT),
        NUBES_MIN_DURATION));
    ob->move(environment(this_player()));

    return 1;
}
