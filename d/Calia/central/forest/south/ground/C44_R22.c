//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C44_R22", ({"C44_R21", "C45_R21",
        "C45_R22", "C45_R23", "C44_R23", "C43_R23", "C43_R22", "C43_R21"}),
        ({"oak", "birch", "hickory"}));
    }
