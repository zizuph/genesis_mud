//Room type m

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C42_R26", ({"C42_R25", "C43_R25", "C43_R26",
        0, 0, 0, 0, 0}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));

}

