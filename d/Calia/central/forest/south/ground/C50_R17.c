//Room type {(}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C50_R17", ({"C50_R16", "C51_R16",
        "C51_R17", "C51_R18", "C50_R18", "C49_R18", "C49_R17", "C49_R16"}),
        ({"oak", "sycamore", "birch", "elm"}), 0, "southwest");
    }
