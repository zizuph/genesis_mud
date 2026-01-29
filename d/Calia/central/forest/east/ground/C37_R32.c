//Room type {O}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C37_R32", ({"C37_R31", "C38_R31", "C38_R32",
        0, 0, 0, "C36_R32", "C36_R31"}),
        ({"fir", "beech", "elm"}), ({"river", "east"}));
    }
