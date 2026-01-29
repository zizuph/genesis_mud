inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

mixed wield(object ob)
{
    object ob2 = present("invis_glove", environment(ob));
    if (ob2 && ob2->query_worn())
    {
	write("With the help of your glove, you can feel the hilt of the sword.\n");
	return 0;
    }
    return "Apparently you can't wield this weapon.\n";
}

void create_weapon()
{
    set_name(({"intang_sword", "sword"}));
    set_adj("unhilted");
    set_short("sword with no hilt");
    set_long("This sword is extremely well-crafted, but it has no hilt!\n");
    set_hit(50);
    set_pen(50);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_wf(this_object());
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
}
