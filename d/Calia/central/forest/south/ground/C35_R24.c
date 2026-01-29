//Room type {[}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C35_R24", ({"C35_R23", "C36_R23",
        "C36_R24", "C36_R25", "C35_R25", "C34_R25", "C34_R24", "C34_R23"}),
        ({"oak", "birch", "hickory"}), ({"west", "southeast", "east"}));
    }
