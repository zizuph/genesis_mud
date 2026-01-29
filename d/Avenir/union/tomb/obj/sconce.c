inherit "/std/container";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h"

#define TORCHFILE	(TOBJ + "ivory_torch")


private object *
torches(void)
{
    return filter(all_inventory(), &->id("torch"));
}

public object
my_torch(void)
{
    object *mine = torches(), *lit;

    if (!sizeof(mine))
	return 0;

    lit = filter(mine, &->query_prop(OBJ_I_HAS_FIRE));

    if (sizeof(lit))
	return lit[0];
    else
	return mine[0];
}

public void
torch_msg(void)
{
    object torch = my_torch();

    if (!torch) return;
    tell_room(ENV(TO), CAP(LANG_ASHORT(torch)) +
	" flares to life in "+ LANG_THESHORT(TO) +".\n");
}

public void
reset_container(void)
{
    object torch = my_torch();

    if (objectp(torch))
	return;

    if (ENV(TO))
	all_inventory(TO)->move(ENV(TO));

    torch = clone_object(TORCHFILE);
    torch->light_me();
    torch->move(TO, 1); 

    set_alarm(1.0, 0.0, torch_msg);
}

public nomask void
create_container()
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name("sconce");
    set_short("wrought-iron sconce");
    add_name(({"stand","bracket", "torchstand", "iron", "wrought",
	    "wrought-iron"}));
    set_adj(({"torch", "iron"}));
    set_long("It is an intricate sconce, made from wrought iron "+
	"formed in weaving designs. ");

    add_prop(OBJ_M_NO_GET, "It is firmly secured to the wall.\n");

    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 11000);
    add_prop(CONT_I_MAX_VOLUME, 11000);

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,  1);

    set_no_show_composite(1);
    reset_container();
}

public string
external_desc(void)
{
    object torch = my_torch();
    string str = " Fastened to the wall is a large, intricate iron sconce";

    if (torch)
	str += ", within which "+ LANG_ASHORT(torch) +" flickers and burns";

    return str + ".";
}
