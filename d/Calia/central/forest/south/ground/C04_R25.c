//Room type {8}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

void create_room()
    {
    add_exit(FOREST_SOUTHWEST + "C29_R15", "south", 0, 2);
    create_forest_entrance("C04_R25", ({"C04_R24", "C05_R24",
        "C05_R25", 0, 0, 0, "C03_R25", "C03_R24"}),
        ({"sycamore", "birch", "elm"}), ({"northwest", "south"}),
        "thicket", "south");
    }
