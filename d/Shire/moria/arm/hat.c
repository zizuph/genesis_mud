inherit "/std/armour";
#include "defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
    set_name("hat");
    add_name("_funny_hat_");
    set_adj( ({ "funny", "strange" }) );
    set_short("strange funny-looking hat");
    set_long(
	"This is a strange funny-looking hat. It really looks funny, "+
	"in fact, you must laugh when you see it. You probably would "+
	"look even funnier if you wore it.\n");
    set_ac(3);
    set_am(0);
    set_at(A_HEAD);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 140);
    add_prop(OBJ_I_VALUE,    2);
}

wear(object to)
{
    ENV(to)->add_subloc("_funny_hat_look", this_object());
}

remove(object to)
{
    ENV(to)->remove_subloc("_funny_hat_look");
}

string
show_subloc(mixed subloc, object on, object who)
{
    if(subloc!="_funny_hat_look")
	return "";
    if(who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if(!query_worn())
	return "";
    if(who==ETO)
	return "You look quite funny wearing that strange hat!!\n";
    else
	return CHE_SHE(ETO)+" looks quite funny wearing that hat!!\n";
}
