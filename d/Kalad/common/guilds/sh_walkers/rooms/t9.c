inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/shadow_walkers/default.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

object ob;
void reset_room();

void
create_room()
{
    set_short("In a dark tunnel");
    set_long("The tunnel dumps off here. To the west, an open doorway "+
    "stands, and you can see nothing but shadows beyond. A single "+
    "torch burns on the wall here, lighting the room. There are "+
    "rats scurrying around here. Shadows of evil and darkness "+
    "surround you like a second skin. There is a small, decrepit "+
    "wooden table against one wall, with a chair behind it.\n");
    add_item("rats","They dart here and there, looking for scraps.\n");
    add_item("torch","The torch burns softly on the wall.\n");
    add_item(({"table","wooden table"}),"There is an ink bottle, "+
    "pen and sheet of paper on the table, as well as a plate with "+
    "food crumbs on it.\n");
    add_item("chair","A strong wooden chair. A black-eyed, silver-haired "+
    "elf sits in it.\n");
    add_item("ink bottle","It is filled with ink.\n");
    add_item("paper","You see names of individuals scrawled on it.\n");
    add_item("pen","For writing.\n");
    add_item("walls","The walls are carved from stone, and they "+
    "radiate an aura of darkness.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    add_exit(SHDIR(t10),"west","@@block@@",-1,1);
    add_exit(SHDIR(t8),"south",0,-1,1);
    reset_room();
}

int
block()
{
    if(TP->query_guild_name_lay() == GUILD_NAME)
        return 0;
    if(TP->query_name() == "Sarr")
    {
        write("Enter, Master Sarr...\n");
        return 0;
    }
    TP->catch_msg(QCTNAME(ob)+" stops you from going that way.\n");
    return 1;
}


void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(SHDIR(shantaris));
        ob->move_living("xxx",TO);
    }
}


void
init()
{
   ::init();
   add_action("do_pledge", "pledge");
   add_action("wimp", "wimp");
   add_action("list", "list");
   add_action("update","update");
}


int
do_pledge(string str)
{
    int i,test;
    object casea;
    object shadow;
    mixed *souls;
    NF("Pledge what?\n");
    if(str != "to be a shadow walker")
        return 0;
    if(TP->query_alignment() > 100)
    {
        NF("Get out of here, your good deeds make me sick.\n");
        return 0;
    }
    if(TP->query_age() < 351160)
    {
       NF("You are too young to start a life of crime. Grow up "+
       "some more.\n");
        return 0;
    }
    if (TP->query_guild_member(GUILD_TYPE))
    {
        NF("You cannot be a member of two layman guilds!\n");
        return 0;
    }
    shadow = clone_object(SW_SHADOW);
    NF("How odd. For some reason you cannot join us.\n");
    if ((test = shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME)) != 1)
    {
        shadow->remove_object();
        write("Test: "+test+".\n");
        return 0;
    }
    TP->set_bit(4,0);
    tell_room(TO,QCTNAME(ob)+" writes something down on the piece of "+
    "paper on the table.\n");
    ob->command("say Welcome, "+TP->query_name()+".");
    log_file("shadow_walkers",TP->query_real_name()+" joined "+
         extract(ctime(time()),4,15)+".\n");
    TP->add_cmdsoul(SW_SOUL);
    seteuid(getuid(TO));
    souls = TP->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
        TP->remove_cmdsoul(souls[i]);
    TP->add_cmdsoul(SW_SOUL);
    for (i = 0; i < sizeof(souls); i++)
        if(souls[i] != SW_SOUL)
             TP->add_cmdsoul(souls[i]);
    TP->update_hooks();
    TP->clear_guild_stat(SS_LAYMAN);
    casea = present("_shadow_walkers_", TP);
    if(!casea)
    {
         casea = clone_object("/d/Kalad/common/guilds/shadow_walkers/sw_case");
         casea->move(TP);
         TP->catch_msg(QCTNAME(ob)+" gives you a black leather carrying "+
         "case.\n");
         tell_room(TO,QCTNAME(ob)+" gives "+QTNAME(TP)+" a black "+
         "leather carrying case.\n",TP);
    }
    return 1;
}

int
wimp(string str)
{
    object casea;
    int result;
    object sould;
    NF("Wimp what?\n");
    if (str != "out")
        return 0;   
    NF("You cannot leave a guild you are not a member of.\n");
    if(TP->query_guild_name_lay() != GUILD_NAME)
        return 0;
    if(TP->remove_guild_lay())
    {
        write("You wimp out of the Shadow Walkers!\n");
        TP->clear_bit(4,0);
        ob->command("emote screams: WHAT?!?!");
        ob->command("emote screams: Wimpying out!!");
        casea = present("_shadow_walkers_", TP);
        if(casea)
        {
            ob->command("emote rips your black leather carrying case from "+
            "you.");
            casea->remove_object();
            log_file("shadow_walkers",TP->query_real_name()+" left   "+
            extract(ctime(time()),4,15)+".\n");
        }
        TP->remove_cmdsoul(SW_SOUL);
        TP->clear_guild_stat(SS_LAYMAN);
        TP->update_hooks();
        ob->command("emote suddenly grabs your head, smashes it againts "+
        "the wall, then angrly slits your throat with his lethal "+
        "vorpal dagger.");
        return 1;
    }
    else
        write("Because of an error, you remain with us.\n");
    return 1;
}

int
list()
{
   
   string str;
   
   str = TP->list_major_guilds();
   if (str)
      write("You are a member of the following guilds.\n" + str);
   else
      write("You are not a member of any important guilds.\n");
   
   return 1;
}

void
soul(object ob)
{
   object spells;
   int i;
   string *souls;
   seteuid(getuid(TO));
   souls = ob->query_cmdsoul_list();
   for (i = 0; i < sizeof(souls); i++)
   ob->remove_cmdsoul(souls[i]);
   ob->add_cmdsoul(SW_SOUL);
   for (i = 0; i < sizeof(souls); i++)
   if(souls[i] != SW_SOUL)
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
}

int 
update(string str)
{
   int i, casea;
   object shadow;
   object *inv;

   if (!str || str != "membership")
      {
      NF("Update what?\n");
      return 0;
   }
   
   if(TP->query_guild_name_lay() != GUILD_NAME)
   {
      write("You are not a member of this guild.\n");
      return 1;
   }   
   write("Updating bit.\n");
   TP->set_bit(4,0);

   inv = deep_inventory(TP);
   for(i=0;i<sizeof(inv);i++)
   {
       if(inv[i]->query_name() == "_shadow_walkers_")
           casea = 1;
   }
   if(casea == 0)
   {
       clone_object("/d/Kalad/common/guilds/shadow_walkers/sw_case")->move(TP);
   }  
   if(TP->query_guild_name_lay() == GUILD_NAME)
   {
       write("Updating shadow.\n");
       shadow = clone_object(SW_SHADOW);
       if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME)!=1)
       {
         write("Couldn't update your shadow. Please contact a wizard about this.+n");
         shadow->remove_object();
       }
    }
   write("Done!\n");
   return 1;
}
