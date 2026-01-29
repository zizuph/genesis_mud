//Room type y

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C32_R12", ({"C32_R11", "C33_R11",
        "C33_R12", "C33_R13", "C32_R13", "C31_R13", "C31_R12", "C31_R11"}),
        ({"cedar", "spruce", "fir"}));

}

