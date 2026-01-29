//Room type {&}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C66_R12", ({"C66_R11", "C67_R11",
        "C67_R12", "C67_R13", "C66_R13", "C65_R13", "C65_R12", "C65_R11"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"southwest", "north"}));
    }
