//Room type {q}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C60_R22", ({"C60_R21", "C61_R21",
        "C61_R22", "C61_R23", "C60_R23", "C59_R23", "C59_R22", "C59_R21"}),
        ({"birch", "elm", "dogwood", "pine"}));
    }
