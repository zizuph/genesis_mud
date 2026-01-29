//Room type l

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C52_R20", ({"C52_R19", "C53_R19", "C53_R20",
        0, 0, 0, "C51_R20", "C51_R19"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"thicket"}));

}

