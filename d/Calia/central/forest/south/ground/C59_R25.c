//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C59_R25", ({"C59_R24", "C60_R24", "C60_R25",
        "C60_R26", 0, 0, 0, "C58_R24"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
