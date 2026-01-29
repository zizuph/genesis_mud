//Room type z

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C32_R17", ({"C32_R16", "C33_R16",
        "C33_R17", "C33_R18", "C32_R18", "C31_R18", "C31_R17", "C31_R16"}),
        ({"cedar", "pine", "spruce", "fir"}));

}
