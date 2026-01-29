//Room type -

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C13_R17", ({"C13_R16", "C14_R16",
        "C14_R17", "C14_R18", "C13_R18", "C12_R18", "C12_R17", "C12_R16"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));

}

