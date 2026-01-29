//Room type {=}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C59_R16", ({"C59_R15", "C60_R15",
        "C60_R16", "C60_R17", "C59_R17", "C58_R17", "C58_R16", "C58_R15"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"west", "east"}));
    }
