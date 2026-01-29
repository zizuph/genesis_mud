//Room type 7

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C46_R18", ({"C46_R17", "C47_R17",
        "C47_R18", "C47_R19", "C46_R19", "C45_R19", "C45_R18", "C45_R17"}),
        ({"cedar", "balsam", "fir"}), ({"northwest", "east", "southwest"}));

}

