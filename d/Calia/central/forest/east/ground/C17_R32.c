//Room type {I}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C17_R32", ({"C17_R31", "C18_R31", "C18_R32",
        0, 0, 0, "C16_R32", "C16_R31"}),
        ({"spruce"}), ({"rapids", "east"}));
    }
