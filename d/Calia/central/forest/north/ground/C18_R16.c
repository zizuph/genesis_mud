//Room type N

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C18_R16", ({"C18_R15", "C19_R15",
        "C19_R16", "C19_R17", "C18_R17", "C17_R17", "C17_R16", "C17_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}),
            "northeast");

}

