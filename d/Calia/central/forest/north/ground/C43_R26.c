//Room type m

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C43_R26", ({"C43_R25", "C44_R25", "C44_R26",
        0, 0, 0, "C42_R26", "C42_R25"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));

}

