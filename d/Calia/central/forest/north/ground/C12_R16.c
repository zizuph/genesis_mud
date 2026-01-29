//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C12_R16", ({0, 0, "C13_R16", "C13_R17",
        "C12_R17", "C11_R17", "C11_R16", 0}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

