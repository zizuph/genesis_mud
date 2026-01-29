/* A torch for the Union tomb area. It last quite a long time. Cirion April 18, 1997 */
inherit "/std/torch";
#include <stdproperties.h>

public void
create_torch(void)
{
    set_name("torch");
    set_short("ivory torch");
    add_adj("ivory");
    set_long("It is a smooth, beautiful torch made from ivory, wrought "+
	"with veins of silver and platinum.@@lit_desc@@\n");

    set_time(3600);
    set_strength(2);
    set_value(800);

    add_prop(OBJ_I_VOLUME, 680);
    add_prop(OBJ_I_WEIGHT, 700);
}

public string
lit_desc(void)
{
    if (!query_time())
    {
	return " The resin at the top of the torch has burned out "+
	    "completely.";
    }
    else if (!query_prop(OBJ_I_HAS_FIRE))
    {
	return " The top of the torch is coated with a sticky, "+
	    "amber-coloured resin.";
    }
    else
    {
	return " A large, rich orange flame rises from it, "+
	    "sending thick plumes of dark smoke into the air.";
    }
}
