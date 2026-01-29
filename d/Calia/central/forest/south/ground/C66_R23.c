//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C66_R23", ({0, 0, "C67_R23", "C67_R24",
        "C66_R24", "C65_R24", "C65_R23", 0}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
