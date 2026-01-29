inherit "/std/leftover";

#define BS(message)	break_string(message, 75)
#define TP 		this_player()
#define TO 		this_object()

void
create_leftover()
{
    set_name(({"leg", "grasshopper leg"}));
    set_long(BS("Compared to its size, this leg looks rather strong. You recon"+
      " that this must be the jumping leg of a grasshopper.\n"));
    set_decay_time(120);
    set_amount(1); /* Not very nutricious! */
}

