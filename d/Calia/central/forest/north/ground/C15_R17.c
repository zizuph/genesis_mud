//Room type %

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C15_R17", ({"C15_R16", "C16_R16",
        "C16_R17", "C16_R18", "C15_R18", "C14_R18", "C14_R17", "C14_R16"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "northeast"}));

}

