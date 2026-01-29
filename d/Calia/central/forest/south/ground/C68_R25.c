//Room type {u}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C68_R25", ({"C68_R24", "C69_R24", "C69_R25",
        "C69_R26", 0, "C67_R26", "C67_R25", "C67_R24"}),
        ({"birch", "sycamore", "elm", "dogwood"}), ({"thicket"}));
    }
