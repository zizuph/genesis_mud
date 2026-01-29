//Room type {q}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C64_R24", ({"C64_R23", "C65_R23",
        "C65_R24", "C65_R25", "C64_R25", "C63_R25", "C63_R24", "C63_R23"}),
        ({"birch", "elm", "dogwood", "pine"}));
    }
