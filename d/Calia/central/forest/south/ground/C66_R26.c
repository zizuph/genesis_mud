//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C66_R26", ({"C66_R25", "C67_R25", "C67_R26",
        0, 0, 0, "C65_R26", "C65_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
