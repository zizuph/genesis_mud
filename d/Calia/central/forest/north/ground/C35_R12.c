//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C35_R12", ({0, 0, "C36_R12", "C36_R13",
        "C35_R13", "C34_R13", "C34_R12", "C34_R11"}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

