//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C30_R15", ({0, 0, "C31_R15", "C31_R16",
        "C30_R16", "C29_R16", "C29_R15", 0}),
        ({"sycamore", "oak"}), ({"thicket"}));
    }
