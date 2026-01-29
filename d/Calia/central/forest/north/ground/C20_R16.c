//Room type K

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C20_R16", ({"C20_R15", "C21_R15",
        "C21_R16", "C21_R17", "C20_R17", "C19_R17", "C19_R16", "C19_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southeast", "west"}));

}

