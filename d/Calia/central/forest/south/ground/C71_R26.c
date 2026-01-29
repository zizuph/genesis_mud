//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C71_R26", ({"C71_R25", "C72_R25", "C72_R26",
        "C72_R27", 0, 0, "C70_R26", "C70_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
