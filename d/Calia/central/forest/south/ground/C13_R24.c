//Room type {\}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C13_R24", ({"C13_R23", "C14_R23",
        "C14_R24", "C14_R25", "C13_R25", "C12_R25", "C12_R24", "C12_R23"}),
        ({"oak", "birch", "hickory"}), ({"northwest", "southeast"}));
    }
