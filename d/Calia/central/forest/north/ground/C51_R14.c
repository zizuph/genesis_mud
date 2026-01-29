//Room type s

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C51_R14", ({0, 0, "C52_R14", "C52_R15",
        "C51_R15", "C50_R15", "C50_R14", 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "east"}));

}

