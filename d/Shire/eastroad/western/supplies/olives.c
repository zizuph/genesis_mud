/* baked goods.--Raymundo, dec 2018
 */
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/eastroad/western/local.h"
inherit "/std/food";


void
create_food()
{
        set_name("olives");
        add_name("olive");
        add_name("toothpick");
        add_name("food");
        set_pname("toothpicks of olives");
        add_adj("toothpick");
        add_adj("of");
        add_adj("three");
        add_adj("3");
        add_adj("with");
        add_adj("on");
        add_adj("it");
        
        
        
        set_short("olives on a toothpick");

        
        set_long("These are three olives skewered through the center "
            + "with a toothpick. They smell like gin and vermouth, "
            + "probably because you got them from a martini.\n");
            
        set_amount(10);
        add_prop(OBJ_I_WEIGHT, 100);
        add_prop(OBJ_I_VOLUME, 100);
        add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    ::init();
    add_action("smell_olives", "smell");
}

int
smell_olives(string str)
{
    if(str == "olives" | str == "olive" | str == "toothpick")
    {
        write("You smell the olives. They smell like gin and vermouth, "
            + "which in turn smells like a good idea.\n");
        say(QCTNAME(TP) + " smells the " + query_short() + ".\n");
    return 1;
    }
    else
    {
        return 0;
    }
}
public void
special_effect(int amount)
{
        setuid();
        seteuid(getuid());

    write("You pinch the toothpick between your index finger and thumb "
		+ "so as not to eat it along with your olives.\n");
    tell_room(environment(TP), QCTNAME(TP) + " pinches the toothpick between " 
        + HIS_HER(TP) + " finger and thumb so as not to eat it along with the "
		+ "olives.\n",
        TP);
    object toothpick;
    toothpick = clone_object(EAST_R_DIR + "supplies/toothpick.c");
    toothpick->move(TP);
}