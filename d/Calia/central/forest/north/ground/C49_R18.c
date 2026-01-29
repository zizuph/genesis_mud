//Room type '

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C49_R18", ({"C49_R17", "C50_R17",
        "C50_R18", "C50_R19", "C49_R19", "C48_R19", "C48_R18", "C48_R17"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "northeast"}));

}

