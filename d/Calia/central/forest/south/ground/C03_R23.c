//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C03_R23", ({0, 0, "C04_R23", "C04_R24",
        "C03_R24", "C02_R24", "C02_R23", 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
