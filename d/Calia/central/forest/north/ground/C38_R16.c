//Room type -

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C38_R16", ({"C38_R15", "C39_R15",
        "C39_R16", "C39_R17", "C38_R17", "C37_R17", "C37_R16", "C37_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));

}

