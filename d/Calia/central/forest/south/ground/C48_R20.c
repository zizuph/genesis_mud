//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C48_R20", ({"C48_R19", "C49_R19",
        "C49_R20", "C49_R21", "C48_R21", "C47_R21", "C47_R20", "C47_R19"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"west", "north"}));
    }
