//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C33_R31", ({"C33_R30", "C34_R30", "C34_R31",
        "C34_R32", 0, 0, "C32_R31", "C32_R30"}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
