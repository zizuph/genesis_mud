/* A Sneaky Elf Thief (humanoid) - Recoded 18/07/95, Tulix III */
/* Cloned by various rooms in /d/Emerald/cave/lair/ */

#include "../defs.h"

inherit THIEF_BASE;

void
create_thief()
{
    set_adj("sneaky");

    set_long("It's one of the sneakiest looking Elves that you " +
        "have ever set eyes upon. Better watch your pockets, or he may " +
        "well relieve you of some of that hard earned cash.\n");

    config_thief(65 + random(15));

    set_chat_time(10); /* Set speaking interval */
    add_chat("Wasn't me!");
    add_chat("I'm no thief!");

    set_act_time(10);  /* Set action interval */
    add_act("cackle");
    add_act(say("The sneaky elf eyes you professionally.\n"));

    make_default_eq();

    start_wander();
}
