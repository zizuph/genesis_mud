//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C21_R14", ({0, 0, "C22_R14", "C22_R15",
        "C21_R15", "C20_R15", 0, 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

