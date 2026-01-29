//Room type s

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C57_R13", ({0, "C58_R12", "C58_R13",
        "C58_R14", "C57_R14", "C56_R14", "C56_R13", 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "east"}));

}

