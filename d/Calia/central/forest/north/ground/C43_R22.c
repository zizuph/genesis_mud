//Room type 5

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C43_R22", ({"C43_R21", "C44_R21",
        "C44_R22", "C44_R23", "C43_R23", "C42_R23", "C42_R22", "C42_R21"}),
        ({"cedar", "balsam", "fir"}), ({"north", "south"}));

}

