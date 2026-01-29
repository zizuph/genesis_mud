//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C35_R30", ({"C35_R29", "C36_R29",
        "C36_R30", "C36_R31", "C35_R31", "C34_R31", "C34_R30", "C34_R29"}),
        ({"fir", "beech", "balsam"}));
    }
