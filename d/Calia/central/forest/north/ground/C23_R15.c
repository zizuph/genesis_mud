//Room type P

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C23_R15", ({"C23_R14", "C24_R14",
        "C24_R15", "C24_R16", "C23_R16", "C22_R16", "C22_R15", "C22_R14"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southwest", "east"}));

}

