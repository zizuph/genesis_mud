inherit "/std/object";

/*
 * A stupid rose
 * Jorl and Cedric,  3/93
 */
void 
create_object()
{
    set_name("rose");
    add_adj("beautiful");
    set_short("beautiful rose");
    set_long("\n--<--<{@	With love from Jorl and Cedric!\n"
	     + "\t\t\t(So smell it, already)\n");
}

void
init()
{
    add_action("do_smell", "smell");
}

int
do_smell(string str)
{
    if (str == "rose" || str == "beautiful rose")
    {
	write("The subtle perfume of this most sublime of flowers brings "
	      + "visions upon you, seeming "
	      + "to open up an entirely new world. Or perhaps "
	      + "it is merely remembrance of this world, a time not so "
	      + "long past...reality shifts and quivers around you, images "
	      + "fleet by with blurring speed, and suddenly the world seems "
	      + "once again to coalesce....you stand in a place of solemnity "
	      + "and austere discipline, a dark hall that houses the wizards "
	      + "of Terel. Before you stands the youngest of these wizards, "
	      + "a dark-eyed swarthy gnome, who kneels and murmurs, "
	      + "'My liege...' \n\nAbruptly the spell fades and you find "
	      + "yourself staring foolishly into a rose, while others look "
	      + "on in wonderment.\n");
	return 1;
    }
    else
	return 0;
}
