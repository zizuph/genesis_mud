//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C29_R03", ({0, "C30_R02", "C30_R03",
        "C30_R04", "C29_R04", 0, 0, 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
