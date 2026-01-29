//Room type {I}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C43_R14", ({"C43_R13", 0, "C44_R14",
        "C44_R15", "C43_R15", "C42_R15", "C42_R14", "C42_R13"}),
        ({"spruce"}), ({"rapids", "east"}));
    }
