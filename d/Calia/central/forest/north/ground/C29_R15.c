//Room type R

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C29_R15", ({"C29_R14", "C30_R14",
        "C30_R15", "C30_R16", "C29_R16", "C28_R16", "C28_R15", "C28_R14"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "southwest"}));

}

