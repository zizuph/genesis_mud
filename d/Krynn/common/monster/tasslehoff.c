/* Hero of the Lance - Tasslehoff
 * beta version by Teth, March 28, 1996
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit M_FILE

void
create_krynn_monster()
{
    set_name("tasslehoff");
    set_living_name("tasslehoff");
    set_title("Burrfoot");
    set_long("This kender, like all others, has a glint in his eye and " +
             "a curiousity in his voice.\n");
    set_race_name("kender");
    set_adj("mischievous");
    add_adj("happy");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_introduce(1);

    set_alignment(900);
}


