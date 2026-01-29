//Room type r

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C45_R12", ({0, 0, "C46_R12", "C46_R13",
        "C45_R13", "C44_R13", "C44_R12", 0}),
        ({"balsam", "cedar", "fir"}), ({"stream", "southeast"}));

}

