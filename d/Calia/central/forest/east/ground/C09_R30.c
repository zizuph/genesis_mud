//Room type {g}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C09_R30", ({"C09_R29", "C10_R29", "C10_R30",
        "C10_R31", "C09_R31", 0, "C08_R30", "C08_R29"}),
        ({"spruce"}), ({"mountains"}));
    }
