//Room type n

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C60_R18", ({"C60_R17", "C61_R17", 0, 0, 0,
        "C59_R19", "C59_R18", "C59_R17"}),
        ({"cedar", "beech", "balsam"}), ({"thicket"}));

}

