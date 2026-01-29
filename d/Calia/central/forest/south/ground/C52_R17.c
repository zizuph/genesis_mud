//Room type {*}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C52_R17", ({"C52_R16", "C53_R16",
        "C53_R17", "C53_R18", "C52_R18", "C51_R18", "C51_R17", "C51_R16"}),
        ({"oak", "sycamore", "birch", "elm"}), 0, "south");
    }
