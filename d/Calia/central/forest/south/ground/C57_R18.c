//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C57_R18", ({"C57_R17", "C58_R17",
        "C58_R18", "C58_R19", "C57_R19", "C56_R19", "C56_R18", "C56_R17"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
