//Room type {B}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C31_R21", ({"C31_R20", "C32_R20", 0, 0, 0,
        "C30_R22", "C30_R21", "C30_R20"}),
        ({"sycamore", "elm"}), ({"barricade"}));
    }
