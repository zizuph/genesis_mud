/* Hero of the Lance - Flint
 * beta version by Teth, March 28, 1996
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit M_FILE

void
create_krynn_monster()
{
    set_name("flint");
    set_living_name("flint");
    set_title("Fireforge");
    set_long("This dwarf, though outwardly appearing harsh, often slips " +
             "and shows his sentimental side, if you catch his eyes at " +
             "the right time. However, he often just grumbles.\n");
    set_race_name("dwarf");
    set_adj("gruff");
    add_adj("old");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_introduce(1);

    set_alignment(900);
}


