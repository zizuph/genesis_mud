//Room type i

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C18_R20", ({"C18_R19", "C19_R19", 0, 0, 0, 0,
        "C17_R20", "C17_R19"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));

}

