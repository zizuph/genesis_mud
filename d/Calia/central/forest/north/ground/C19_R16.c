//Room type -

inherit "/d/Calia/central/forest/baserooms/base_interior";

void
create_room()

{

    create_forest_interior("C19_R16", ({"C19_R15", "C20_R15",
        "C20_R16", "C20_R17", "C19_R17", "C18_R17", "C18_R16", "C18_R15"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));

}

