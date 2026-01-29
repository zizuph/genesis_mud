//Room type y

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C30_R12", ({"C30_R11", "C31_R11",
        "C31_R12", "C31_R13", "C30_R13", "C29_R13", "C29_R12", "C29_R11"}),
        ({"cedar", "spruce", "fir"}));

}

