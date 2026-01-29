/*
 * This is grasshopper meat. It is good food.
 */

inherit "/std/leftover";

#define BS(message)	break_string(message, 75)
#define TP 		this_player()
#define TO 		this_object()

void
create_leftover()
{
    set_name(({"meat", "grasshopper meat"}));
    set_long("A tiny chunk of grasshopper meat. You might even try eating it.\n");
    set_decay_time(30);
    set_amount(50);
}

