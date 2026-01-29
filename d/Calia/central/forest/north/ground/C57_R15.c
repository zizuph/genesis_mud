//Room type z

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C57_R15", ({"C57_R14", "C58_R14",
        "C58_R15", "C58_R16", "C57_R16", "C56_R16", "C56_R15", "C56_R14"}),
        ({"cedar", "pine", "spruce", "fir"}));

}
