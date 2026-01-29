//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C46_R22", ({"C46_R21", "C47_R21",
        "C47_R22", "C47_R23", "C46_R23", "C45_R23", "C45_R22", "C45_R21"}),
        ({"oak", "birch", "hickory"}));
    }
