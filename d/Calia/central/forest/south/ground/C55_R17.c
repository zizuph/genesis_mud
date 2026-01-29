//Room type {'}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C55_R17", ({"C55_R16", "C56_R16",
        "C56_R17", "C56_R18", "C55_R18", "C54_R18", "C54_R17", "C54_R16"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"southwest", "northeast"}));
    }
