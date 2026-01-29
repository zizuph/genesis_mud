//Room type K

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C42_R15", ({"C42_R14", "C43_R14",
        "C43_R15", "C43_R16", "C42_R16", "C41_R16", "C41_R15", "C41_R14"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southeast", "west"}));

}

