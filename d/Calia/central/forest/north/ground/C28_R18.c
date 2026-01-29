//Room type @

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C28_R18", ({"C28_R17", "C29_R17",
        "C29_R18", "C29_R19", "C28_R19", "C27_R19", "C27_R18", "C27_R17"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"pit"}));

}

