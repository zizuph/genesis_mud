//Room type -

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C27_R16", ({"C27_R15", "C28_R15",
        "C28_R16", "C28_R17", "C27_R17", "C26_R17", "C26_R16", "C26_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));

}

