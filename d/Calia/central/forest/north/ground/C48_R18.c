//Room type ~

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C48_R18", ({"C48_R17", "C49_R17",
        "C49_R18", "C49_R19", "C48_R19", "C47_R19", "C47_R18", "C47_R17"}),
        ({"cedar", "balsam", "fir"}), ({"west", "east"}));

}

