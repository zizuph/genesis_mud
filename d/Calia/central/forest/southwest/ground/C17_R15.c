//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C17_R15", ({"C17_R14", "C18_R14",
        "C18_R15", "C18_R16", "C17_R16", "C16_R16", "C16_R15", "C16_R14"}),
        ({"sycamore", "birch", "elm"}));
    }
