//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C48_R21", ({"C48_R20", "C49_R20",
        "C49_R21", "C49_R22", "C48_R22", "C47_R22", "C47_R21", "C47_R20"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
