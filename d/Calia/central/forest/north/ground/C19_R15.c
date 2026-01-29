//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C19_R15", ({0, 0, "C20_R15", "C20_R16",
        "C19_R16", "C18_R16", "C18_R15", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

