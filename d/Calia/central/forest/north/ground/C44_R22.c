//Room type l

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C44_R22", ({"C44_R21", "C45_R21", "C45_R22",
        0, "C44_R23", "C43_R23", "C43_R22", "C43_R21"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"thicket"}));

}

