
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define CLEANING_NOW "_cleaning_now"

void
create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE,1);
    set_short("Store room");
    set_long("\n   The gem store room.\n\n");
}

void
enter_inv(object ob, object from)
{
    string fname;
    int qty;
    mapping lo_list;
    ::enter_inv(ob,from);
    if( stringp(ob->query_gem_name()) )
    {
        ob->add_name(ob->query_gem_name());
        if(ob->query_prop("just_sold_gem"))
        {
            lo_list = restore_map(SPIRIT_OBJECTS+"gemlist");
            if(!m_sizeof(lo_list))
                lo_list = ([]);
            fname = MASTER_OB(ob);
            qty = lo_list[fname];
            qty += num_heap(ob);
            lo_list += ([fname:qty]);
            save_map(lo_list,SPIRIT_OBJECTS+"gemlist");
        }
        if(!query_prop(CLEANING_NOW))
        {
            add_prop(CLEANING_NOW,1);
            set_alarm(0.5,0.0,"clean_up_gems");
        }
    }
}

void
leave_inv(object ob,object to)
{
    ::leave_inv(ob,to);
/*    if(stringp(ob->query_gem_name()))
        ob->remove_name(ob->query_gem_name());
*/
}

void
clean_up_gems()
{
    int i;
    object *obs;
    obs = all_inventory();
    for(i=0;i<sizeof(obs);i++)
    {
        if(obs[i]->query_gem_name())
            obs[i]->remove_object();
    }
    remove_prop(CLEANING_NOW);
}

