inherit "/std/leftover";

#define BS(message)	break_string(message, 75)

void
create_leftover()
{
    set_name("midge wing");
    add_name("wing");
    set_long(BS("It the tiny wing of a midge.\n"));
    set_decay_time(120);
    set_amount(1); /* Not very nutricious! */
}

