//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C63_R23", ({0, 0, "C64_R23", "C64_R24",
        "C63_R24", "C62_R24", "C62_R23", 0}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
