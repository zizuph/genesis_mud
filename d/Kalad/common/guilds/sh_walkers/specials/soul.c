#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Krynn/open/cmd/thief_soul_mudlib.c";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/shadow_walkers/default.h"
#include <cmdparse.h>
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Shadow Walkers"; }

#define KALAD_SHADOW_CONFUSED "_kalad_shadow_confused"
#define KALAD_SHADOW_IS_CONFUSING "_kalad_shadow_is_confusing"
#define KALAD_SHADOW_WIRE  "_kalad_shadow_wire"

public mapping
query_cmdlist()
{
   return ([
              #include "scommands.h"
           ]);
}

string my_title;

string *
swsay()
{
    switch(random(6))
    {
        case 0:
            return ({"whispers coldly","whisper coldly"});
             break;
        case 1:
            return ({"hisses insanely","hiss insanely"});
            break;
        case 2:
            return ({"growls dangerously","growl dangerously"});
            break;
        case 3:
            return ({"growls savagely","growl savagely"});
            break;
        case 4:
            return ({"spits madly","spit madly"});
            break;
        case 5:
            return ({"snarls cruely","snarl cruely"});
            break;
        }
}

int
c_swsay(string str)
{
    string *mess = swsay();
    say(QCTNAME(TP)+" "+mess[0]+": "+str+"\n");
    write("You "+mess[1]+": "+str+"\n");
    return 1;
}

int
steal(string str)
{
    NF("You are busy distracting right now.\n");
    if(TP->query_prop(KALAD_SHADOW_IS_CONFUSING))
        return 0;
    TP->adjust_alignment(-400);
    return ::steal(str);
}

    
public int
c_tear(string str)
{
    object robe,rag;
    NF("Tear what?\n");
    if(!parse_command("tear "+str,TP,"'tear' %o",robe))
        return 0;
    if(!robe)
        return 0;
    NF("You can only tear non-magical robes for rags.\n");
    if(robe->query_at() != A_ROBE)
        return 0;
    if(robe->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
        return 0;
    write("You tear up the "+robe->short()+" to make your rags.\n");
    say(QCTNAME(TP)+" tears up the "+robe->short()+" to make "+
    HIS(TP)+" rags.\n");
    setuid();
    seteuid(getuid());
    rag = clone_object("/d/Kalad/common/guilds/shadow_walkers/rag");
    rag->move(TP);
    rag = clone_object("/d/Kalad/common/guilds/shadow_walkers/rag");
    rag->move(TP);
    rag = clone_object("/d/Kalad/common/guilds/shadow_walkers/rag");
    rag->move(TP);
    rag = clone_object("/d/Kalad/common/guilds/shadow_walkers/rag");
    rag->move(TP);
    rag = clone_object("/d/Kalad/common/guilds/shadow_walkers/rag");
    rag->move(TP);
    robe->remove_object();
    return 1;
}

public int
c_distract(string str)
{
    object target;
    string mess;
    NF("Distract whom with what?\n");
    if(!parse_command("distract "+str,E(TP),"'distract' %l 'with' %s", 
    target,mess))
        return 0;
    if(!mess)
        return 0;
    NF("You are already busy distracting someone else!\n");
    if(TP->query_prop(KALAD_SHADOW_IS_CONFUSING))
        return 0;
    write("You distract your victim by saying: "+mess+"\n");
    say(QCTNAME(TP)+" says: "+mess+"\n");
    target->add_prop(KALAD_SHADOW_CONFUSED,1);
    write("You feel your victim is distracted...for the moment.\n");
    TP->add_prop(KALAD_SHADOW_IS_CONFUSING,1);
    set_alarm(15.0,0.0,"un_distract",target,TP);
    return 1;
}

void
un_distract(object target, object ob)
{
    tell_object(ob,"You feel your victim is no longer distracted.\n");
    target->remove_prop(KALAD_SHADOW_CONFUSED);
    ob->remove_prop(KALAD_SHADOW_IS_CONFUSING);
}

public int
c_set(string str)
{
    int i,roomlevel;
    object wire,room,trap,*inv;
    room = E(TP);
    NF("Set what where?\n");
    if(!str)
        return 0;
    if(!parse_command("set "+str,TP,"'set' %o 'here'",wire))
        return 0;
    if(!wire)
        return 0;
    NF("You can't set that here, you need a long thin wire.\n");
    if(!wire->id("_kalad_wire"))
        return 0;
    NF("You can only set traps inside!\n");
    if(!room->query_prop(ROOM_I_INSIDE))    
        return 0;
    NF("There is already a trip wire here!\n");
    inv = all_inventory(E(TP));
    for(i=0;i<sizeof(inv);i++)
    {
        if(MASTER_OB(inv[i]) == "/d/Kalad/common/guilds/shadow_walkers/trip_wire")
            return 0;
    }
    write("You cleverly hide a trip wire across the room.\n");
    say(QCTNAME(TP)+" sets a wire across the room.\n");
    setuid();
    seteuid(getuid());
    trap = clone_object("/d/Kalad/common/guilds/shadow_walkers/trip_wire");
    inv = FILTER_LIVE(all_inventory(E(TP)));
    for(i=0;i<sizeof(inv);i++)
    {     
        if(inv[i]->query_prop(KALAD_SHADOW_WIRE) == 0)
            inv[i]->add_prop(KALAD_SHADOW_WIRE,({}));
inv[i]->add_prop(KALAD_SHADOW_WIRE,inv[i]->query_prop(KALAD_SHADOW_WIRE) +
     ({file_name(trap)}));
    }
    if(TP->query_prop(KALAD_SHADOW_WIRE) == 0)
        TP->add_prop(KALAD_SHADOW_WIRE,({}));
    TP->add_prop(KALAD_SHADOW_WIRE,TP->query_prop(KALAD_SHADOW_WIRE) +
    ({file_name(trap)}));
    roomlevel = E(TP)->query_prop(ROOM_I_HIDE);
    if(roomlevel)
        roomlevel = MIN(roomlevel/5,random(roomlevel));
    trap->set_hidden_level( ( TP->query_skill(SS_HIDE) + 
    random(TP->query_skill(SS_FR_TRAP)) ) - roomlevel );
    trap->move(E(TP));    
    wire->remove_object();
    return 1;
}

public int
c_fill(string str)
{
    int i;
    object bottle, wat;
    NF("Fill what with water?\n");
    if(!parse_command("fill "+str,TP,"'fill' %o 'with' 'water'",bottle))
        return 0;
    NF("You can't fill that with water.\n");
    if(!bottle->id("bottle"))
        return 0;
    if(!bottle->query_prop(CONT_I_VOLUME))
        return 0;
    NF("There is no water in the room to fill your bottle with.\n");
    if(!E(TP)->query_prop(OBJ_I_CONTAIN_WATER))
        if(E(TP)->query_prop(ROOM_I_TYPE) != 1)
            return 0;
    NF("The bottle already has water in it!\n");
    wat = present("water",bottle); 
    if(wat && MASTER_OB(wat) == "/d/Kalad/common/guilds/shadow_walkers/water")
        return 0;
    setuid();
    seteuid(getuid());
    clone_object("/d/Kalad/common/guilds/shadow_walkers/water")->move(bottle);
    write("You fill your bottle up from the water nearby.\n");
    say(QCTNAME(TP)+" fills up the "+bottle->short()+" from the water "+
    "nearby.\n");
    return 1;
}

public int
e_scorpse(string str)
{
    int i;
    object *corpses,corpse,*obs;
    NF("Search what corpse?\n");
    if(!str)
        return 0;
    if(!(corpses = FIND_STR_IN_OBJECT(str,E(TP)) ) )
        return 0;
    if(!sizeof(corpses))
        return 0;
    corpse = corpses[0];
    NF("That is not a corpse.\n");
    if(!corpse->id("corpse"))
        return 0;
    TP->catch_msg("You kneel down to the "+corpse->short()+" and "+
    "search it for valuables.\n");
    say(QCTNAME(TP)+" kneels down to the "+corpse->short()+" and "+
    "searches it for valuables.\n");
    obs = all_inventory(corpse);
    NF("The corpse is empty.\n");
    if(!sizeof(obs))
        return 0;
    for(i=0;i<sizeof(obs);i++)
    {
        if(!obs[i]->query_prop(OBJ_M_NO_GET))
        {
            if(!obs[i]->move(TP))
                TP->catch_msg("You find "+obs[i]->short()+" and "+
                "quickly put it into your pocket.\n");
            else
                TP->catch_msg("You are too full of valuables to "+
                "get anymore.\n");
        }
    }
    return 1;
}

public int
c_hook(string str)
{
    int i;
    object item,*inv,trap,dust;
    NF("Hook what to where?\n");
    if(!parse_command("hook "+str,TP,"'hook' %o 'to' 'wire'",item))
        return 0;
    if(!item)
        return 0;
    if(dust = present("dust",item))
        item = dust;
    NF("You can't hook that to the trip wire.\n");
    if(MASTER_OB(item) != "/d/Kalad/common/guilds/shadow_walkers/fire_bomb")
        if(MASTER_OB(item) != "/d/Kalad/common/guilds/shadow_walkers/net")
            if(MASTER_OB(item) != "/d/Kalad/common/guilds/shadow_walkers/dust")
                return 0;
    inv = all_inventory(E(TP));
    for(i=0;i<sizeof(inv);i++)
    {
        if(MASTER_OB(inv[i]) == "/d/Kalad/common/guilds/shadow_walkers/trip_wire")
            trap = inv[i];
    }
    NF("There is not trip wire set here to hook it to.\n");
    if(!trap)
        return 0;
    NF("The trip wire here is already hooked to something!\n");
    if(trap->query_hooked())
        return 0;
    if(dust)
        item = E(item);
    write("You carefully hook the "+item->short()+" to the trip "+
    "wire.\n");
    say(QCTNAME(TP)+" hooks the "+item->short()+" to the trip "+
    "wire.\n");
    if(dust)
         item = present("dust",item);
    trap->set_hooked(item);
    if(dust)
        E(item)->remove_object();
    item->remove_object();
    return 1;
}
    
public int
c_help(string str)
{
    NF("Help what?\n");
    if(str == "shadow")
    {
        write("-----------------SHADOW WALKERS---------------------\n");
        write("|                                                  |\n");
        write("| help shadow emotes   =  List of emotes           |\n");
        write("| help shadow steal    =  Help on steal command    |\n");
        write("| help shadow distract =  Help on distract command |\n");
        write("| help shadow set      =  Help on set command      |\n");
        write("| help shadow hook     =  Help on hook command     |\n");
        write("| slist                =  List of members logged on|\n");
        write("| help shadow titles   =  List of possible titles  |\n");
        write("|                                                  |\n");
        write("| ideas,bugs,ect can be sent to Sarr via mail      |\n");
        write("|                                                  |\n");
        write("----------------------------------------------------\n");
        return 1;
    }
    if(str == "shadow titles")
    {
    setuid();
    seteuid(getuid());
    cat("/d/Kalad/common/guilds/shadow_walkers/title_list");
    return 1;
    }
    if(str == "shadow steal")
    { 
    setuid();
    seteuid(getuid());
    cat("/d/Kalad/common/guilds/shadow_walkers/steal_des"); 
    return 1; 
    }
    if(str == "shadow emotes")
    { 
    setuid();
    seteuid(getuid());
    cat("/d/Kalad/common/guilds/shadow_walkers/emote_des"); 
    return 1; 
    }
    if(str == "shadow distract")
    { 
    setuid();
    seteuid(getuid());     
    cat("/d/Kalad/common/guilds/shadow_walkers/distract_des"); 
    return 1;
    }
    if(str == "shadow set")
    {
    setuid();
    seteuid(getuid()); 
    cat("/d/Kalad/common/guilds/shadow_walkers/set_des"); 
    return 1; 
    }
    if(str == "shadow hook")
    {
    setuid();
    seteuid(getuid()); 
    cat("/d/Kalad/common/guilds/shadow_walkers/hook_des"); 
    return 1;
    }
    return 0;
}

public int
e_sthreat(string arg)
{
    object *oblist;
    NF("Sthreat whom?\n");
    if(!arg)
        return 0;
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
        return 0;
    NF("Threat only one person at a time.\n");
    if(sizeof(oblist) > 1)
        return 0;
    actor("You study",oblist," with amusement and casually offer to "+
    "break a number of "+HIS(oblist[0])+" bones if "+HE(oblist[0])+
    " doesn't get out of your face.");
    all2actbb(" studies",oblist," with amusement and casually offers "+
    "to break a number of "+HIS(oblist[0])+" bones if "+HE(oblist[0])+
    " doesn't get out of "+HIS(TP)+" face.");
    targetbb(" studies you with amusement and casually offers to "+
    "break a number of your bones if you don't get out of "+HIS(TP)+ 
    " face.",oblist);
    return 1;
}

public int
e_sglare(string arg)
{
   object *oblist;
   NF("Sglare at who?\n");
   if (!strlen(arg))
      {
      allbb(" glares dangerously, "+HIS(TP)+" eyes like daggers.");
      write("You glare dangerously, your eyes like daggers.\n");
      SOULDESC("glaring with knife-like eyes.");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   SOULDESC("glaring with knife-like eyes.");
   actor("You glare at", oblist, " dangerously, your eyes like daggers.");
   all2actbb(" glares at", oblist, " dangerously, "+HIS(TP)+" eyes like "+
   "daggers.");
   targetbb(" glares at you dangerously, "+HIS(TP)+" eyes like "+
   "daggers.", oblist);
   return 1;
}

public int
e_spart(string exit)
{
    string sin,sout;
    NF("Spart in which direction?\n");
    if(!exit)
        return 0;
    sin = TP->query_m_in();
    sout = TP->query_m_out();
    TP->set_m_in("steps out of the shadows.");
    TP->set_m_out("steps into the shadows to the");
    write("You step into the shadows to the "+exit+".\n");
    TP->command(exit);
    TP->set_m_in(sin);
    TP->set_m_out(sout);
    return 1;
}

public int
e_ssneer(string arg)
{
   object *oblist;
   NF("Ssneer at who?\n");
   if (!strlen(arg))
      {
      allbb(" sneers in contempt.");
      write("You sneer in contempt.\n");
      SOULDESC("sneering in contempt.");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   SOULDESC("sneering in contempt.");
   actor("You sneer at", oblist, " in contempt.");
   all2actbb(" sneers at", oblist, " in contempt.");
   targetbb(" sneers at you in contempt.", oblist);
   return 1;
}

public int
e_seye(string arg)
{
   object *oblist;
   NF("Seye who's valuables?\n");
   if (!strlen(arg))
      return 0;
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   SOULDESC("eyeing your valuables greedily.");
   actor("You eye", oblist, "'s valuables greedily.");
   all2actbb(" eyes", oblist, "'s valuables greedily.");
   targetbb(" eyes your valuables greedily.", oblist);
   return 1;
}

public int
e_sint(string arg)
{
   object *oblist;
   NF("Sint who?\n");
   if (!strlen(arg))
      return 0;
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   actor("You glare at", oblist, " with hatred, running your "+
   "finger across your neck slowly.");
   all2actbb(" glares at", oblist, " with hatred, running "+HIS(TP)+
   " finger across "+HIS(TP)+" neck slowly.");
   targetbb(" glares at you with hatred, running "+HIS(TP)+
   " finger across "+HIS(TP)+" neck slowly.", oblist);
   return 1;
}

public string
q_title(object ob, int wiz)
{
   if (!ob->query_guild_member("Shadow Walkers"))
      return 0;
   if(ob->query_wiz_level())
       return "-<{ "+ob->query_presentation()+" }>-"; 
   return implode(explode(break_string(ob->query_presentation(), 76), "\n"),
      "\n    ");
}

public int
c_slist()
{
   int i = 0;
   write("You hear rumours that the following thieves are walking "+
      "the shadows of the world:\n"+
      implode(map(users() - ({ 0 }), "q_title", this_object(), i) - ({ 0 }),
         "\n") + "\n");
   return 1;
}

public int
e_slurk()
{
      all(" lurks in the shadows.");
      write("You lurk in the shadows.\n");
      SOULDESC("lurking in the shadows.");
      return 1;
}


public int
e_sback()
{
      all(" backs up againts a wall.");
      write("You back up againts a wall.\n");
      SOULDESC("backed up againts a wall.");
      return 1;
}

public int
e_snarrow()
{
      all(" narrows "+HIS(TP)+" eyes suspiciously.");
      write("You narrow your eyes suspiciously.\n");
      SOULDESC("eyes are narrowed suspiciously.");
      return 1;
}

public int
e_skneel()
{
      all(" kneels on the ground, searching for traps.");
      write("You kneel on the ground, searching for traps.\n");
      return 1;
}

public int
e_semote()
{
      all(" shows no emotion on "+HIS(TP)+" face.");
      write("You show no emotion on your face.\n");
      return 1;
}

public int
c_shand(string str)
{
    NF("Sign what in the thief hand language?\n");
    if(!str)
        return 0;
    NF("You can't form such a long sentance with your hands.\n");
    if(strlen(str) > 20)
        return 0;
    write("You sign in the thief hand language: "+str+"\n");
    filter(all_inventory(E(TP)) - ({TP}), "do_say",TO,({str,TP}));
    return 1;
}
    
int
do_say(object who,mixed arr)
{
    string str;
    object ob;
    str = arr[0];
    ob = arr[1];
    if(who->query_guild_name_lay() != GUILD_NAME)
    {
        who->catch_msg(QCTNAME(ob)+" signs with "+HIS(ob)+" hands.\n");
        return 0;
    }
    else
    {
        who->catch_msg(QCTNAME(ob)+" signs in the thief hand language: "+
        str+"\n");
        return 1;
    }
}

public int
e_smercy(string str)
{
      all(" shows no mercy. Mercy is for the weak.");
      write("You show no mercy. Mercy is for the weak.\n");
      return 1;
}

public int
e_speer()
{
      all(" peers around the corner cautiously.");
      write("You peer around the corner cautiously.\n");
      return 1;
}



public int
e_sgrip(string str)
{
    object wep;
    NF("Sgrip what weapon?\n");
    if(!str)
        return 0;
    if(!parse_command("sgrip "+str,TP,"'sgrip' %o",wep))
        return 0;
    if(!wep)
        return 0;
    NF("You must wield the "+wep->short()+" first.\n");
    if(wep->query_wielded() != TP)
        return 0;
    all(" grips "+HIS(TP)+" "+wep->short()+" tightly.");
    TP->catch_msg("You grip your "+wep->short()+" tightly.\n");
    SOULDESC("gripping his weapon tightly.");
    return 1;
}

public int
e_sapp(string str)
{
    object ob;
    NF("Sapp what object?\n");
    if(!str)
        return 0;
    if(!parse_command("sapp "+str,TP,"'sapp' %o",ob))
        if(!parse_command("sapp "+str,E(TP),"'sapp' %o",ob))
            return 0;
    if(!ob)
        return 0;
    NF("You can only appraise non-living objects.\n");
    if(living(ob))
        return 0;
    all(" studies the "+ob->short()+" carefully, appraising its worth.");
    TP->catch_msg("You study the "+ob->short()+" carefully, "+
    "appraising its worth.\n");
    TP->command("appraise "+lower_case(ob->query_name()));
    return 1;
}


public int
e_swipe(string str)
{
    object wep;
    NF("Swipe what weapon?\n");
    if(!str)
        return 0;
    if(!parse_command("swipe "+str,TP,"'swipe' %o",wep))
        return 0;
    if(!wep)
        return 0;
    NF("You must wield the "+wep->short()+" first.\n");
    if(wep->query_wielded() != TP)
        return 0;
    all(" wipes the blood off "+HIS(TP)+" "+wep->short()+
    " on "+HIS(TP)+" sleeve.");
    TP->catch_msg("You wipe the blood off your "+wep->short()+
    " on your sleeve.\n");
    return 1;
}


public int
e_slick(string str)
{
    object wep;
    NF("Slick the blade of what dagger?\n");
    if(!str)
        return 0;
    if(!parse_command("slick "+str,TP,"'slick' %o",wep))
        return 0;
    if(!wep)
        return 0;
    NF("You can only lick the blade of knives or daggers.\n");
    if(wep->query_wt() != 3)
        return 0;
    NF("You must wield the "+wep->short()+" first.\n");
    if(wep->query_wielded() != TP)
        return 0;
    all(" licks the blade of "+HIS(TP)+" "+wep->short()+
    " slowly.");
    TP->catch_msg("You lick the blade of your "+wep->short()+
    " slowly.\n");
    return 1;
}

public int
e_sbran(string str)
{
    object wep,*tars;
    string tar,them,they;
    NF("Brandish your club in front of whom?\n");
    if(!str)
        return 0;
    if(!parse_command("sbran "+str,TP,"'sbran' %o 'in' 'front' 'of' %s",wep,tar))
        return 0;
    if(!wep)
        return 0;
    NF("You can only brandish clubs.\n");
    if(wep->query_wt() != W_CLUB)
        return 0;
    NF("You must wield the "+wep->short()+" first.\n");
    if(wep->query_wielded() != TP)
        return 0;
    tars = parse_this(tar,"[the] %l");
    NF("Who do you want to brandish the club at?\n");
    if(!sizeof(tars))
        return 0;
    if(sizeof(tars) > 1)
    {
        them = "them";
        they = "they pay";
    }
    else
    {
        them = HIM(tars[0]);
        they = HE(tars[0])+" pays";
    }        
    all2actbb(" shows",tars," "+HIS(TP)+" "+wep->short()+" that "+HE(TP)+
    " will pound "+them+" with unless "+they+" up.");
    actor("You show",tars," your "+wep->short()+" that you will "+
    "pound "+them+" with unless "+they+" up.");
    targetbb(" shows you "+HIS(TP)+" "+wep->short()+" that "+HE(TP)+
    " will pound you with unless you pay up.",tars);
    return 1;
}



public int
e_sknife(string str)
{
    object wep,*tars;
    string tar,them,they;
    NF("Sknife who with what knife?\n");
    if(!str)
        return 0;
    if(!parse_command("sknife "+str,TP,"'sknife' %s 'with' %o",tar,wep))
        return 0;
    if(!wep)
        return 0;
    NF("You can only use knives.\n");
    if(wep->query_wt() != W_KNIFE)
        return 0;
    NF("You must wield the "+wep->short()+" first.\n");
    if(wep->query_wielded() != TP)
        return 0;
    tars = parse_this(tar,"[the] %l");
    NF("Who do you want to threaten with your knife?\n");
    if(!sizeof(tars))
        return 0;
    if(sizeof(tars) > 1)
    {
        them = "them";
        they = "they pay";
    }
    else
    {
        them = HIM(tars[0]);
        they = HE(tars[0])+" pays";
    }        
    all2actbb(" puts "+HIS(TP)+" "+wep->short()+" to",tars,"'s throat"+
    " with an evil look in "+HIS(TP)+" eye."); 
    actor("You put your "+wep->short()+" to",tars,"'s throat with "+
    "an evil look in your eye.");
    targetbb(" puts "+HIS(TP)+" "+wep->short()+" to your throat with "+
    "an evil look in "+HIS(TP)+" eye.",tars); 
    return 1;
}




