//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C27_R11", ({0, 0, "C28_R11", "C28_R12",
        "C27_R12", "C26_R12", "C26_R11", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

