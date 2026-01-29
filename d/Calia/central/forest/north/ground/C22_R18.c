//Room type i

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C22_R18", ({"C22_R17", "C23_R17", "C23_R18",
        0, 0, "C21_R19", "C21_R18", "C21_R17"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));

}

