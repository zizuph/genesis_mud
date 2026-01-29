//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C15_R22", ({"C15_R21", "C16_R21",
        "C16_R22", "C16_R23", "C15_R23", "C14_R23", "C14_R22", "C14_R21"}),
        ({"oak", "birch", "hickory"}));
    }
