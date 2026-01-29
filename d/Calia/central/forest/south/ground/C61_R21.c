//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C61_R21", ({0, 0, 0, 0, "C61_R22", "C60_R22",
        "C60_R21", 0}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
