//Room type {h}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R02", ({"C32_R01", 0, "C33_R02",
        "C33_R03", "C32_R03", "C31_R03", "C31_R02", "C31_R01"}),
        ({"cedar", "birch", "fir"}), ({"mountain"}));
    }
