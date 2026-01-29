//Room type m

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C41_R20", ({"C41_R19", "C42_R19", "C42_R20",
        "C42_R21", 0, 0, "C40_R20", "C40_R19"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));

}

