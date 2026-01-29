//Room type q

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C62_R11", ({0, 0, "C63_R11", "C63_R12",
        "C62_R12", "C61_R12", 0, 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "northeast"}));

}

