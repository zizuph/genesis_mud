//Room type T

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C18_R18", ({"C18_R17", "C19_R17",
        "C19_R18", "C19_R19", "C18_R19", "C17_R19", "C17_R18", "C17_R17"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southwest", "east"}),
        "southeast");

}

