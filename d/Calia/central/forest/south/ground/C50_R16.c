//Room type {(}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C50_R16", ({"C50_R15", "C51_R15",
        "C51_R16", "C51_R17", "C50_R17", "C49_R17", "C49_R16", "C49_R15"}),
        ({"oak", "sycamore", "birch", "elm"}), 0, "southwest");
    }
