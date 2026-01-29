//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C24_R10", ({0, "C25_R09", "C25_R10",
        "C25_R11", "C24_R11", "C23_R11", 0, 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
