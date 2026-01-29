//Room type l

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C49_R20", ({"C49_R19", "C50_R19", "C50_R20",
        0, "C49_R21", "C48_R21", "C48_R20", "C48_R19"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"thicket"}));

}

