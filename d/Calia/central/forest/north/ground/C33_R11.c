//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C33_R11", ({0, 0, "C34_R11", "C34_R12",
        "C33_R12", "C32_R12", "C32_R11", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

