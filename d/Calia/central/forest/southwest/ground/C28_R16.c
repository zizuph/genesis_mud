//Room type {P}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R16", ({"C28_R15", "C29_R15",
        "C29_R16", "C29_R17", "C28_R17", "C27_R17", "C27_R16", "C27_R15"}),
        ({"sycamore", "birch", "elm"}), ({"northwest", "south"}));
    }
