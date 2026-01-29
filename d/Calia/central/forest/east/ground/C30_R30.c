//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C30_R30", ({0, "C31_R29", "C31_R30",
        "C31_R31", 0, 0, 0, 0}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
