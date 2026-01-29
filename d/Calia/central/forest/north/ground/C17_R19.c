//Room type J

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C17_R19", ({"C17_R18", "C18_R18",
        "C18_R19", "C18_R20", "C17_R20", "C16_R20", "C16_R19", "C16_R18"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "northeast"}));

}

