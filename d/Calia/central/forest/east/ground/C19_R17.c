//Room type {p}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C19_R17", ({"C19_R16", "C20_R16", "C20_R17",
        0, 0, 0, 0, 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "south"}));
    }
