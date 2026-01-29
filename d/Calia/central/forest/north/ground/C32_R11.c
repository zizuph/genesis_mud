//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C32_R11", ({0, 0, "C33_R11", "C33_R12",
        "C32_R12", "C31_R12", "C31_R11", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

