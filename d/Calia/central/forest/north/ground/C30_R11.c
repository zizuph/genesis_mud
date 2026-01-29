//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C30_R11", ({0, 0, "C31_R11", "C31_R12",
        "C30_R12", "C29_R12", "C29_R11", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

