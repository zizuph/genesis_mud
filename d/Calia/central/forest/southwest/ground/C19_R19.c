//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C19_R19", ({"C19_R18", "C20_R18",
        "C20_R19", "C20_R20", "C19_R20", "C18_R20", "C18_R19", "C18_R18"}),
        ({"sycamore", "birch", "elm"}), ({"west", "east"}));
    }
