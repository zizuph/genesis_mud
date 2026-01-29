//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C56_R21", ({0, 0, "C57_R21", "C57_R22",
        "C56_R22", 0, 0, 0}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
