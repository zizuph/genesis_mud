//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C66_R15", ({"C66_R14", "C67_R14",
        "C67_R15", "C67_R16", "C66_R16", "C65_R16", "C65_R15", "C65_R14"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
