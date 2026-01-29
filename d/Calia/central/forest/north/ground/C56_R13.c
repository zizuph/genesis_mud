//Room type s

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C56_R13", ({0, 0, "C57_R13", "C57_R14",
        "C56_R14", "C55_R14", "C55_R13", 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "east"}));

}

