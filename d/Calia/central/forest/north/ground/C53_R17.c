//Room type ]

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C53_R17", ({"C53_R16", "C54_R16",
        "C54_R17", "C54_R18", "C53_R18", "C52_R18", "C52_R17", "C52_R16"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "east"}));

}

