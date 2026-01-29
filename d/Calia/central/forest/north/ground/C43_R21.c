//Room type C

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C43_R21", ({"C43_R20", "C44_R20",
        "C44_R21", "C44_R22", "C43_R22", "C42_R22", "C42_R21", "C42_R20"}),
        ({"cedar", "balsam", "fir"}), ({"northeast", "south"}));

}

