//Room type l

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C46_R21", ({"C46_R20", "C47_R20", "C47_R21",
        0, 0, "C45_R22", "C45_R21", "C45_R20"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"thicket"}));

}

