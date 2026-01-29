//Room type {#}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C64_R14", ({"C64_R13", "C65_R13",
        "C65_R14", "C65_R15", "C64_R15", "C63_R15", "C63_R14", "C63_R13"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"west", "northeast"}));
    }
