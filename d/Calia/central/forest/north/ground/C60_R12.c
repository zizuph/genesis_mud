//Room type s

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C60_R12", ({0, 0, "C61_R12", "C61_R13",
        "C60_R13", "C59_R13", "C59_R12", 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "east"}));

}

