//Room type {=}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C63_R14", ({"C63_R13", "C64_R13",
        "C64_R14", "C64_R15", "C63_R15", "C62_R15", "C62_R14", "C62_R13"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"west", "east"}));
    }
