/*
 * White-black Bubbly Potion for Task 3 for the Academy of Elemental Arts
 *
 * This is the potion that the students will get from Raspatoon when
 * they complete the task.
 *
 * Created by Petros, December 2009
 */

#pragma strict_types

inherit "/std/potion";

// Global Variables
public string       owner_name;

public void
create_potion()
{
    ::create_potion();

    add_adj( ({ "white-black", "bubbly" }) );
    add_name("academic_raspatoon_potion");
    set_short("white-black bubbly potion");
    set_id_long("This is an odd concoction of some sort, it smells a bit "
        + "vile honestly. You wonder what happens if you were to <taste> or "
        + "<smell> it before giving it to Taskmaster Amjal.\n");
    set_unid_long("This is an odd concoction of some sort, it smells a bit "
        + "vile honestly. You wonder what happens if you were to <taste> or "
        + "<smell> it before giving it to Taskmaster Amjal.\n");
    set_unid_smell("The potion is extremely putrid and you can barely "
        + "discern anything about it because of the overwhelming "
        + "odor.\n");
    set_id_smell("Smelling the potion you are reminded of the smell of "
        + "drudgeworth. This must be the famed Crazy-Krougian potion.\n");
    set_unid_taste("You carefully taste the potion, despite its slimy texture "
        + "it is rather tasty with a hint of something spicy.\n");
    set_id_taste("You carefully taste the potion, despite its slimy texture "
        + "it is rather tasty with a hint of something spicy, drudgeworth "
        + "maybe?\n");
    set_potion_name("task_3_potion");
}

public void
set_owner_name(string name)
{
    owner_name = name;
}

public string
query_owner_name()
{
    return owner_name;
}
