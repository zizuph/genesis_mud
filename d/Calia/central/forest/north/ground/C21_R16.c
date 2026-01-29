//Room type z

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C21_R16", ({"C21_R15", "C22_R15",
        "C22_R16", "C22_R17", "C21_R17", "C20_R17", "C20_R16", "C20_R15"}),
        ({"cedar", "pine", "spruce", "fir"}));

}
