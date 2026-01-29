//Room type Y

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C44_R20", ({"C44_R19", "C45_R19",
        "C45_R20", "C45_R21", "C44_R21", "C43_R21", "C43_R20", "C43_R19"}),
        ({"cedar", "balsam", "fir"}), ({"northeast", "southwest"}));

}

