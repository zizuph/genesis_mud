//Room type #

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C59_R14", ({"C59_R13", "C60_R13",
        "C60_R14", "C60_R15", "C59_R15", "C58_R15", "C58_R14", "C58_R13"}),
        ({"cedar", "spruce", "fir"}), ({"pit"}));

}

