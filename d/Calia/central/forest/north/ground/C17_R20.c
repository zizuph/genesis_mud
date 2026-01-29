//Room type i

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C17_R20", ({"C17_R19", "C18_R19", "C18_R20",
        0, 0, 0, "C16_R20", "C16_R19"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));

}

