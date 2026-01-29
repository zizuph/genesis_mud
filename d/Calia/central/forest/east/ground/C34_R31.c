//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C34_R31", ({"C34_R30", "C35_R30",
        "C35_R31", "C35_R32", "C34_R32", 0, "C33_R31", "C33_R30"}),
        ({"fir", "beech", "balsam"}));
    }
