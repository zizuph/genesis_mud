//Room type r

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C46_R13", ({"C46_R12", 0, 0, "C47_R14",
        "C46_R14", "C45_R14", "C45_R13", "C45_R12"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "southeast"}));

}

