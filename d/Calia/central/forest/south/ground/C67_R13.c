//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C67_R13", ({"C67_R12", "C68_R12",
        "C68_R13", "C68_R14", "C67_R14", "C66_R14", "C66_R13", "C66_R12"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
