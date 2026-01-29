//Room type {c}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C19_R13", ({0, 0, "C20_R13", "C20_R14",
        "C19_R14", 0, 0, 0}),
        ({"balsam", "cedar", "beech"}), ({"stream", "west", "bog", "north"}));
    }
