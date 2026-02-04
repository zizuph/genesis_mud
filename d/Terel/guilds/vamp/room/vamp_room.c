
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <std.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>

#include "../guild.h"

public object * Shelves;

public void clone_coffins();

public void create_vamp_room()
{
}

public void create_room()
{
    ::create_room();
    
    add_prop(ROOM_I_LIGHT,-2);
    add_prop(VAMP_FREE_SEE_DARKNESS,10);
    add_prop(ROOM_I_INSIDE,1);
    
    /*
    add_prop(ROOM_M_NO_TELEPORT,"@@block_teleport@@");
    add_prop(ROOM_M_NO_SCRY,"@@block_scry@@");
    */
    
    setuid();
    seteuid(getuid());
    create_vamp_room();
  
    // Don't clone coffins anymore. Guild is closed. Petros, February 2010  
//    clone_coffins();
}

/*
public string block_teleport()
{
    if (!interactive(TP))
    {
        return 0;
    }
    if (IS_VAMP(TP) || IS_BG(TP) || IS_WIZ(TP))
    {
        return 0;
    }
    return "Some oppressive force prevents you from leaving here "+
    "through magical means.\n";
}

public string block_scry()
{
    if (!interactive(TP))
    {
        return 0;
    }
    if (IS_VAMP(TP) || IS_BG(TP) || IS_WIZ(TP))
    {
        return 0;
    }
    return "Some oppressive force prevents you from seeing here "+
    "through magical means.\n";
}


public void enter_inv(object obj,object from)
{
    ::enter_inv(obj,from);
    int to_dark=query_prop(VAMP_FREE_SEE_DARKNESS);
    int from_dark=(from ? from->query_prop(VAMP_FREE_SEE_DARKNESS) : 0);
    if (!IS_VAMP(obj) && !IS_BG(obj) && !IS_WIZ(obj))
    {
        if (!from_dark && living(obj) && !obj->query_npc())
        {
            VAMPS(users())->catch_msg("You sense an intrusive "+
                "presence near your home.\n");
        }
        
        return;
    }
    obj->add_prop(LIVE_I_SEE_DARK,to_dark 
            + obj->query_prop(LIVE_I_SEE_DARK));
    obj->add_prop(VAMP_FREE_SEE_DARKNESS,to_dark);

    int from_light=(from ? from->query_prop(OBJ_I_LIGHT) : 0);
    int to_light=query_prop(OBJ_I_LIGHT);

    if (to_light<from_light && to_light<=0 && 
        to_light+obj->query_prop(LIVE_I_SEE_DARK)>=0)
    {        
        obj->catch_msg("Although dark, your heightened senses allow you " +
        "to see here.\n");
    }

}

public void leave_inv(object obj,object to)
{
    ::leave_inv(obj,to);
    
    int from_dark=obj->query_prop(VAMP_FREE_SEE_DARKNESS);
    int to_dark=(to ? to->query_prop(VAMP_FREE_SEE_DARKNESS) : 0);
    
    if (!IS_VAMP(obj) && !IS_BG(obj) && !IS_WIZ(obj) && !obj->query_npc())
    {
        if (!to_dark && living(obj))
        {
            VAMPS(users())->catch_msg("The intrusive "+
                "presence fades.\n");
        }
        return;
    }
    int from_light=query_prop(OBJ_I_LIGHT);
    int to_light=(to ? to->query_prop(OBJ_I_LIGHT) : 0);
    
    obj->add_prop(LIVE_I_SEE_DARK,
            obj->query_prop(LIVE_I_SEE_DARK)-from_dark);
    obj->remove_prop(VAMP_FREE_SEE_DARKNESS);

    if (from_light<to_light && from_light+obj->query_prop(OBJ_I_LIGHT)<=0)
    {        
        obj->catch_msg("As you leave this darkened place, your sense of "+
        "sight diminishes.\n");
    }

}
*/

public void set_shelves(object * ob)
{
    Shelves=ob;
}

public object * query_shelves()
{
    return Shelves;
}

int
manip_drop_access(object ob)
{
    if (!objectp(ob))
        return 0;

    if (ob->query_no_show())
        return 0;

    if (ob->query_prop(OBJ_I_NO_DROP))
    {
        return 0;
    }
    
    if (environment(ob) == TP)
        return 1;
    return 0;
}


public int do_get(string str)
{
    if (!Shelves || !sizeof(Shelves))
    {
        return 0;
    }
    if (!strlen(str))
    {
        return 0;
    }
    string itemstr;
    object * containers;

    if (!parse_command(str,Shelves,
        "%s 'in' / 'inside' / 'from' %i",
        itemstr,containers))
    {
        return 0;
    }
    containers=containers[1..];
    
    object * possible=({});
    foreach (object container : containers)
    {
        possible+=all_inventory(container);
    }
    object * items;
    items=FIND_STR_IN_ARR(itemstr,possible);
    if (!sizeof(items))
    {
        return 0;
    }
    for (int i=sizeof(containers)-1;i>=0;i--)
    {
        object shelf=containers[i];
        object * to_move=items & all_inventory(shelf);
        object * moved=({ });
        
        foreach (object ob : to_move)
        {
            int result=ob->move(TP);
            if (!result)
            {
                moved+=({ ob });
            }
            else
            {
                CMD_LIVE_THINGS->move_err_short(result,ob,TP);
            }
        }
        if (sizeof(moved))
        {
            moved->remove_prop(OBJ_I_HIDE);
            write("You "+query_verb()+" "+COMPOSITE_DEAD(moved) +
                " from the "+shelf->short()+".\n");
            WATCHERS(TP)->catch_msg(QCTNAME(TP)+" "+query_verb()+"s "+
            COMPOSITE_DEAD(moved)+" from the "+shelf->short()+".\n");
            moved->force_heap_merge();
        }
        items-=moved;
    }
    return 1;       
}


public int do_put(string str)
{
    if (!Shelves || !sizeof(Shelves))
    {
        return 0;
    }

    if (!strlen(str))
    {
        return 0;
    }
    
    string itemstr;
    object * containers;

    if (!parse_command(str,Shelves,
        "%s 'on' / 'in' / 'into' / 'inside' / 'onto' %i",
        itemstr,containers))
    {
        return 0;
    }
    containers=containers[1..];
    object * items;
    items=FIND_STR_IN_ARR(itemstr,
        filter(all_inventory(TP),manip_drop_access));
    if (!sizeof(items))
    {
        return 0;
    }
    foreach (object shelf : containers)
    {
        object * moved=filter(items,&operator(==) (0) @
        &->move(shelf));
        string onto=shelf->query_prop(CONT_I_ATTACH) ? "onto" : "into";
        if (sizeof(moved))
        {
            moved->remove_prop(OBJ_I_HIDE);
            write("You "+query_verb()+" "+COMPOSITE_DEAD(moved) +
                " "+onto+" the "+shelf->short()+".\n");
            WATCHERS(TP)->catch_msg(QCTNAME(TP)+" "+query_verb()+"s "+
            COMPOSITE_DEAD(moved)+" "+onto+" the "+shelf->short()+".\n");
            moved->force_heap_merge();
        }
        items-=moved;
    }
    if (sizeof(items))
    {
        write(capitalize(COMPOSITE_DEAD(items))+" could not be "+
        query_verb()+" there.\n");
    }
    return 1;    
}

public int do_list(string str)
{
    if (!Shelves || !sizeof(Shelves))
    {
        return 0;
    }
    
    notify_fail("List what?\n");
    
    if (!strlen(str))
    {
        str="all";
    }
    
    object * possible=({});
    foreach (object container : Shelves)
    {
        possible+=all_inventory(container);
    }
    if (!sizeof(possible))
    {
        string on=Shelves[0]->query_prop(CONT_I_ATTACH) ? "on" : "in";
        write("There is nothing "+on+" the "+
        Shelves[0]->query_pname()+".\n");
        return 1;
    }
    object * items;
    items=FIND_STR_IN_ARR(str,possible);
    if (!sizeof(items))
    {
        return 0;
    }
    foreach (object shelf : Shelves)
    {
        object * match=items & all_inventory(shelf);
        if (sizeof(match))
        {
            write(sprintf("%-10s\n%'='-20s\n\n",
                capitalize(shelf->short()),""));
            foreach(object item : match)
            {
                write(sprintf("%1s%1s %s\n",
                    (item->check_recoverable() ? "*" : ""),
                    (sizeof(all_inventory(item)) ? "+" : ""),
                    item->short()));
            }
            write("\n");
        }
        items-=match;
    }
    write("---------------------------------------\n");
    write("* = This item appears to last a while.\n");
    write("+ = This container has items inside.\n");
    write("---------------------------------------\n");
    return 1;
}


public void remove_object()
{
    if (Shelves && sizeof(Shelves))
    {
        foreach (object shelf : Shelves)
        {
            if (!shelf)
            {
                continue;
            }
            if (sizeof(all_inventory(shelf)))
            {
                throw(capitalize(LANG_THESHORT(shelf))+
                    " has items on it.\n");
            }
        }
    }
    ::remove_object();
}

public void clone_coffins()
{
    
    if (!query_prop(VAMP_CAN_START_HERE))
    {
        return;
    }

    string * coffins=COFFIN_MANAGER->query_all_coffins();
    
    coffins=filter(coffins,&operator (==) (file_name(TO),)
      @ &COFFIN_MANAGER->query_location());
      
    foreach (string owner : coffins)
    {
        object coffin=clone_object(ROOM_DIR+"coffin");
        coffin->load_coffin(owner);
        coffin->move(TO);
    }  
    
}