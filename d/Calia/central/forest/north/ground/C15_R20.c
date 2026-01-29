//Room type t

inherit "/d/Calia/central/forest/baserooms/base_edge";

void
create_room()

{

    create_forest_edge("C15_R20", ({"C15_R19", "C16_R19", "C16_R20",
        0, 0, 0, 0, "C14_R19"}),
        ({"cedar", "fir", "balsam"}), ({"thicket"}));

}

