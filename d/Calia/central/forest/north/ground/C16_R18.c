//Room type O

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C16_R18", ({"C16_R17", "C17_R17",
        "C17_R18", "C17_R19", "C16_R19", "C15_R19", "C15_R18", "C15_R17"}),
        ({"cedar", "pine", "spruce", "fir"}), "southwest");

}

