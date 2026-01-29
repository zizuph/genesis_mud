inherit "/d/Kalad/room_std";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#pragma strict_types
#pragma save_binary

#define NUMM sizeof(MONEY_TYPES)
#define KALAD_FANG_WOLF_ID "_kalad_fang_wolf_id_"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("The Stables of the Red Fang");

    set_long("\n   You are now in a smelly room. All around you, there "+
    "are cages with wolves in them. There is a sign on one wall. "+
    "Piles of dirt and old bones lay scattered on the ground.\n\n");
    add_item("bones","They are human bones.\n");
    add_item("dirt","Actually, it looks like dirt mixed with wolf "+
    "dung.\n");
    add_item("cages","They are iron cages with mean looking "+
    "wolves in them.\n");
    add_item("sign","The sign has readable words on it.\n");
    add_cmd_item("sign","read","@@wolf_sign@@");
    INSIDE;
    add_exit(FANG_DIR(rooms/train),"northeast",0,-1);
    config_default_trade();
}

string
wolf_sign()
{
    return
    "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n"+
    "|  Here you can buy wolves that will always be  |\n"+
    "|  here when you come back. They cost a mere 5  |\n"+
    "|  platinum coins. You can also select your own |\n"+
    "|  description for them from the list here. You |\n"+
    "|  can always suggest more with the 'idea'      |\n"+
    "|  command. You can do the following:           |\n"+
    "|  buy (adj1) (adj2) wolf  - For 2 adj wolf, or |\n"+
    "|  buy (adj1) only wolf    - For 1 adj wolf     |\n"+
    "|  fetch wolf from stables                      |\n"+
    "|  send wolf back to stables                    |\n"+
    "|  list adjectives                              |\n"+
    "|                                               |\n"+
    "|  When you send a wolf back, then fetch it him |\n"+
    "|  again, he will be fully rested and feed.     |\n"+
    "|  If you buy another one, your old one will be |\n"+
    "|  replaced by the new one.                     |\n"+
    "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n";
}

void
init()
{
   ::init();
   AA(do_list,list);
   AA(do_fetch,fetch);
   AA(do_send,send);
   AA(do_buy,buy);
}

int
do_send(string str)
{
    string fname;
    object wolf;
    NF("Send what back to stables?\n");

    if(!parse_command(str,E(TP),"%o 'back' 'to' 'stables'",wolf))
        return 0;
    if(!objectp(wolf))
        return 0;
    NF("You can't send that in the stables!\n");
    if(MASTER_OB(wolf) != "/d/Kalad/common/guilds/red_fang/obj/wolf")
        return 0;
    NF("You must dismount your wolf first!\n");
    if(wolf->query_occupied() == TP)
        return 0;
    NF("That is not your wolf.\n");
    if(wolf->query_owner() != TP->query_real_name())
        return 0;
    tell_room(TO,"The wolf keeper opens a cage.\n");
    write("Your "+wolf->short()+" hops into the cage.\n");
    say(QCTNAME(TP)+"'s "+wolf->short()+" hops into the cage.\n");
    remove_prop(KALAD_FANG_WOLF_ID+fname);
    wolf->save_wolf(TP);
    wolf->remove_object();
    return 1;
}


int
do_fetch(string str)
{
    string fname;
    object nwolf,me;
    int my_co, i;
    NF("Fetch what?\n");
    if(str != "wolf from stables")
        return 0;
    me = TP;
    fname = TP->query_real_name();
    if(query_prop(KALAD_FANG_WOLF_ID+fname))
        nwolf = find_object(query_prop(KALAD_FANG_WOLF_ID+fname));
    NF("Your wolf is already out in the world!\n");
    if(objectp(nwolf))
        return 0;
    NF("You don't have a wolf stabled here!\n");
    my_co = TP->query_stat(SS_CON);
    nwolf = clone_object(FANG_DIR(obj/wolf));

    nwolf->set_base_stat(SS_CON,(my_co+50)); 
    nwolf->refresh_mobile();
    nwolf->eat_food(-nwolf->query_stuffed());
    for(i=0; i<5;i++)
        nwolf->eat_food(nwolf->query_prop(LIVE_I_MAX_EAT) / 5);
    if(!(nwolf->configure_wolf(me)) )
        return 0;

    tell_room(TO,"The wolf keeper opens one of the cages.\n");

    tell_object(me,"Your "+nwolf->short()+" hops out of the stables.\n");
    nwolf->move_living("M",TO);
    tell_room(TO,QCTNAME(me)+"'s "+nwolf->short()+" hops out the stables.\n",me);
    add_prop(KALAD_FANG_WOLF_ID+fname,file_name(nwolf));
    return 1;
}
 
int
do_list(string str)
{
    string fname;
    NF("List what?\n");
    if(str != "adjectives")
        return 0;
    seteuid(getuid());
    fname = read_file(FANG_DIR(doc/ADJLIST));
    TP->more(fname,0);
    return 1;
}

int
do_buy(string str)
{
    string what, for_c, get_c, change, adj1, adj2, fname;
    int *result, m_res, price, fcon;
    object wolf;
    NF("Buy what? A wolf?\n");
    if(!str)
        return 0;
    NF("Buy what kind of wolf?\n");
    if(sscanf(str,"%s %s wolf",adj1,adj2) != 2)
        return 0;
    NF("The adjective "+adj1+" is not available.\n");
    if(member_array(adj1,MASTER_WOLF_ADJ_LIST) == -1)
        return 0;
    NF("The adjective "+adj2+" is not available.\n");
    if(member_array(adj2,MASTER_WOLF_ADJ_LIST) == -1)
        return 0;
    fname = TP->query_real_name();
    fcon = TP->query_stat(2) + 50;
        
    price= 8640; /* 5 platinums */
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1) 
       return 0;    
    write("You pay the wolf trainer " + text(result[0 .. NUMM - 1]) + ".\n");
    if (change)
       write("He gives you " + change + " as change.\n");
    wolf = clone_object(FANG_DIR(obj/wolf));
    wolf->set_owner(TP);

    if(adj2 == "only")
        wolf->set_wolf_desc(adj1);
    else
        wolf->set_wolf_desc(adj1,adj2);
    wolf->set_base_stat(SS_CON,fcon);
    wolf->save_wolf();
    wolf->move_living("M",TO);

    write("The wolf trainer opens his cage and a "+wolf->short()+" hops "+
    "out, ready for you to mount.\n");
    say("The wolf trainer opens his cage and a "+wolf->short()+" hops "+
    "out.\n");
    add_prop(KALAD_FANG_WOLF_ID+fname,file_name(wolf));
    return 1;
}
