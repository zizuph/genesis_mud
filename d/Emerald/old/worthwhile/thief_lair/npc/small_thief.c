#include "../defs.h"

inherit THIEF_BASE;

void
create_thief()
{
    set_adj("small");

    set_long("This little Elven thief looks like he is not " +
        "old enough to be a particularly experienced thief. He is probably " +
        "just starting to learn the profession.\n");

    config_thief(45 + random(15));

    set_chat_time(10); /* Set speaking interval */
    add_chat("hmmmmm.");
    add_chat("I'm just learning to be a thief.");
    add_chat("I still don't know how to pick pockets.");
    
    add_equipment(({ THIEF_LAIR_DIR + "wep/stiletto",
                     THIEF_LAIR_DIR + "wep/stiletto",
                     THIEF_LAIR_DIR + "arm/studded_mail",
                     THIEF_LAIR_DIR + "arm/studded_helm", }));

    start_wander();
}
