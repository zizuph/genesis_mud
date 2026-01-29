//Room type m

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C42_R21", ({"C42_R20", "C43_R20", "C43_R21",
        "C43_R22", "C42_R22", 0, 0, "C41_R20"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));

}

