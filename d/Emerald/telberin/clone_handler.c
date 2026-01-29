inherit "/d/Emerald/std/clone_handler";

#include "defs.h"

void
create_clone_handler()
{
    string *merc_open, *science_open, *arts_open, *magic_open, *other_open;

    set_default_area("/d/Emerald/telberin/");

    merc_open = ({ TELBERIN_DIR + "artisans_plaza",
                   TELBERIN_DIR + "artisans_way05",
                   TELBERIN_DIR + "artisans_way06",
                   TELBERIN_DIR + "artisans_way07",
                   TELBERIN_MERCANTILE_DIR + "general_store",
                   TELBERIN_MERCANTILE_DIR + "jeweler_shop",
                   TELBERIN_MERCANTILE_DIR + "bank",
                   TELBERIN_MERCANTILE_DIR + "arms_shop", });

    science_open = ({ TELBERIN_DIR + "scholars_plaza",
                      TELBERIN_DIR + "scholars_way01",
                      TELBERIN_DIR + "scholars_way02",
                      TELBERIN_DIR + "scholars_way03",
                      TELBERIN_SCIENCE_DIR + "apothecarium", });
    arts_open = ({ TELBERIN_DIR + "cantors_plaza",
                   TELBERIN_DIR + "cantors_way05",
                   TELBERIN_DIR + "cantors_way06",
                   TELBERIN_DIR + "cantors_way07",
                   TELBERIN_ARTS_DIR + "post",
                   TELBERIN_ARTS_DIR + "inn", });

    magic_open = ({ TELBERIN_DIR + "channelers_plaza",
                    TELBERIN_DIR + "channelers_way01",
                    TELBERIN_DIR + "channelers_way02",
                    TELBERIN_DIR + "channelers_way03",
                    TELBERIN_DIR + "channelers_way03",
                      TELBERIN_MAGIC_DIR + "mage_guild1", });

    other_open = ({ TELBERIN_DIR + "fruit_garden/",
                    TELBERIN_DIR + "magic_garden/",
                    TELBERIN_DIR + "royal_circle*", });


    add_clone(TELBERIN_DIR + "npc/telberin_elf", 1, 2, science_open);
    add_clone(TELBERIN_DIR + "npc/telberin_elf", 2, 2, arts_open);
    add_clone(TELBERIN_DIR + "npc/telberin_elf", 3, 2, magic_open);
    add_clone(TELBERIN_DIR + "npc/telberin_elf", 4, 2, merc_open);

    add_clone(TELBERIN_MERCANTILE_DIR + "armoury/armourer", 5, 1,
              TELBERIN_MERCANTILE_DIR + "armoury/armoury");

    set_excluded_destinations(({ TELBERIN_DIR + "royal_circle",
                                   TELBERIN_DIR + "scholars_way",
                                   TELBERIN_DIR + "cantors_way",
                                   TELBERIN_DIR + "artisans_way",
                                   TELBERIN_DIR + "channelers_way",
                                   TELBERIN_DIR + "telberin_room",
                                   TELBERIN_DIR + "telberin_building",
                                   TELBERIN_DIR + "telberin_street", }));
}
