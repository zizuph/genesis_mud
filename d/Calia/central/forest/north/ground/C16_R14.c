//Room type v

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C16_R14", ({0, 0, "C17_R14", "C17_R15",
        "C16_R15", "C15_R15", 0, 0}),
        ({"cedar", "fir", "balsam"}), ({"thicket", "west", "bog", "north"}));

}

