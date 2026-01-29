//Room type {V}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C20_R19", ({"C20_R18", "C21_R18",
        "C21_R19", "C21_R20", "C20_R20", "C19_R20", "C19_R19", "C19_R18"}),
        ({"sycamore", "birch", "elm"}), ({"west", "southeast"}));
    }
