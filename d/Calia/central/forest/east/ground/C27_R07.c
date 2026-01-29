//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C27_R07", ({"C27_R06", "C28_R06", "C28_R07",
        "C28_R08", "C27_R08", "C26_R08", "C26_R07", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
