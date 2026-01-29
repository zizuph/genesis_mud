inherit "/std/shadow";

#include <stdproperties.h>

object gSheath;

public void set_sheath_object(object ob) { gSheath = ob; }

public void
unstrap_shield()
{
    shadow_who->set_no_show_composite(0);
    shadow_who->remove_prop(OBJ_M_NO_DROP);
    remove_shadow();
}

public object 
query_sheath_object() 
{ 
    if (!objectp(gSheath))
    {
	unstrap_shield();
        return 0;
    }

    if (shadow_who->query_worn())
    {
        unstrap_shield();
        return 0;
    }

    if (environment(shadow_who) != environment(gSheath))
    {
	unstrap_shield();
	return 0;
    }

    return gSheath; 
}

void leave_env(object from, object to)
{
    shadow_who->leave_env(from, to);

    from->catch_tell("You unstrap your "+shadow_who->short()+
        " from your back.\n");
    return unstrap_shield();
}
