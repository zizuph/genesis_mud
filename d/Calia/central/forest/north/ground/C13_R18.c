//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C13_R18", ({"C13_R17", "C14_R17", "C14_R18",
        "C14_R19", 0, 0, "C12_R18", "C12_R17"}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

