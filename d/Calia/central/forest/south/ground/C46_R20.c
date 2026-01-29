//Room type {=}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C46_R20", ({"C46_R19", "C47_R19",
        "C47_R20", "C47_R21", "C46_R21", "C45_R21", "C45_R20", "C45_R19"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"west", "east"}));
    }
