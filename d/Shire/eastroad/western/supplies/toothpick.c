/* 
*  A toothpick
*  
*  Raymundo, 2019
*/
#include "/d/Shire/common/defs.h"
#include "/d/Shire/eastroad/western/local.h"
#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>

inherit "/std/object";
inherit "/lib/commands.c";

# define SEARCHED "_i_searched_the_toothpick"

public void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("toothpick");
    add_name("skewer");
    set_adj("wooden");
    set_adj("small");
    set_short("small wooden toothpick");
    set_long("This is a " + query_short() + ". It looks like the kind of "
       +  "thing you'd use to put olives on if you wanted to have them in "
       +  "your martini.\n");
   add_item( ({"scratch", "scratches"}), "@@see_scratches@@");
       
    add_prop(OBJ_S_SEARCH_FUN, "search_toothpick");
    
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    ::init();
    add_action("pick_teeth", "pick");
    add_action("flick_toothpick", "flick");
    add_action("chew_toothpick", "chew");
    add_action("discard_toothpick", "discard");
    add_action("help_toothpick", "help");
}

mixed
search_toothpick(object searcher, string str)
{
    
    if(str=="toothpick" | str == "tooth pick")
    {
        TP->add_prop(SEARCHED, 1);
        return("You see some scratches on the toothpick.\n");
    }
}

string
see_scratches()
{
    if(TP->query_prop(SEARCHED))
    {
        return("The scratches are actually tiny words! They say:\n"
        + "help toothpick\n");
    }
    else
    {
        return("You see no scratches.\n");
    }
}

string
help_string()
{
    return(""
        + "+-----------------------+\n"
        + "|       TOOTHPICK       |\n"
        + "| ********************* |\n"
        + "| You can:              |\n"
        + "|   chew                |\n"
        + "|   flick (at a person) |\n"
        + "|   pick your teeth     |\n"
        + "|   or discard          |\n"
        + "| your toothpick        |\n"
        + "+-----------------------+\n\n");
}

int
help_toothpick(string str)
{
    if(TP->query_prop(SEARCHED))
    {
    if(str == "toothpick" | str == "tooth pick")
    {
        write(help_string());
        return 1;
    }
     else
     {
        return 0;
     }         
    }
    else
    {
        return 0;
    }
}




int
pick_teeth(string str)
{
    if(str == "teeth" | str == "tooth" | str == "teeth with toothpick" |
        str == "tooth with toothpick")
    {
        write("You pick your teeth with the " + query_short() + ".\n");
        say(QCTNAME(TP) + " picks " + HIS_HER(TP) + " teeth with the "
            + query_short() + ".\n");
        return 1;
    }
    else
    {
        notify_fail("Pick what? Your teeth?\n");
        return 0;
    }
}

//Let's you flick the toothpick, because that's what people do.
int
flick_toothpick(string str)
{
    object toothpick;
    object* targ;
           
    if(!strlen(str))   
    {
        notify_fail("Flick what? Your toothpick? At somebody?\n");
        return 0;
    }
    else if(str == "toothpick" | str == "tooth pick")
    {
        write("You flick your " + query_short() + " onto the ground.\n");
        say(QCTNAME(TP) + " flicks " + HIS_HER(TP) + " toothpick onto the "
            + "ground.\n");
        TO->move(environment(TP));
        return 1;
  
    }
    targ = parse_this(str, " [the] [small] [wooden] 'toothpick' [at] [the] %l");
    if(!sizeof(targ))
    {
        notify_fail("Flick your " + query_short() + " at whom?\n");
        return 0;
    }
    else
    {
        
        actor("You flick your " + query_short() + " at",targ,".");
        all2actbb(" flicks " + HIS_HER(TP) + " " + query_short()
            + " at",targ,".");
        targetbb(" flicks " + HIS_HER(TP) + " " + query_short()
            + " at you.",targ);
        TO->move(targ[0]);
    
        return 1;
    }
 
    
}
    
int
chew_toothpick(string str)
{
    if(str == "toothpick" | str == "tooth pick")
    {
        write("You chew your " + query_short() + ".\n");
        say(QCTNAME(TP) + " chews " + HIS_HER(TP) + " " + query_short()
            + ".\n");
            return 1;
    }
    else
    {
        notify_fail("Chew what? Your toothpick?\n");
        return 0;
    }
}
int
discard_toothpick(string str)
{
    if(str == "toothpick" | str == "tooth pick")
    {
        write("You break the " + query_short() + " into little pieces and "
            + "toss it away.\n");
        say(QCTNAME(TP) + " breaks the " + query_short() + " into little pieces and "
            + "throws it away.\n");
        TO->remove_object();
        return 1;
    }
    else
    {
        notify_fail("Huh?\n");
        return 0;
    }
    
}
