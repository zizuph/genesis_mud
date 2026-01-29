//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C73_R25", ({"C73_R24", 0, 0, 0, "C73_R26",
        "C72_R26", "C72_R25", "C72_R24"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
