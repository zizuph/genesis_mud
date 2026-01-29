//Room type {p}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C20_R17", ({"C20_R16", "C21_R16", "C21_R17",
        "C21_R18", 0, 0, "C19_R17", "C19_R16"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "south"}));
    }
