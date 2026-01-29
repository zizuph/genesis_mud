//Room type h

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C30_R19", ({"C30_R18", "C31_R18", "C31_R19",
        0, 0, 0, "C29_R19", "C29_R18"}),
        ({"fir", "cedar", "birch"}), ({"mountains"}));

}

