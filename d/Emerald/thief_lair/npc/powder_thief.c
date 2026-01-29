/* An Elven Powder Thief (humanoid) - Coded 05/04/96 by Tulix III */
/* This npc is needed for completion of a certain quest.          */
/* Cloned by various rooms in /d/Emerald/cave/lair/               */

#include "../defs.h"

inherit THIEF_BASE;

#include <ss_types.h>

/* Prototype function */
public string powder_trace();

public void
create_thief()
{
    set_adj("tall");

    set_long("This particular elf is taller than most, and looks a little " +
        "bit tougher, too. It is quite likely that stealing has been " +
        "more of a way of life than a hobby for this specimen.\n" +
        "After all, why earn money for something you can just steal...?\n" +
        "@@powder_trace@@");
    
    set_chat_time(10);                 /* Set speaking interval         */
    add_chat("I wonder if the old mage has noticed his loss yet....");
    add_chat("Hmmm, this could be trouble.");
    add_chat("Soon be time to raid Telberin again, I guess.");

    set_cchat_time(4);
    add_cchat("If you want the powder, you'll have to earn it!");
    add_cchat("Have it your way!");

    config_thief(80 + random(20));
    make_default_eq();

    add_equipment(THIEF_LAIR_DIR + "obj/powder");

    start_wander();
}

public string
powder_trace()
{
    if (this_player()->query_skill(SS_AWARENESS) >= 40)
    {
        return "You notice traces of a green powder on the elf's hand.\n"; 
    }
    
    return "";
}
