//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C33_R18", ({"C33_R17", "C34_R17",
        "C34_R18", "C34_R19", "C33_R19", "C32_R19", "C32_R18", "C32_R17"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
