//Room type K

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C33_R16", ({"C33_R15", "C34_R15",
        "C34_R16", "C34_R17", "C33_R17", "C32_R17", "C32_R16", "C32_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southeast", "west"}));

}

