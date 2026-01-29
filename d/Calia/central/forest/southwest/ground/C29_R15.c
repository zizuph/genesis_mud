//Room type {9}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

void create_room()
    {
    add_exit(FOREST_SOUTH + "C04_R25", "north", 0, 2);
    create_forest_entrance("C29_R15", ({0, 0, "C30_R15", "C30_R16",
        "C29_R16", "C28_R16", "C28_R15", 0}),
        ({"sycamore", "birch", "elm"}), ({"southwest", "north"}),
        "thicket", "north");
    }
