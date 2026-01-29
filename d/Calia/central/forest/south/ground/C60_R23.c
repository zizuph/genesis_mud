//Room type {q}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C60_R23", ({"C60_R22", "C61_R22",
        "C61_R23", "C61_R24", "C60_R24", "C59_R24", "C59_R23", "C59_R22"}),
        ({"birch", "elm", "dogwood", "pine"}));
    }
