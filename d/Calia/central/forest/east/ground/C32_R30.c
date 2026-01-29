//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C32_R30", ({"C32_R29", "C33_R29",
        "C33_R30", "C33_R31", "C32_R31", "C31_R31", "C31_R30", "C31_R29"}),
        ({"fir", "beech", "balsam"}));
    }
