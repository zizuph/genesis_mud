//Room type {B}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R20", ({"C32_R19", 0, 0, 0, 0, "C31_R21",
        "C31_R20", "C31_R19"}),
        ({"sycamore", "elm"}), ({"barricade"}));
    }
