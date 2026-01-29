//Room type {h}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C33_R05", ({"C33_R04", 0, 0, 0, 0, "C32_R06",
        "C32_R05", "C32_R04"}),
        ({"cedar", "birch", "fir"}), ({"mountain"}));
    }
