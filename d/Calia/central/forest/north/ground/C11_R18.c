//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C11_R18", ({"C11_R17", "C12_R17", "C12_R18",
        0, 0, 0, 0, 0}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

