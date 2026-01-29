//Room type K

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C45_R17", ({"C45_R16", "C46_R16",
        "C46_R17", "C46_R18", "C45_R18", "C44_R18", "C44_R17", "C44_R16"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southeast", "west"}));

}

