inherit "/d/Kalad/room_std";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#define NUMM sizeof(MONEY_TYPES)

#define WOLF_O_OCCUPIED "_wolf_o_occupied"
#define KALAD_FANG_WOLF_ID "_kalad_fang_wolf_id_"

/* Mhyrkhaan */

string *winfo;

void
create_room()
{
    ::create_room();
    set_short("War Stables");
    set_long("You are in the War Stables. There are cages "+ 
    "with wolves in them all over the room. There is a sign on one wall. "+
    "The wolves in these cages are specially bread to kill, their fangs "+
    "are sharp and extra long. Muscles can be seen bulging on even the smallest "+
    "of the wolves in here.\n");
    add_item("cages","They are iron cages with mean looking "+
    "wolves in them.\n");
    add_item("sign","The sign has readable words on it.\n");
    add_cmd_item("sign","read","@@wolf_sing@@");
    INSIDE;
    add_exit(COMMON(guilds/riders/rhall),"west",0,-1,-1);
    config_default_trade();
}

string
wolf_sing()
{
    return
    "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n"+
    "|  Here you can buy wolves that will always be  |\n"+
    "|  here when you come back. They cost a mere 5  |\n"+
    "|  platinum coins. You can also select your own |\n"+
    "|  description for them from the list here. You |\n"+
    "|  can always suggest more with the 'idea'      |\n"+
    "|  command. You can do the following:           |\n"+
    "|  buy warwolf with (1st adj#) and (2nd adj#)   |\n"+
    "|  fetch warwolf from stables                   |\n"+
    "|  send warwolf back to stables                 |\n"+
    "|  list adjectives                              |\n"+
    "|                                               |\n"+
    "|  When you send a warwolf back, then fetch it  |\n"+
    "|  again, he will be fully rested and feed.     |\n"+
    "|  Note: If there are two wolves on the ground  |\n"+
    "|  when you are sending back to the stable,     |\n"+
    "|  make sure you send the correct one, or else  |\n"+
    "|  the one you send will become yours. Also, if |\n"+
    "|  you buy another one, your old one will be    |\n"+
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
    string fname,*aadj;
    object warwolf;
    NF("Send what back to stables?\n");
    if(!parse_command("send "+str,E(TP),"'send' %o 'back' 'to' 'stables'",warwolf))
        return 0;
    if(!warwolf)
        return 0;
    NF("You can't send that in the stables!\n");
    if(MASTER_OB(warwolf) != "/d/Kalad/common/guilds/riders/war_wolf")
        return 0;
    NF("You must dismount your warwolf first!\n");
    if(warwolf->query_prop(WOLF_O_OCCUPIED) == TP)
        return 0;
    NF("You can't send that warwolf in.\n");
    if(warwolf->query_prop(WOLF_O_OCCUPIED) == 0)
    {
    tell_room(TO,"The warwolf keeper opens a cage.\n");
    write("Your "+warwolf->short()+" hops into the cage.\n");
    say(QCTNAME(TP)+"'s "+warwolf->short()+" hops into the cage.\n");
    winfo = ({});
    aadj = warwolf->query_adj(1);
    fname = lower_case(TP->query_name());
    if(sizeof(aadj) == 1)
        winfo = ({fname,aadj[0],"single"});
    else
        winfo = ({fname,aadj[0],aadj[1]});
    save_object("/d/Kalad/common/guilds/riders/LOG/"+fname);
    add_prop(KALAD_FANG_WOLF_ID+fname,0);
    warwolf->remove_object();
    return 1;
    }
    else
        return 0;
}


int
do_fetch(string str)
{
    string fname,adj1,adj2;
    object warwolf,me;
    int fcon;
    me = TP;
    NF("Fetch what?\n");
    if(str != "warwolf from stables")
        return 0;
    fname = lower_case(TP->query_name());
    if(query_prop(KALAD_FANG_WOLF_ID+fname))
        warwolf = find_object(query_prop(KALAD_FANG_WOLF_ID+fname));
    NF("Your warwolf is already out in the world!\n");
    if(warwolf)
        return 0;
    winfo = ({});
    NF("You don't have a warwolf stabled here!\n");
    if(!restore_object("/d/Kalad/common/guilds/riders/LOG/"+fname))
        return 0;
    adj1 = winfo[1];
    adj2 = winfo[2];
    if(adj2 == "single")
    {
    fcon = TP->query_stat(2);
    warwolf = clone_object(COMMON(guilds/riders/war_wolf));
    warwolf->set_wolf_desc_one(adj1);
    warwolf->set_base_stat(2,fcon+50);
    tell_room(TO,"The warwolf keeper opens one of the cages.\n");
    set_this_player(me);
    write("Your "+warwolf->short()+" hops out of the stables.\n");
    warwolf->move_living("M",TO);
    say(QCTNAME(TP)+"'s "+warwolf->short()+" hops out the stables.\n");
    add_prop(KALAD_FANG_WOLF_ID+fname,file_name(warwolf));
    return 1;
    }
    fcon = TP->query_stat(2);
    warwolf = clone_object(COMMON(guilds/riders/war_wolf));
    warwolf->set_wolf_desc(adj1,adj2);
    warwolf->set_base_stat(2,fcon+50);
    tell_room(TO,"The warwolf keeper opens one of the cages.\n");
    set_this_player(me);
    write("Your "+warwolf->short()+" hops out of the stables.\n");
    warwolf->move_living("M",TO);
    say(QCTNAME(TP)+"'s "+warwolf->short()+" hops out the stables.\n");
    add_prop(KALAD_FANG_WOLF_ID+fname,file_name(warwolf));
    return 1;
}
 
int
do_list(string str)
{
    NF("List what?\n");
    if(str != "adjectives")
        return 0;
    seteuid(getuid());
    TP->more("/d/Kalad/open/ADJLIST",1);
    return 1;
}


int
do_buy(string str)
{
    string what, for_c, get_c, change, adj1, adj2, fname;
    int *result, m_res, price, nadj1,nadj2,fcon;
    object warwolf,me;
    me = TP;
    NF("Buy what? A warwolf?\n");
    if(!str)
        return 0;
    if(sscanf(str,"warwolf with %d and %d",nadj1,nadj2) != 2)
        return 0;
    NF("No such adjective number "+nadj1+".\n");
    switch(nadj1)
    {
        case 1:
        adj1 = "ferocious";
        break;
        case 2:
        adj1 = "deadly";
        break;
        case 3:
        adj1 = "fearsome";
        break;
        case 4:
        adj1 = "lethal";
        break;
        case 5:
        adj1 = "drooling";
        break;
        case 6:
        adj1 = "blood-lusting";
        break;
        case 7:
        adj1 = "snarling";
        break;
        case 8:
        adj1 = "fierce";
        break;
        case 9:
        adj1 = "cruel";
        break;
        case 10:
        adj1 = "savage";
        break;
        case 11:
        adj1 = "grey-maned";
        break;
        case 12:
        adj1 = "black-maned";
        break;
        case 13:
        adj1 = "white-maned";
        break;
        case 14:
        adj1 = "red-maned";
        break;
        case 15:
        adj1 = "silver-maned";
        break;
        case 16:
        adj1 = "brown-maned";
        break;
        case 17:
        adj1 = "sharp-fanged";
        break;
        case 18:
        adj1 = "hungry";
        break;
        case 19:
        adj1 = "human-eating";
        break;
        case 20:
        adj1 = "pale";
        break;
        case 21:
        adj1 = "gaunt";
        break;
        case 22:
        adj1 = "furry";
        break;
        case 23:
        adj1 = "hairy";
        break;
        case 24:
        adj1 = "foul-smelling";
        break;
        case 25:
        adj1 = "howling";
        break;
        case 26:
        adj1 = "vicious";
        break;
        case 27:
        adj1 = "wild";
        break;
        case 29:
        adj1 = "menacing";
        break;
        case 30:
        adj1 = "massive";
        break;
        case 31:
        adj1 = "angry";
        break;
        case 32:
        adj1 = "red-eyed";
        break;
        case 33:
        adj1 = "black-eyed";
        break;
        case 34:
        adj1 = "blue-eyed";
        break;
        case 35:
        adj1 = "brown-eyed";
        break;
        case 36:
        adj1 = "silver-eyed";
        break;
        case 37:
        adj1 = "male";
        break;
        case 38:
        adj1 = "female";
        break;
        default:
            return 0;
    }
    NF("No such adjective number "+nadj2+".\n");
    switch(nadj2)
    {
        case 1:
        adj2 = "ferocious";
        break;
        case 2:
        adj2 = "deadly";
        break;
        case 3:
        adj2 = "fearsome";
        break;
        case 4:
        adj2 = "lethal";
        break;
        case 5:
        adj2 = "drooling";
        break;
        case 6:
        adj2 = "blood-lusting";
        break;
        case 7:
        adj2 = "snarling";
        break;
        case 8:
        adj2 = "fierce";
        break;
        case 9:
        adj2 = "cruel";
        break;
        case 10:
        adj2 = "savage";
        break;
        case 11:
        adj2 = "grey-maned";
        break;
        case 12:
        adj2 = "black-maned";
        break;
        case 13:
        adj2 = "white-maned";
        break;
        case 14:
        adj2 = "red-maned";
        break;
        case 15:
        adj2 = "silver-maned";
        break;
        case 16:
        adj2 = "brown-maned";
        break;
        case 17:
        adj2 = "sharp-fanged";
        break;
        case 18:
        adj2 = "hungry";
        break;
        case 19:
        adj2 = "human-eating";
        break;
        case 20:
        adj2 = "pale";
        break;
        case 21:
        adj2 = "gaunt";
        break;
        case 22:
        adj2 = "furry";
        break;
        case 23:
        adj2 = "hairy";
        break;
        case 24:
        adj2 = "foul-smelling";
        break;
        case 25:
        adj2 = "howling";
        break;
        case 26:
        adj2 = "vicious";
        break;
        case 27:
        adj2 = "wild";
        break;
        case 28:
        adj2 = "single";
        break;
        case 29:
         adj2 = "menacing";
         break;
        case 30:
        adj2 = "massive";
        break;
        case 31:
        adj2 = "angry";
        break;
        case 32:
        adj2 = "red-eyed";
        break;
        case 33:
        adj2 = "black-eyed";
        break;
        case 34:
        adj2 = "blue-eyed";
        break;
        case 35:
        adj2 = "brown-eyed";
        break;
        case 36:
        adj2 = "silver-eyed";
        break;
        case 37:
        adj2 = "male";
       break;
       case 38:
       adj2 = "female";
       break;
        default:
            return 0;
    }
    winfo = ({});
    fname = lower_case(TP->query_name());
    fcon = TP->query_stat(2) + 50;
    winfo = ({fname,adj1,adj2});
    save_object("/d/Kalad/common/guilds/riders/LOG/"+fname);
    price= 8640; /* 5 platinums */
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1) 
       return 0;    
    write("You pay the warwolf trainer " + text(result[0 .. NUMM - 1]) + ".\n");
    if (change)
       write("He gives you " + change + " as change.\n");
    warwolf = clone_object(COMMON(guilds/riders/war_wolf));
    if(adj2 == "single")
        warwolf->set_wolf_desc_one(adj1);
    else
        warwolf->set_wolf_desc(adj1,adj2);
    warwolf->set_base_stat(2,fcon);
    warwolf->move_living("xxx",TO);
    set_this_player(me);
    write("The warwolf trainer opens his cage and a "+warwolf->short()+" hops "+
    "out, ready for you to mount.\n");
    add_prop(KALAD_FANG_WOLF_ID+fname,file_name(warwolf));
    return 1;
}
