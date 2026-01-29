//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C70_R24", ({0, 0, "C71_R24", "C71_R25",
        "C70_R25", "C69_R25", "C69_R24", 0}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
