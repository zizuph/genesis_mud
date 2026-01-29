//Room type \

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C43_R16", ({"C43_R15", "C44_R15",
        "C44_R16", "C44_R17", "C43_R17", "C42_R17", "C42_R16", "C42_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "southeast"}));

}

