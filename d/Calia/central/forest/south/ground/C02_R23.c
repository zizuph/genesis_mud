//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C02_R23", ({0, 0, "C03_R23", "C03_R24",
        "C02_R24", 0, 0, 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
