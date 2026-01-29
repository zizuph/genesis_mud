//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C65_R16", ({"C65_R15", "C66_R15",
        "C66_R16", "C66_R17", "C65_R17", "C64_R17", "C64_R16", "C64_R15"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
