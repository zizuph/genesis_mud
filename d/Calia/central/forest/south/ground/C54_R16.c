//Room type {)}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C54_R16", ({"C54_R15", "C55_R15",
        "C55_R16", "C55_R17", "C54_R17", "C53_R17", "C53_R16", "C53_R15"}),
        ({"oak", "sycamore", "birch", "elm"}), 0, "southeast");
    }
