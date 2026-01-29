//Room type q

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C52_R14", ({0, "C53_R13", "C53_R14",
        "C53_R15", "C52_R15", "C51_R15", "C51_R14", 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "northeast"}));

}

