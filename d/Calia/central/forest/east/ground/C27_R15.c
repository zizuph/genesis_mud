//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C27_R15", ({"C27_R14", "C28_R14",
        "C28_R15", "C28_R16", "C27_R16", "C26_R16", "C26_R15", "C26_R14"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
