//Room type -

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C19_R18", ({"C19_R17", "C20_R17",
        "C20_R18", "C20_R19", "C19_R19", "C18_R19", "C18_R18", "C18_R17"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));

}

