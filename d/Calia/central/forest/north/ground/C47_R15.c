//Room type s

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C47_R15", ({"C47_R14", 0, "C48_R15",
        "C48_R16", "C47_R16", "C46_R16", "C46_R15", "C46_R14"}),
        ({"balsam", "cedar", "fir"}), ({"stream", "east"}));

}

