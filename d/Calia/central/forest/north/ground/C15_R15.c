//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C15_R15", ({0, "C16_R14", "C16_R15",
        "C16_R16", "C15_R16", "C14_R16", "C14_R15", 0}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

