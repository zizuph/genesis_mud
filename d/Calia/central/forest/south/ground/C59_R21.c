//Room type {n}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C59_R21", ({0, 0, "C60_R21", "C60_R22",
        "C59_R22", "C58_R22", "C58_R21", 0}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
