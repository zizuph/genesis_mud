//Room type {I}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C15_R32", ({"C15_R31", "C16_R31", "C16_R32",
        0, 0, 0, "C14_R32", "C14_R31"}),
        ({"spruce"}), ({"rapids", "east"}));
    }
