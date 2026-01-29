//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C14_R19", ({"C14_R18", "C15_R18", "C15_R19",
        "C15_R20", 0, 0, 0, "C13_R18"}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

