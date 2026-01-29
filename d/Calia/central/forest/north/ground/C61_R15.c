//Room type B

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C61_R15", ({"C61_R14", "C62_R14",
        "C62_R15", "C62_R16", "C61_R16", "C60_R16", "C60_R15", "C60_R14"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "southeast"}));

}

