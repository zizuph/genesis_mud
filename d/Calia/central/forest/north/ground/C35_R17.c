//Room type -

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C35_R17", ({"C35_R16", "C36_R16",
        "C36_R17", "C36_R18", "C35_R18", "C34_R18", "C34_R17", "C34_R16"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));

}

