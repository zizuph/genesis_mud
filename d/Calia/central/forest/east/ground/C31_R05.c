//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R05", ({"C31_R04", "C32_R04",
        "C32_R05", "C32_R06", "C31_R06", "C30_R06", "C30_R05", "C30_R04"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
