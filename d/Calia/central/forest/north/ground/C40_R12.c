//Room type y

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C40_R12", ({"C40_R11", "C41_R11",
        "C41_R12", "C41_R13", "C40_R13", "C39_R13", "C39_R12", "C39_R11"}),
        ({"cedar", "spruce", "fir"}));

}

