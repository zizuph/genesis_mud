//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C31_R30", ({"C31_R29", "C32_R29", "C32_R30",
        "C32_R31", "C31_R31", 0, "C30_R30", 0}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
