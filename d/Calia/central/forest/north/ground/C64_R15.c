//Room type r

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C64_R15", ({"C64_R14", 0, "C65_R15",
        "C65_R16", "C64_R16", "C63_R16", "C63_R15", "C63_R14"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "southeast"}));

}

