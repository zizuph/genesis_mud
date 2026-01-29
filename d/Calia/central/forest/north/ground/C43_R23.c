//Room type 5

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C43_R23", ({"C43_R22", "C44_R22",
        "C44_R23", "C44_R24", "C43_R24", "C42_R24", "C42_R23", "C42_R22"}),
        ({"cedar", "balsam", "fir"}), ({"north", "south"}));

}

