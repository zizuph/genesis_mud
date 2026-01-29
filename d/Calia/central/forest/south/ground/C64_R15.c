//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C64_R15", ({"C64_R14", "C65_R14",
        "C65_R15", "C65_R16", "C64_R16", "C63_R16", "C63_R15", "C63_R14"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
