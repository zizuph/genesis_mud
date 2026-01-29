inherit "/d/Wiz/shiva/clone_handler";

#include "../garden.h"

static string random_plant();

create_clone_handler()
{
    set_clone_handler_id("Poison Garden Clone Handler");
    set_default_area(POISON_GARDEN_ROOM);
    set_excluded_destinations(({ POISON_GARDEN_ROOM + "cottage",
                                 POISON_GARDEN_ROOM + "garden" }));

    add_clone(POISON_GARDEN_NPC + "wither", 1, 1, POISON_GARDEN_ROOM + "cottage");
    add_clone(random_plant, 2, 10);
}

static string random_plant()
{
    string *npcs;

    setuid();
    seteuid(getuid());

    npcs = filter(get_dir(POISON_GARDEN_RAND_NPC), &wildmatch("*.c"));

    if (!sizeof(npcs))
    {
        return "";
    }

    return POISON_GARDEN_RAND_NPC + npcs[random(sizeof(npcs))];
}
