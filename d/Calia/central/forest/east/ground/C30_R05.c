//Room type {|}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C30_R05", ({"C30_R04", "C31_R04",
        "C31_R05", "C31_R06", "C30_R06", "C29_R06", "C29_R05", "C29_R04"}),
        ({"cedar", "pine", "balsam"}), ({"north", "south"}));
    }
