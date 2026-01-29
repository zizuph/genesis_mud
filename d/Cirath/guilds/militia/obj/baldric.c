inherit "/std/clothing.c";
inherit "/lib/wearable_item.c";
#include "../defs.h"
#include <wa_types.h>
#include <clothing.h>


#pragma strict_types
#pragma save_binary

int worn;
object contslot;


public void
create_clothing()
{
    set_bulk(1);
    set_elasticity(10);
    set_location(CLOTHING_CHEST);
    set_name("baldric");
    add_name("_militia_baldric_");

    set_adj("leather");
     set_pshort("leather baldrics");
    set_short("leather baldric");
    set_long("This long piece of hardened leather has been "
       +"designed to be worn across the chest.  The leather has "
       +"been stained a deep red with some form of dye to "
       +"identify you to both Tyr and her enemies as a member "
       +"of the Tyrian Militia.  Members can use <help baldric> for "
      +"more information about the guild.\n");

    add_prop(OBJ_M_NO_DROP, "You don't think that would be a good idea.\n");
       add_prop(CONT_I_WEIGHT,500);
      add_prop(CONT_I_VOLUME,20);
      add_prop(CONT_I_MAX_WEIGHT,1500);
      add_prop(CONT_I_MAX_VOLUME,400);
}


void
init()
{
    ::init();
    add_action("do_help","help");
}

int
do_help(string str)
{
    if(str != "baldric")
        return 0;
    write("Members can use <mhelp> to see a list of their commands.\n");
    return 1;
}

public mixed
wear_me()
{
    contslot->move(TP);
    contslot->add_prop(OBJ_I_NO_DROP,1);
        TP->add_subloc("leather baldric",TO,"on chest");
    return ::wear_me();
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != "leather baldric")
        return "";
    if(on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if (for_obj != on)
      return capitalize(on->query_pronoun()) + " is wearing the "
          +"leather baldric across "+ HIS_HER(on) +" chest.\n";
     else
        return "You are wearing the "+short()+" across your chest.\n";
}

public mixed
remove_me()
{
    TP->remove_subloc("leather baldric");
    return ::remove_me();
}

void enter_env(object env, object from)
{
    ::enter_env(env, from);
    if(!IS_TYR_MILITIA(env))
        remove_object();
}
int
query_recover()
{
    return 0;
}



public string
query_auto_load()
{
    setuid();
    seteuid(getuid());
    return MASTER + ":";
}

