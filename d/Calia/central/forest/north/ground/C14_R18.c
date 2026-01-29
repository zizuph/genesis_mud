//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C14_R18", ({"C14_R17", "C15_R17", "C15_R18",
        "C15_R19", "C14_R19", 0, "C13_R18", "C13_R17"}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

