//Room type c

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C39_R11", ({0, 0, "C40_R11", "C40_R12",
        "C39_R12", "C38_R12", 0, 0}),
        ({"balsam", "cedar", "beech"}), ({"stream", "east", "north", "bog",
        "west"}));

}

