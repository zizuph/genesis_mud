//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C60_R26", ({"C60_R25", "C61_R25", "C61_R26",
        "C61_R27", 0, 0, 0, "C59_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
