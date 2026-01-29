//Room type z

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C45_R16", ({"C45_R15", "C46_R15",
        "C46_R16", "C46_R17", "C45_R17", "C44_R17", "C44_R16", "C44_R15"}),
        ({"cedar", "pine", "spruce", "fir"}));

}
