//Room type m

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C42_R23", ({"C42_R22", "C43_R22", "C43_R23",
        "C43_R24", "C42_R24", 0, 0, 0}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));

}

