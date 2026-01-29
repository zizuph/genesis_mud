//Room type {W}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C18_R19", ({"C18_R18", "C19_R18",
        "C19_R19", "C19_R20", "C18_R20", "C17_R20", "C17_R19", "C17_R18"}),
        ({"sycamore", "birch", "elm"}), ({"northwest", "east"}));
    }
