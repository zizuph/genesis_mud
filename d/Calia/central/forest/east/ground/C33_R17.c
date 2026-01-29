//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C33_R17", ({"C33_R16", "C34_R16",
        "C34_R17", "C34_R18", "C33_R18", "C32_R18", "C32_R17", "C32_R16"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
