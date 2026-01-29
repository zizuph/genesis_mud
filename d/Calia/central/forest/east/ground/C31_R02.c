//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C31_R02", ({"C31_R01", "C32_R01", "C32_R02",
        "C32_R03", "C31_R03", "C30_R03", "C30_R02", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
