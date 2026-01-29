//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C72_R24", ({0, 0, "C73_R24", "C73_R25",
        "C72_R25", "C71_R25", "C71_R24", 0}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
