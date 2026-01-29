//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C30_R03", ({"C30_R02", "C31_R02", "C31_R03",
        "C31_R04", "C30_R04", "C29_R04", "C29_R03", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
