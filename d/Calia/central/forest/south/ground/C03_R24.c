//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C03_R24", ({"C03_R23", "C04_R23",
        "C04_R24", "C04_R25", "C03_R25", "C02_R25", "C02_R24", "C02_R23"}),
        ({"sycamore", "birch", "elm"}));
    }
