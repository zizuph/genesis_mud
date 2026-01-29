//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C25_R08", ({0, "C26_R07", "C26_R08",
        "C26_R09", "C25_R09", 0, 0, 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
