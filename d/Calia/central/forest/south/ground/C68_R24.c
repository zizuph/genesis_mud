//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C68_R24", ({"C68_R23", 0, "C69_R24",
        "C69_R25", "C68_R25", "C67_R25", "C67_R24", "C67_R23"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
