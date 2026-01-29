//Room type {B}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C30_R22", ({"C30_R21", "C31_R21", 0, 0, 0,
        "C29_R23", "C29_R22", "C29_R21"}),
        ({"sycamore", "elm"}), ({"barricade"}));
    }
