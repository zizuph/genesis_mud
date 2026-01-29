//Room type b

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C18_R15", ({0, 0, "C19_R15", "C19_R16",
        "C18_R16", "C17_R16", "C17_R15", "C17_R14"}),
        ({"balsam", "fir", "beech"}), ({"bog"}));

}

