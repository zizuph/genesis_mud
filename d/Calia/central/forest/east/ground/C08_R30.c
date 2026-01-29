//Room type {g}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C08_R30", ({"C08_R29", "C09_R29", "C09_R30",
        "C09_R31", 0, 0, 0, "C07_R29"}),
        ({"spruce"}), ({"mountains"}));
    }
