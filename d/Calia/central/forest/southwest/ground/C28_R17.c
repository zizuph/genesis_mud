//Room type {|}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R17", ({"C28_R16", "C29_R16",
        "C29_R17", "C29_R18", "C28_R18", "C27_R18", "C27_R17", "C27_R16"}),
        ({"sycamore", "birch", "elm"}), ({"north", "south"}));
    }
