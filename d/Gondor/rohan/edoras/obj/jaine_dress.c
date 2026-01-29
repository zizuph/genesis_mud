inherit "/std/armour";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Gondor/defs.h"

int is_buttoned = 1;

create_armour()
{
    set_name("dress");
    add_name("gown");
    add_name("armour");
    set_adj("silk");
    add_adj("black");
    set_short("black silk gown");
    set_long("This is a long black gown. It's made of silk and embroidered "
        + "with white flowers. It stretches from the neck all the way "
        + "down to the ankles. " + "@@do_button@@" + ".\n");
    set_default_armour(15,(A_TORSO | A_LEGS), (({ -2, 1, 1})), 0);	    
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 5000); 
    add_prop(OBJ_I_VALUE, 1728);
}  

string
do_button()
{
    if(is_buttoned == 1)
    {
        return("The gown is buttoned tight, covering your neck for warmth");
    }
    else
    {
        return("The gown is unbuttoned, open at the neck");
    }
}

void
init()
{
    ::init();
    add_action("button_it", "button");
    add_action("unbutton_it", "unbutton");
}

int
button_it(string str)
{
    if(is_buttoned == 1)
    {
        notify_fail("But the gown is already buttoned up tight.\n");
        return 0;
    }
    if(str == "dress" | str == "gown" | str == "buttons")
    {
        write("You button the gown up tight around the neck.\n");
        say(QCTNAME(TP) + " buttons the gown up tight around the "
            + "neck.\n");
        is_buttoned = 1;
        return 1;
    }
    else
    {
        notify_fail("Button what? The dress?\n");
        return 0;
    }
}

int
unbutton_it(string str)
{
    if(is_buttoned == 0)
    {
        notify_fail("But the gown is already unbuttoned.\n");
        return 0;
    }
    if(str == "dress" | str == "gown" | str == "buttons")
    {
        write("You unbutton the gown, letting more air circulate around "
            + "your neck.\n");
        say(QCTNAME(TP) + " unbuttons " + HIS_HER(TP) + " gown, letting "
            + "more air circulate around " + HIS_HER(TP) + " neck.\n");
        is_buttoned = 0;
        return 1;
    }
    else
    {
        notify_fail("Unbutton what? The dress?\n");
        return 0;
    }
}
