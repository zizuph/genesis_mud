//Room type h

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C27_R19", ({"C27_R18", "C28_R18", "C28_R19",
        0, 0, 0, "C26_R19", "C26_R18"}),
        ({"fir", "cedar", "birch"}), ({"mountains"}));

}

