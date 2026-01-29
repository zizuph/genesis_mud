//Room type i

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C20_R19", ({"C20_R18", "C21_R18", "C21_R19",
        0, 0, 0, "C19_R19", "C19_R18"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));

}

