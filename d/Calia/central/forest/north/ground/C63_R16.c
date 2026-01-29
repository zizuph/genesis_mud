//Room type ~

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C63_R16", ({"C63_R15", "C64_R15",
        "C64_R16", "C64_R17", "C63_R17", "C62_R17", "C62_R16", "C62_R15"}),
        ({"cedar", "balsam", "fir"}), ({"west", "east"}));

}

