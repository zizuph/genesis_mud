//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C44_R24", ({"C44_R23", "C45_R23", "C45_R24",
        0, "C44_R25", "C43_R25", "C43_R24", "C43_R23"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
