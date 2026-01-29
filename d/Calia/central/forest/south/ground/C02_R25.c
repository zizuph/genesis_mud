//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C02_R25", ({"C02_R24", "C03_R24", "C03_R25",
        0, 0, 0, 0, 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
