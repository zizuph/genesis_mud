//Room type 6

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C43_R24", ({"C43_R23", "C44_R23",
        "C44_R24", "C44_R25", "C43_R25", "C42_R25", "C42_R24", "C42_R23"}),
        ({"cedar", "balsam", "fir"}), ({"north", "east"}));

}

