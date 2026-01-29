//Room type n

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C62_R17", ({"C62_R16", "C63_R16", "C63_R17",
        "C63_R18", 0, 0, "C61_R17", "C61_R16"}),
        ({"cedar", "beech", "balsam"}), ({"thicket"}));

}

