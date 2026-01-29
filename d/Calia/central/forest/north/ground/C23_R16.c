//Room type z

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C23_R16", ({"C23_R15", "C24_R15",
        "C24_R16", "C24_R17", "C23_R17", "C22_R17", "C22_R16", "C22_R15"}),
        ({"cedar", "pine", "spruce", "fir"}));

}
