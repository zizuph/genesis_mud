//Room type {#}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C60_R16", ({"C60_R15", "C61_R15",
        "C61_R16", "C61_R17", "C60_R17", "C59_R17", "C59_R16", "C59_R15"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"west", "northeast"}));
    }
