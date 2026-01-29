//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C65_R26", ({"C65_R25", "C66_R25", "C66_R26",
        0, 0, 0, 0, "C64_R25"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
