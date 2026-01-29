//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R13", ({"C29_R12", "C30_R12",
        "C30_R13", "C30_R14", "C29_R14", "C28_R14", "C28_R13", "C28_R12"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
