//Room type z

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C30_R16", ({"C30_R15", "C31_R15",
        "C31_R16", "C31_R17", "C30_R17", "C29_R17", "C29_R16", "C29_R15"}),
        ({"cedar", "pine", "spruce", "fir"}));

}
