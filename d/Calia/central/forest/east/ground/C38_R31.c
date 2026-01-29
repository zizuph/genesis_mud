//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C38_R31", ({"C38_R30", 0, "C39_R31", 0,
        "C38_R32", "C37_R32", "C37_R31", "C37_R30"}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
