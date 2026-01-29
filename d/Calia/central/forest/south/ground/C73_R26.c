//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C73_R26", ({"C73_R25", 0, 0, 0, "C73_R27",
        "C72_R27", "C72_R26", "C72_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
