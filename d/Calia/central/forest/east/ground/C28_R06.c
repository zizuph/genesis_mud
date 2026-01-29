//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C28_R06", ({"C28_R05", "C29_R05", "C29_R06",
        "C29_R07", "C28_R07", "C27_R07", "C27_R06", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
