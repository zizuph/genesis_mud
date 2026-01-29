//Room type Q

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C62_R16", ({"C62_R15", "C63_R15",
        "C63_R16", "C63_R17", "C62_R17", "C61_R17", "C61_R16", "C61_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));

}

