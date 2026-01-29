/* A Sneaky Elf Thief (humanoid) - Recoded 18/07/95, Tulix III */
/* Cloned by various rooms in /d/Emerald/cave/lair/ */

#include "../defs.h"

inherit THIEF_BASE;

void
create_thief()
{
    set_adj("roaming");

    set_long("This particular elf seems intent on 'collecting' " +
        "anything that he can lay his hands on. You'd better " +
        "keep an eye on him, just in case he tries to 'collect' " +
        "anything belonging to you...\n");
    
    config_thief(65 + random(15));

    add_act("get all");
    add_act("fill rucksack");

    set_chat_time(10); /* Set speaking interval */
    add_chat("Now what have we got here...");
    add_chat("Hmmm, not much doing here.");
    add_chat("I'm no thief!");

    set_act_time(10);  /* Set action interval */
    add_act("cackle");
    add_act("emote eyes you professionally.\n");

    make_default_eq();

    start_wander();
}
