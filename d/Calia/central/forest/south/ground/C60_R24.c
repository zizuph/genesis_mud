//Room type {q}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C60_R24", ({"C60_R23", "C61_R23",
        "C61_R24", "C61_R25", "C60_R25", "C59_R25", "C59_R24", "C59_R23"}),
        ({"birch", "elm", "dogwood", "pine"}));
    }
