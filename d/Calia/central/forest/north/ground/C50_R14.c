//Room type q

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C50_R14", ({0, 0, "C51_R14", "C51_R15",
        "C50_R15", "C49_R15", 0, 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "northeast"}));

}

