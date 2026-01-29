/*
 * A shirt for the Union of the Warriors
 * of Shadow. Cirion 031696
 */
#pragma strict_types
#include "../defs.h"

inherit "/d/Avenir/inherit/cloth_arm";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#define LOC	"_Union_shirt_Subloc"


public void
create_armour()
{
    set_name("robe");
    set_short("thin white robe");
    set_adj(({"thin","white","gossamer"}));
    add_adj("union");
    add_adj("unworn");
    
    set_long("This robe is thin and translucent, almost "+
      "gossamer. It is perhaps the most comfortable "+
      "garment you will ever wear.\n"+
      "On the front is a symbol of "+
      "a black flame rising from a dark sphere.\n");

    add_prop(OBJ_I_VOLUME,  500);
    add_prop(OBJ_I_WEIGHT,  400);
    add_prop(OBJ_I_VALUE,    389);

    set_at(A_ROBE);
    set_af(TO);
    set_ac(4);
}

public int
wear(object ob)
{
    write("Ready to relax, you slide "+ LANG_THESHORT(TO) +
	" over your body and revel in the smooth, silky feel of it.\n");
    say("As "+ QTNAME(TP) +" wears "+ LANG_ASHORT(TO) +" over "+ HIS(TP) +
	" body "+ HE(TP) +" appears more comfortable and relaxed.\n");
    TP->add_subloc(LOC, TO);
    return 1;
}

public int
remove(object ob)
{
    TP->remove_subloc(LOC);
    return 0;
}

public void
leave_env(object dest, object old)
{
    ::leave_env(dest, old);
    old->remove_subloc(LOC);
}

public string
show_subloc(mixed subloc, object on, object for_obj)
{
    if (for_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || subloc != LOC)
	return "";

    if (for_obj != on)
    {
	return CAP(HIS(on)) +" "+ short() +" bears the symbol of a "+
	    "dark flame rising from a black sphere.\n";
    }
    else
    {
	return "Your "+ short() +" bears the symbol of a dark "+
	    "flame rising from a black sphere.\n";
    }
}
