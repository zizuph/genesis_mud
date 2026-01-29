//Room type l

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C51_R20", ({"C51_R19", "C52_R19", "C52_R20",
        0, 0, 0, "C50_R20", "C50_R19"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"thicket"}));

}

