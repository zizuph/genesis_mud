//Room type {p}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C21_R17", ({"C21_R16", "C22_R16", "C22_R17",
        "C22_R18", "C21_R18", 0, "C20_R17", "C20_R16"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "south"}));
    }
