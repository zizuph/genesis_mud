//Room type {*}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C53_R16", ({"C53_R15", "C54_R15",
        "C54_R16", "C54_R17", "C53_R17", "C52_R17", "C52_R16", "C52_R15"}),
        ({"oak", "sycamore", "birch", "elm"}), 0, "south");
    }
