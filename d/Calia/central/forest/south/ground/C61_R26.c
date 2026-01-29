//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C61_R26", ({"C61_R25", "C62_R25", "C62_R26",
        "C62_R27", "C61_R27", 0, "C60_R26", "C60_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
