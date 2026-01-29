//Room type k

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C44_R26", ({"C44_R25", 0, 0, 0, 0, 0,
        "C43_R26", "C43_R25"}),
        ({"cedar", "beech", "fir", "balsam"}), ({"thicket", "west",
        "mountains", "south"}));

}

