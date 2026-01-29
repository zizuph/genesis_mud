/* Alcoholic Beverage--Raymundo, dec 2018
 */
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/eastroad/western/local.h"
inherit "/std/drink";
#define NO_OLIVE "_i_have_no_olive"
#define DRINK EAST_R_DIR + "supplies/martini.c"
void
create_drink()
{
        set_name("martini");
        
        
        set_short("martini");
        set_pshort("martinis");
        set_adj("gin");
        set_long("This is a martini. Made of gin and vermouth, it smells "
            + "like juniper "
            + "berries and other botanicals. It is in a glass that looks "
            + "like a small cone upside down on an elegant glass stand. "
            + "The martini is ice cold, so cold that condensation forms "
            + "on the outside of the glass. " + "@@is_olive@@" + "\n");
            
        add_item( ({"toothpick", "olive", "olives"}), "@@is_toothpick@@");
            
        add_item( ({"condensation"}), "Little drops of icy water form on the "
            + "outside of the glass.\n");
            
        add_cmd_item( ({"martini"}), ({"smell"}), "As you smell the martini "
            + "you get aromas of juniper berries and assorted botanicals. It "
            + "is slightly medicinal, but also very appealing.\n");
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,200);
}

string
is_olive()
{
    if(TO->query_prop(NO_OLIVE))
    {
        return ("");
    }
    else
    {
        return( "There are three olives on a "
            + "small wooden toothpick inside the glass.");
    }
}

string
is_toothpick()
{
    if(TO->query_prop(NO_OLIVE))
    {
        return("You see no olives.\n");
    }
    else
    {
        return("The olives are speared "
            + "together with a small toothpick. Looking closely, you realize "
            + "that the toothpick was hand carved! Such attention to detail! "
            + "You're quite confident that you will eat the olives when you drink "
            + "the martini, because that would taste amazing.\n");
    }
}
    

void
special_effect(object eff)
{
    write("Oh yes, that's the stuff. Cold. Refreshing. Classy. You "
        + "feel sophisticated.\n");
    say(QCTNAME(TP) + " looks classy as " + HE_SHE(TP) + " drinks the "
        + query_short() + ".\n");
    
  
}

void
init()
{
    ::init();
    add_action("get_olive", "get");
    add_action("get_olive", "pick");
    add_action("get_olive", "take");
    add_action("get_olive", "retrieve");
}

int
get_olive(string str)
{
    if(str == "olive from martini" | str == "olives from martini" |
        str == "toothpick from martini")
    {
        setuid();
        seteuid(getuid());
        TO->add_prop(NO_OLIVE, 1);
        object olive;
        olive = clone_object(EAST_R_DIR + "supplies/olives.c");
        olive->move(TP);
        write("You pick the " + olive->query_short() + " out of the martini.\n");
        say(QCTNAME(TP) + " picks the " + olive->query_short() + " from the martini.\n");
            return 1;
    }
    else
    {
        return 0;
    }
}
    
    
 