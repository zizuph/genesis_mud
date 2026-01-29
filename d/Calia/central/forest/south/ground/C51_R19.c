//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C51_R19", ({"C51_R18", "C52_R18",
        "C52_R19", "C52_R20", "C51_R20", "C50_R20", "C50_R19", "C50_R18"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
