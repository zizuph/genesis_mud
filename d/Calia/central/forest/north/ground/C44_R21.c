//Room type &

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C44_R21", ({"C44_R20", "C45_R20",
        "C45_R21", "C45_R22", "C44_R22", "C43_R22", "C43_R21", "C43_R20"}),
        ({"cedar", "spruce", "fir"}), ({"southwest", "east"}));

}

