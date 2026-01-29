//Room type A

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C56_R16", ({"C56_R15", "C57_R15",
        "C57_R16", "C57_R17", "C56_R17", "C55_R17", "C55_R16", "C55_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southwest", "east"}));

}

