//Room type s

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C43_R12", ({0, 0, "C44_R12", "C44_R13",
        "C43_R13", "C42_R13", "C42_R12", "C42_R11"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "east"}));

}

