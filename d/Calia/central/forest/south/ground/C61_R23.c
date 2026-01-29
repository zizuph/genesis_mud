//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C61_R23", ({"C61_R22", 0, "C62_R23",
        "C62_R24", "C61_R24", "C60_R24", "C60_R23", "C60_R22"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
