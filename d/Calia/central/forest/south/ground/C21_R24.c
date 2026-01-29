//Room type {Q}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C21_R24", ({"C21_R23", "C22_R23",
        "C22_R24", "C22_R25", "C21_R25", "C20_R25", "C20_R24", "C20_R23"}),
        ({"oak", "birch", "hickory"}), ({"southwest", "east"}));
    }
