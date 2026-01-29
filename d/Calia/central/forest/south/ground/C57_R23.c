//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C57_R23", ({"C57_R22", "C58_R22", "C58_R23",
        "C58_R24", 0, 0, 0, "C56_R22"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
