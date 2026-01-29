//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C36_R12", ({0, 0, "C37_R12", "C37_R13",
        "C36_R13", "C35_R13", "C35_R12", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

