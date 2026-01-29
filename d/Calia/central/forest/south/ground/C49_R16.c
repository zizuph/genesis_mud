//Room type {(}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C49_R16", ({"C49_R15", "C50_R15",
        "C50_R16", "C50_R17", "C49_R17", "C48_R17", "C48_R16", "C48_R15"}),
        ({"oak", "sycamore", "birch", "elm"}), 0, "southwest");
    }
