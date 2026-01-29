//Room type {O}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C29_R22", ({"C29_R21", "C30_R21", "C30_R22",
        0, "C29_R23", "C28_R23", "C28_R22", "C28_R21"}),
        ({"sycamore", "elm"}), ({"barricade"}), ({"northwest"}));
    }
