//Room type l

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C45_R22", ({"C45_R21", "C46_R21", 0, 0, 0,
        "C44_R23", "C44_R22", "C44_R21"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"thicket"}));

}

