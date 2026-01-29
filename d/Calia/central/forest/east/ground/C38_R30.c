//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C38_R30", ({"C38_R29", 0, 0, "C39_R31",
        "C38_R31", "C37_R31", "C37_R30", "C37_R29"}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
