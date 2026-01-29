//Room type h

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C25_R19", ({"C25_R18", "C26_R18", "C26_R19",
        0, 0, 0, "C24_R19", "C24_R18"}),
        ({"fir", "cedar", "birch"}), ({"mountains"}));

}

