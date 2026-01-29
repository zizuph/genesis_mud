//Room type q

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C53_R13", ({0, 0, "C54_R13", "C54_R14",
        "C53_R14", "C52_R14", 0, 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "northeast"}));

}

