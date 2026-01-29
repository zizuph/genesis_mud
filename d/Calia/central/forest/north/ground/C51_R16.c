//Room type z

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C51_R16", ({"C51_R15", "C52_R15",
        "C52_R16", "C52_R17", "C51_R17", "C50_R17", "C50_R16", "C50_R15"}),
        ({"cedar", "pine", "spruce", "fir"}));

}
