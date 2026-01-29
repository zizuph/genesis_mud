/* 
 * /d/Kalad/common/wild/pass/goblin/guild/riders/joinroom.c
 * Purpose    : Joinroom of the Dark Alliance
 * Located    : Fang guild
 * Created By : Mhyrkhaan  3-23-97
 * Modified By: 
 * First Modif: 
 */ 

inherit "/lib/guild_support";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/riders/default.h"

string title;
object obj;

create_room()
{
   ::create_room();
   
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A dim, cold stone chamber");
   set_long("You are in a dim, cold stone chamber, much smaller "+
   "than the one above you. It seems the perpose of this room, is "+
   "to separate the part of this hideout that belongs to the feared "+
   "Army of the Dark Alliance, from the rest of it. There is a large "+
   "poster on the wall, next to a black book on a stone pedestal. "+
   "In the northern corner of the room, there is a large stone "+
   "staricase leading down into the Dark Alliance Guildhall. The sounds of"+
   "laughing, shouting, and the smell of food, rise from these stairs. "+
   "There is a large sign boldy claiming: 'RIDERS ONLY', hanging "+
   "above the staircase. If you wish to serve the Dark Alliance, this "+
   "is the room to do it in, please read the poster on the wall for "+
   "more details.\n");
   add_cmd_item("poster","read","Here is what you can do here: "+
   "If you wish to serve the Dark Alliance, you must <sign in> to the book "+
   "or you can <leave> this guild if you wish. You may also <read> the "+
   "book, for our history, or even get a <list> of the guilds you are "+
   "currently in. A disclaimer: If you are human, get the hell out of "+
   "here before you are cought in these halls.\n");
   add_item("book","A large black book, you can read it if you like");
   add_exit(CPASS(goblin/guild/joinroom),"up");
   add_exit(COMMON(guilds/riders/rhall),"down","@@check_member",-1);

}

check_member()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for(i = 0; i < sizeof(ob); i++)
   if(ob[i]->id("_rider_"))
      {
      return 0;
   }
   write("You try to head downstairs, but are pushed backwards by a "+
         "crowd of rowdy, yelling warriors of the Dark Alliance.\n");
   say(QCTNAME(TP) + " tries to enter the Riders guild, but is pushed back "+
      "by a crowd of angry warriors!\n");
   return 1;
}

void
init()
{
   ::init();
   add_action("join", "sign");
   add_action("my_leave", "leave");
   add_action("list", "list");
   add_action("update","update");
   add_action("history","read");
}

history(string str)
{
    if(str != "book")
    {
        NF("Read what? The book?\n");
        return 0;
    }
    
TP->more("/d/Kalad/open/RIDER_INFO",1);
    return 1;
}

join(str)
{
   object shadow,collar;
   int i;
   object *souls;
   
   if(str == "in")
      {
      
      if(TP->query_race_name() == "human")
         {
         NF("Get the hell out of here you Human scum!\n");
         return 0;
      }
      if(TP->query_alignment() > -1)
      {
          NF("Sorry, no goodies allowed, go get evil and come back.\n");
          return 0;
      }
      if (TP->query_guild_member(GUILD_TYPE))
         {
         NF("You cannot be a member of two layman guilds!\n");
         return 0;
      }
      shadow = clone_object(RIDER_SHADOW);
      NF("How odd. For some reason you cannot join us.\n");
      if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
               GUILD_NAME)!=1)
      {
         shadow->remove_object();
         return 0;
      }
      TP->set_bit(4,8);
      write("You sign your name and become a member of the Dark Alliance.\n");
      
      log_file("fang",TP->query_real_name()+" joined "+
         extract(ctime(time()),4,15)+".\n");
      
      TP->add_cmdsoul(RIDER_SOUL);
      
      seteuid(getuid(TO));
      souls = TP->query_cmdsoul_list();
      for (i = 0; i < sizeof(souls); i++)
      TP->remove_cmdsoul(souls[i]);
      TP->add_cmdsoul(RIDER_SOUL);
      for (i = 0; i < sizeof(souls); i++)
      if(souls[i] != RIDER_SOUL)
         TP->add_cmdsoul(souls[i]);
      
      TP->update_hooks();
      TP->clear_guild_stat(SS_LAYMAN);
      collar = present("_rider_", TP);
      if(!collar)
         {
         collar = clone_object(COMMON(guilds/riders/rcollar));
         collar -> move(TP);
         write("You receive your rider's collar.\n");
         say(QCTNAME(TP) + " signed in to join the Dark Alliance.\n");
      }
      return 1;
   }
   return 0;
}

my_leave(str)
{
   object collar;
   int result;
   object sould;
   
   if (str != "riders")
      {
      write("What do you wish to leave?\n");
      return 1;
   }
   
   if(TP->query_guild_name_lay()!=GUILD_NAME)
      {
      NF("You cannot leave a guild you are not a member of.\n");
      return 0;
   }
   if(TP->remove_guild_layman())
      {
      write("You are no longer a member of the Riders of teh Dark Alliance.\n");
      TP->clear_bit(4,8);
      collar = present("_rider_", TP);
      if(collar)
         {
         collar->remove_object();
         write("Your collar is ripped off you.\n");
         say(QCTNAME(TP) + " leaves the Dark Alliance.\n");
         log_file("rider",TP->query_real_name()+" left   "+
            extract(ctime(time()),4,15)+".\n");
      }
      TP->remove_cmdsoul(RIDER_SOUL);
      TP->clear_guild_stat(SS_LAYMAN);
      TP->update_hooks();
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
   ob->add_cmdsoul(RIDER_SOUL);
   for (i = 0; i < sizeof(souls); i++)
   if(souls[i] != RIDER_SOUL)
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
}

int 
update(string str)
{
   int i, collar;
   object shadow;
   object *inv;
   
   if (!str || str != "membership")
      {
      NF("Update what?\n");
      return 0;
   }
   
   if(!IS_MEMBER(TP) && TP->query_guild_name_layman()!=GUILD_NAME)
      {
      write("You are not a member of this guild.\n");
      return 1;
   }
   
   if (!IS_MEMBER(TP))
      {
      write("Updating bit.\n");
      TP->set_bit(4,8);
      if(TP->test_bit("Kalad",4,0))
         if(TP->query_guild_name_occ() != "Blackhands Guild")
         TP->clear_bit(4,0);
   }

   inv = deep_inventory(TP);
   for(i=0;i<sizeof(inv);i++)
   {
       if(inv[i]->query_name() == "_rider_")
           collar = 1;
   }
   if(collar == 0)
   {
       clone_object("/d/Kalad/common/guilds/riders/rcollar")->move(TP);
   }  
   
   if(TP->query_guild_name_layman()!=GUILD_NAME)
      {
      write("Updating shadow.\n");
      shadow = clone_object(RIDER_SHADOW);
      if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
               GUILD_NAME)!=1)
      {
         write("Couldn't update your shadow. Please contact a wizard about this.+n");
         shadow->remove_object();
      }
   }
   
   write("Done!\n");
   return 1;
}
