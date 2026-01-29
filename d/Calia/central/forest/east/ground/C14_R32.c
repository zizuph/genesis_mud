//Room type {I}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C14_R32", ({"C14_R31", "C15_R31", "C15_R32",
        0, 0, 0, "C13_R32", "C13_R31"}),
        ({"spruce"}), ({"rapids", "east"}));
    }
