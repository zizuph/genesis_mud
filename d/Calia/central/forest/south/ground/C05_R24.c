//Room type {^}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C05_R24", ({0, 0, 0, "C06_R25", "C05_R25",
        "C04_R25", "C04_R24", "C04_R23"}),
        ({"sycamore", "oak"}), ({"thicket"}), ({"southwest"}));
    }
