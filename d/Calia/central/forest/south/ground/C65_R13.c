//Room type {'}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C65_R13", ({"C65_R12", "C66_R12",
        "C66_R13", "C66_R14", "C65_R14", "C64_R14", "C64_R13", "C64_R12"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"southwest", "northeast"}));
    }
