inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

#define CLEANING_NOW "_cleaning_now"

/* 
 * /d/Kalad/common/guilds/khiraa/temple/rooms/herb_store.c
 * Purpose    : store room for herbs
 * Located    : Khiraa temple
 * Created By : Sarr 10.Apr.97
 * Modified By: 
 */


void
create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE,1);
    set_short("Store room");
    set_long("\n   The herb store room.\n\n");
    add_exit(KHIRAA_DIR(temple/rooms/temple_study),"south",0,-1,-1);
}

void
enter_inv(object ob, object from)
{
    string fname;
    int qty;
    mapping herb_list,lo_list;
    ::enter_inv(ob,from);
    if( stringp(ob->query_potion_name()) )
    {
        ob->add_name(ob->query_potion_name());
        if(ob->query_prop("just_sold_herb"))
        {
            lo_list = restore_map(KHIRAA_DIR(log/potion_master));
            if(!m_sizeof(lo_list))
                lo_list = ([]);
            fname = MASTER_OB(ob);
            qty = lo_list[fname];
            qty += 1;
            lo_list += ([fname:qty]);
            save_map(lo_list,KHIRAA_DIR(log/potion_master));
        }
        if(!query_prop(CLEANING_NOW))
        {
            add_prop(CLEANING_NOW,1);
            set_alarm(0.5,0.0,"clean_up_herbs");
        }
    }
    if( stringp(ob->query_herb_name()) )
    {
        ob->add_name(ob->query_herb_name());
        if(ob->query_prop("just_sold_herb"))
        {
            herb_list = restore_map(KHIRAA_DIR(log/herb_master));
            if(!m_sizeof(herb_list))
                herb_list = ([]);
            fname = MASTER_OB(ob);
            qty = herb_list[fname];
            qty += 1;
            herb_list += ([fname:qty]);
            save_map(herb_list,KHIRAA_DIR(log/herb_master));
        }
        if(!query_prop(CLEANING_NOW))
        {
            add_prop(CLEANING_NOW,1);
            set_alarm(0.5,0.0,"clean_up_herbs");
        }
    }
}

void
leave_inv(object ob,object to)
{
    ::leave_inv(ob,to);
    if(stringp(ob->query_herb_name()))
        ob->remove_name(ob->query_herb_name());
}

void
clean_up_herbs()
{
    int i;
    object *obs;
    obs = all_inventory();
    for(i=0;i<sizeof(obs);i++)
    {
        if(obs[i]->query_herb_name())
            obs[i]->remove_object();
        if(obs[i]->query_potion_name())
            obs[i]->remove_object();
    }
    remove_prop(CLEANING_NOW);
}

