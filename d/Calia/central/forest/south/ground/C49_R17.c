//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C49_R17", ({"C49_R16", "C50_R16",
        "C50_R17", "C50_R18", "C49_R18", "C48_R18", "C48_R17", "C48_R16"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
