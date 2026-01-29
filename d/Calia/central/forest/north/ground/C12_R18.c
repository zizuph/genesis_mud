//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C12_R18", ({"C12_R17", "C13_R17", "C13_R18",
        0, 0, 0, "C11_R18", "C11_R17"}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

