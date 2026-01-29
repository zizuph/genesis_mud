//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C63_R26", ({"C63_R25", "C64_R25", 0, 0, 0,
        "C62_R27", "C62_R26", "C62_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
