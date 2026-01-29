//Room type {/}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C27_R19", ({"C27_R18", "C28_R18",
        "C28_R19", "C28_R20", "C27_R20", "C26_R20", "C26_R19", "C26_R18"}),
        ({"sycamore", "birch", "elm"}), ({"southwest", "northeast"}));
    }
