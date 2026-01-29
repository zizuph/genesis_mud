//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C23_R13", ({0, 0, "C24_R13", "C24_R14",
        "C23_R14", "C22_R14", 0, 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

