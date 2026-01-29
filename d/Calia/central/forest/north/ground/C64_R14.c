//Room type p

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C64_R14", ({"C64_R13", 0, 0, "C65_R15",
        "C64_R15", "C63_R15", "C63_R14", "C63_R13"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "south"}));

}

