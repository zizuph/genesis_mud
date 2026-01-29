//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C66_R14", ({"C66_R13", "C67_R13",
        "C67_R14", "C67_R15", "C66_R15", "C65_R15", "C65_R14", "C65_R13"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
