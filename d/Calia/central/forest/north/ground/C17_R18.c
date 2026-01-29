//Room type ^

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C17_R18", ({"C17_R17", "C18_R17",
        "C18_R18", "C18_R19", "C17_R19", "C16_R19", "C16_R18", "C16_R17"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"pit"}), "south");

}

