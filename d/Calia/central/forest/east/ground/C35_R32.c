//Room type {O}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C35_R32", ({"C35_R31", "C36_R31", "C36_R32",
        0, 0, 0, "C34_R32", "C34_R31"}),
        ({"fir", "beech", "elm"}), ({"river", "east"}));
    }
