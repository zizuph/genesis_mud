#include </stdproperties.h>

inherit "/std/arrow";

public void
create_arrow()
{
    set_adj(({"long", "black"}));
    set_short("long black arrow");
    set_pshort("long black arrows");
    
    set_projectile_id("gondor_long_black_arrow");
    set_hit(40);
    set_pen(46);
}

string
get_projectile_long(string str, object for_obj, int num)
{
    if (num == 1)
    {
	return "This is a long and rather heavy arrow suitable for longbows. "+
	    "The shaft has been dyed to a dark grey, almost blackish colour, "+
	    "and the fins are black cock feathers. The arrow head is made " +
	    "of blackened iron, hammered into a crude but efficent edge.\n";
    }
    else
    {
	return "These are long and rather heavy arrows suitable for " +
	    "longbows. Their shafts has been dyed to a dark grey, almost " +
	    "blackish colour, and their fins are black cock feathers. " +
	    "The arrow heads are made of blackened iron, that has been " +
	    "hammered into crude but efficent edges.\n";
    }
}

