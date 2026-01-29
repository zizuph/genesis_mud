//Room type i

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C23_R18", ({"C23_R17", "C24_R17", "C24_R18",
        "C24_R19", 0, 0, "C22_R18", "C22_R17"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));

}

