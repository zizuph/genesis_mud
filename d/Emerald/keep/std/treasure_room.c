#pragma strict_types

inherit "/d/Emerald/keep/std/keep_room";

void
create_treasure_room()
{
}

static nomask void
create_keep_room()
{
    set_short("Treasure room");
    set_long("A treasure room.\n");

    set_dimensions(1, 1);
    set_structure_name("Treasure room");
    set_structure_cost(12 * 12 * 12 * 10);
    set_structure_completion_time(60 * 60 * 8);

    create_treasure_room();
}
