//Room type P

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C37_R16", ({"C37_R15", "C38_R15",
        "C38_R16", "C38_R17", "C37_R17", "C36_R17", "C36_R16", "C36_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southwest", "east"}));

}

