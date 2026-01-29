//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R16", ({"C31_R15", "C32_R15",
        "C32_R16", "C32_R17", "C31_R17", "C30_R17", "C30_R16", "C30_R15"}),
        ({"sycamore", "birch", "elm"}));
    }
