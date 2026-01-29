/* A Shifty Elf Thief (humanoid) - Recoded 18/07/95, Tulix III */
/* Cloned by various rooms in /d/Emerald/cave/lair/ */

#include "../defs.h"

inherit THIEF_BASE;

void
create_thief()
{
    set_adj("shifty");

    set_long("It's a very shifty looking Elf. He'll probably " +
        "steal all your money if given the opportunity. But then again, " +
        "a lot of Elves are like that.\n");
    
    config_thief(65 + random(20));

    set_chat_time(10); /* Set speaking interval         */
    add_chat("Away with ye!");
    add_chat("Heh, you look like you have too much money.");
    add_chat("Hmm, a rich one, perhaps...");

    make_default_eq();

    start_wander();
}
