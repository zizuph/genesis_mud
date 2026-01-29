#include "../defs.h"

inherit THIEF_BASE;

void
create_thief()
{
    add_name("leader");
    set_adj( ({ "leader" }) );

    set_long("This guy looks like he is more than capable " +
        "of holding his own in combat, and he seems to be quite well " +
        "prepared for a fight. He's obviously quite a discerning thief, " +
        "because the armour he is wearing looks like some of the best " +
        "Elven made chainmail around.\n");
    
    config_thief(100);

    set_chat_time(10);
    add_chat("Maybe I won't steal all your money.......yet!");
    add_chat("Perhaps I should go and rob someone.");

    add_equipment(({ THIEF_LAIR_DIR + "wep/stiletto",
                     THIEF_LAIR_DIR + "arm/elf_chainmail",
                     THIEF_LAIR_DIR + "arm/brig_leggings",
                     THIEF_LAIR_DIR + "arm/visored_helm",
                     THIEF_LAIR_DIR + "obj/pouch3",
                     THIEF_LAIR_DIR + "obj/lair_key", }));
}
