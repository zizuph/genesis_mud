//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C70_R26", ({"C70_R25", "C71_R25", "C71_R26",
        0, 0, 0, "C69_R26", "C69_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
