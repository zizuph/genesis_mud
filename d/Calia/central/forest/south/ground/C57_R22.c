//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C57_R22", ({"C57_R21", "C58_R21", "C58_R22",
        "C58_R23", "C57_R23", 0, "C56_R22", "C56_R21"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
