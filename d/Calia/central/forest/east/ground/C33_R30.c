//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C33_R30", ({"C33_R29", "C34_R29",
        "C34_R30", "C34_R31", "C33_R31", "C32_R31", "C32_R30", "C32_R29"}),
        ({"fir", "beech", "balsam"}));
    }
