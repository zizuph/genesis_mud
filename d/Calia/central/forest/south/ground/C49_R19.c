//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C49_R19", ({"C49_R18", "C50_R18",
        "C50_R19", "C50_R20", "C49_R20", "C48_R20", "C48_R19", "C48_R18"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
