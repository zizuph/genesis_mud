//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
inherit "/std/container";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>

string direction="";

/*
 * Function name: torches
 * Description:   checks if item in inventory is a torch
 */
private object
*torches()
{
    return filter(all_inventory(TO), &->id("torch"));
}


/*
 * Function name: my_torch
 * Description:   checks if torch is lit
 */
public object
my_torch()
{
    object *mine = torches(), *lit;

    if(!sizeof(mine))
       return 0;

    lit = filter(mine, &->query_prop(OBJ_I_HAS_FIRE));

    if(sizeof(lit))
       return lit[0];
    else
       return mine[0];    
}

public int has_torch()
{
    if (my_torch())
    {
        return 1;
    }
    return 0;
}

/*
 * Function name: torch_msg
 * Description:   gives message for torches lighting up
 */
public void
torch_msg()
{
    if(!my_torch())
        return;

    tell_room(ENV(TO), capitalize(LANG_ASHORT(my_torch())) +
        " flares to life in " + LANG_THESHORT(TO) + 
        " with a crackling whoosh.\n");
    all_inventory(ENV(TO))->hook_torches_lit();    
}

/*
 * Function name: prevent_enter
 * Description:   only torches allowed, make them burn longer
 */
public int
prevent_enter(object ob)
{
    if (!ob->id("torch"))
    {
        write("It does not fit there.\n");
        return 1;
    }

    if (present("torch",TO))
    {
        write("There is already a torch present.\n");
        return 1;
    }
   
    ob->set_time(ob->query_time() * 10);
    ob->set_time_left(ob->query_time());
    ob->light_me();
    set_alarm(0.0,0.0,torch_msg);
    
    return 0;
}        
  
/*
 * Function name: prevent_leave
 * Description:   resets torch time left to appropriate level
 */      
public int
prevent_leave(object ob)
{
 
    ob->set_time(ob->query_time() / 10);
    ob->set_time_left(ob->query_time());
    return 0;
}


public void
reset_container()
{
    object torch;

    if(!my_torch())
    {
       if(ENV(TO))
          all_inventory(TO)->move(ENV(TO));

       seteuid(getuid());
       torch = clone_object("/std/torch");
       torch->set_time(5000);
       torch->set_long("This ia a torch.\n");
       torch->light_me();
       torch->move(TO);

    }
}

public void hook_torch_burned_out(object torch)
{
    tell_room(environment(TO),"The flames in the "+short()+ " flicker "+
        "briefly and die.\n",({ }),0);
}



/*
 * Function name: external_desc
 * Description:   called by external items
 */

string
external_desc()
{
    object torch = my_torch();
    string str;

    str = "A tall, heavy wrought-iron sconce standing in the " +
    (strlen(direction) ? direction +" " : "") + "corner";

    if(torch && torch->query_lit())
      str += ". The flames of " + LANG_ASHORT(torch) + " whose handle " +
        "has been thrust unto it dance, casting shadows along the "+
        "walls";

    return str + ".\n";
}

void set_direction(string dir)
{
    direction=dir;
    add_adj(direction);
}

string my_short()
{
    return 
    (strlen(direction) ? direction + " " : "") + "wrought-iron sconce";
}

nomask void
create_container()
{
    if(!IS_CLONE)
        return;

    set_name("sconce");
    set_short("@@my_short");
    add_name(({"stand","torchstand", "iron", "torchiere"}));
    set_adj(({"wrought", "wrought-iron", "torch", "iron", "tall", "heavy", "ornate"}));
    set_long(external_desc);

    add_prop(OBJ_M_NO_GET, "It is firmly secured to the floor.\n");

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

/*
 * Function name:
 * Description:
 */
