//Room type A

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C60_R15", ({"C60_R14", "C61_R14",
        "C61_R15", "C61_R16", "C60_R16", "C59_R16", "C59_R15", "C59_R14"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southwest", "east"}));

}

