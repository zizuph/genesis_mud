//Room type r

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C46_R14", ({"C46_R13", 0, "C47_R14",
        "C47_R15", "C46_R15", "C45_R15", "C45_R14", "C45_R13"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "southeast"}));

}

