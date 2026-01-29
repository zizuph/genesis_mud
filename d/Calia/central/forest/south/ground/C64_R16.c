//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C64_R16", ({"C64_R15", "C65_R15",
        "C65_R16", "C65_R17", "C64_R17", "C63_R17", "C63_R16", "C63_R15"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
