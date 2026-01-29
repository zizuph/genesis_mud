#include "../defs.h"

inherit THIEF_BASE;

#include <stdproperties.h>

void
reset_monster()
{
    object *eq = all_inventory(this_object());
    int i;

    setuid();
    seteuid(getuid());

    for (i = sizeof(filter(eq, &->id("smoke_bomb"))); i <= 3; i++)
    {
        clone_object(THIEF_LAIR_DIR + "obj/smoke_bomb")->move(this_object(), 1);
    }
}

void
create_thief()
{
    int level;

    set_adj(({ "sinister", "lithe", "master" }));

    set_long("This elf has a truly sinister glint in his eye.\n");

    level = 130 + random(20);
    config_thief(level);

    add_prop(LIVE_I_QUICKNESS, 100);

    add_prop(CONT_I_HEIGHT, 225); /* he's tall */
    add_prop(CONT_I_WEIGHT, 47000);
    add_prop(CONT_I_VOLUME, 47000);

    add_equipment(({ THIEF_LAIR_DIR + "wep/magic_knife",
                     THIEF_LAIR_DIR + "arm/black_cloak", }));

    reset_monster();
    enable_reset();

    start_wander();
}
