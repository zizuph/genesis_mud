//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C35_R31", ({"C35_R30", "C36_R30",
        "C36_R31", "C36_R32", "C35_R32", "C34_R32", "C34_R31", "C34_R30"}),
        ({"fir", "beech", "balsam"}));
    }
