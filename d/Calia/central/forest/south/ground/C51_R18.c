//Room type {=}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C51_R18", ({"C51_R17", "C52_R17",
        "C52_R18", "C52_R19", "C51_R19", "C50_R19", "C50_R18", "C50_R17"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"west", "east"}));
    }
