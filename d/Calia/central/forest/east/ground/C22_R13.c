//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C22_R13", ({"C22_R12", "C23_R12",
        "C23_R13", "C23_R14", "C22_R14", "C21_R14", "C21_R13", "C21_R12"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
