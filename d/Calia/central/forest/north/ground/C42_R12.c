//Room type r

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C42_R12", ({"C42_R11", 0, "C43_R12",
        "C43_R13", "C42_R13", "C41_R13", "C41_R12", "C41_R11"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "southeast"}));

}

