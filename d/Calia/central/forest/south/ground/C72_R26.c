//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C72_R26", ({"C72_R25", "C73_R25", "C73_R26",
        "C73_R27", "C72_R27", 0, "C71_R26", "C71_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
