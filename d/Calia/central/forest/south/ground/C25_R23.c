//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C25_R23", ({0, 0, "C26_R23", "C26_R24",
        "C25_R24", "C24_R24", "C24_R23", "C24_R22"}),
        ({"oak", "sycamore", "elm", "birch"}), ({"mountains"}));
    }
