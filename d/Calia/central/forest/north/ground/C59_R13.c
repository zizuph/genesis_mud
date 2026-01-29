//Room type q

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C59_R13", ({"C59_R12", "C60_R12", "C60_R13",
        "C60_R14", "C59_R14", "C58_R14", "C58_R13", "C58_R12"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "northeast"}));

}

