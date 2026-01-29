//Room type {2}

inherit "/d/Calia/central/forest/baserooms/base_entrance";

void create_room()
    {
    add_exit("/d/Calia/uhclem/workroom", "northwest", 0, 2);
    create_forest_entrance("C06_R20", ({0, 0, "C07_R20", "C07_R21",
        "C06_R21", 0, 0, 0}),
        ({"sycamore", "cedar", "elm", "birch"}),
        ({"northwest", "southeast"}), "thicket", "northwest");
    }
