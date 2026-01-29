//Room type {h}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R05", ({"C32_R04", "C33_R04", "C33_R05",
        0, "C32_R06", "C31_R06", "C31_R05", "C31_R04"}),
        ({"cedar", "birch", "fir"}), ({"mountain"}));
    }
