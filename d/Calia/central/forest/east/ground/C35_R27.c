//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C35_R27", ({"C35_R26", 0, 0, "C36_R28",
        "C35_R28", "C34_R28", 0, 0}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
