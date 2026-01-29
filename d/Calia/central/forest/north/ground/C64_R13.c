//Room type p

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C64_R13", ({"C64_R12", 0, 0, 0, "C64_R14",
        "C63_R14", "C63_R13", "C63_R12"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "south"}));

}

