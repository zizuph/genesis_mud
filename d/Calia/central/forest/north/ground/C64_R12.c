//Room type r

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C64_R12", ({0, 0, 0, 0, "C64_R13", "C63_R13",
        "C63_R12", "C63_R11"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "southeast"}));

}

