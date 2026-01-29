//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C46_R19", ({"C46_R18", "C47_R18",
        "C47_R19", "C47_R20", "C46_R20", "C45_R20", "C45_R19", "C45_R18"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
