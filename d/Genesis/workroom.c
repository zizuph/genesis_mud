inherit "/std/workroom";

create_workroom()
{
    ::create_workroom();

    add_exit("/d/Genesis/start/human/town/tower", "human", 0, 0);
    add_exit("/d/Genesis/start/hobbit/v/guild", "hobbit", 0, 0);
    add_exit("/d/Genesis/start/dwarf/lvl1/board", "dwarf", 0, 0);
    add_exit("/d/Genesis/start/goblin/caverns/quarters", "goblin", 0, 0);
    add_exit("/d/Genesis/start/elf/room/vill_board", "elf", 0, 0);
}
