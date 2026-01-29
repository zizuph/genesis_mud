//Room type q

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C58_R12", ({0, 0, "C59_R12", "C59_R13",
        "C58_R13", "C57_R13", 0, 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "northeast"}));

}

