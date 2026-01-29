//Room type {>}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C08_R22", ({"C08_R21", "C09_R21",
        "C09_R22", "C09_R23", "C08_R23", "C07_R23", "C07_R22", "C07_R21"}),
        ({"oak", "birch", "hickory"}), ({"northwest", "southwest", "east"}));
    }
