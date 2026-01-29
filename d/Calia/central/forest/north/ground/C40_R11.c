//Room type s

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C40_R11", ({0, 0, "C41_R11", "C41_R12",
        "C40_R12", "C39_R12", "C39_R11", 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "east"}));

}

