//Room type L

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C44_R17", ({"C44_R16", "C45_R16",
        "C45_R17", "C45_R18", "C44_R18", "C43_R18", "C43_R17", "C43_R16"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));

}

