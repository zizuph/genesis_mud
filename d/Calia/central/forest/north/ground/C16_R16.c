//Room type M

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C16_R16", ({"C16_R15", "C17_R15",
        "C17_R16", "C17_R17", "C16_R17", "C15_R17", "C15_R16", "C15_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southwest", "east"}),
        "northwest");

}

