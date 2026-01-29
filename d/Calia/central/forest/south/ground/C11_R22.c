//Room type {V}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C11_R22", ({"C11_R21", "C12_R21",
        "C12_R22", "C12_R23", "C11_R23", "C10_R23", "C10_R22", "C10_R21"}),
        ({"oak", "birch", "hickory"}), ({"west", "southeast"}));
    }
