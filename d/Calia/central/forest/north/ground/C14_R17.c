//Room type =

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C14_R17", ({"C14_R16", "C15_R16",
        "C15_R17", "C15_R18", "C14_R18", "C13_R18", "C13_R17", "C13_R16"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "east",
            "southeast"}));

}

