//Room type {)}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C30_R07", ({"C30_R06", "C31_R06",
        "C31_R07", "C31_R08", "C30_R08", "C29_R08", "C29_R07", "C29_R06"}),
        ({"cedar", "pine", "balsam"}), ({"southwest", "north"}));
    }
