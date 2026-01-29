/*
 * This is snake meat. It is good food.
 */
inherit "/std/leftover";

void
create_leftover()
{
    set_name(({"chunk of snake meat", "meat", "snake meat", "chunk",
        "leftover"}) );
    set_pname( ({"chunks of snake meat", "chunks", "meats", "snake meats",
        "leftovers"}) );
    set_long("Meat from the corpse of a snake. It is edible, and rumour "
      + "has it that it is even a delicacy for some.\n");
 
    set_decay_time(120);
    set_amount(20);
}

