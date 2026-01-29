//Room type s

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C44_R12", ({0, 0, "C45_R12", "C45_R13",
        "C44_R13", "C43_R13", "C43_R12", 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "east"}));

}

