//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C20_R15", ({"C20_R14", "C21_R14",
        "C21_R15", "C21_R16", "C20_R16", "C19_R16", "C19_R15", "C19_R14"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
