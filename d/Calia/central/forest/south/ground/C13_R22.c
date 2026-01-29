//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C13_R22", ({"C13_R21", "C14_R21",
        "C14_R22", "C14_R23", "C13_R23", "C12_R23", "C12_R22", "C12_R21"}),
        ({"oak", "birch", "hickory"}));
    }
