//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R11", ({"C29_R10", "C30_R10",
        "C30_R11", "C30_R12", "C29_R12", "C28_R12", "C28_R11", "C28_R10"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
