//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C13_R16", ({0, "C14_R15", "C14_R16",
        "C14_R17", "C13_R17", "C12_R17", "C12_R16", 0}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

