//Room type #

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C41_R12", ({"C41_R11", "C42_R11",
        "C42_R12", "C42_R13", "C41_R13", "C40_R13", "C40_R12", "C40_R11"}),
        ({"cedar", "spruce", "fir"}), ({"pit"}));

}

