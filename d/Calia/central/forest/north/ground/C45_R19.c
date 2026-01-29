//Room type Y

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C45_R19", ({"C45_R18", "C46_R18",
        "C46_R19", "C46_R20", "C45_R20", "C44_R20", "C44_R19", "C44_R18"}),
        ({"cedar", "balsam", "fir"}), ({"northeast", "southwest"}));

}

