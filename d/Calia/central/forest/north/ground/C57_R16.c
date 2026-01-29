//Room type ]

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C57_R16", ({"C57_R15", "C58_R15",
        "C58_R16", "C58_R17", "C57_R17", "C56_R17", "C56_R16", "C56_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "east"}));

}

