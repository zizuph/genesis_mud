//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R19", ({"C31_R18", "C32_R18",
        "C32_R19", "C32_R20", "C31_R20", "C30_R20", "C30_R19", "C30_R18"}),
        ({"sycamore", "birch", "elm"}));
    }
