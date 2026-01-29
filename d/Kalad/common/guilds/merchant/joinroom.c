inherit "/lib/guild_support";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/caravan/guild/default.h"

string title;

create_room()
{
   ::create_room();
   
   hear_bell = 1;
   INSIDE;
   set_short("The Merchants Guild of Kabal");
   set_long("The central hall of the Merchants Guild of Kabal.\n"+
      "This great, circular-shaped chamber is built entirely of strong and "+
      "enduring granite, save for the floor, which is built out of a "+
      "wondrous white marble. Stone pillars stand at the sides of the "+
      "archways in the west, north, east and south. While a set of "+
      "redwood stairs with golden handrails spirals upward to the second "+
      "level of the guild, standing as they are, in the center of this "+
      "chamber. Just a few paces north of the staircase, halfway between "+
      "it and the archway in the north, is a high, twelve-foot tall pillar "+
      "of marble. At its top is a golden necklace while at its northern "+
      "face is a sign.\n");
   add_cmd_item("sign","read","Here you can join or leave the Merchants "+
      "Guild of Kabal. You may also <list> to see what guilds you are "+
      "already a member of. Use <enter> or <leave> guild. You can also do "+
      "<update membership>.\n");
   add_exit(CVAN(guild/chapel),"west","@@check_member",-1,-1);
   add_exit(CVAN(guild/entrance),"north",0,-1,-1);
   add_exit(CVAN(guild/train),"east","@@check_member",-1,-1);
   add_exit(CVAN(guild/hall1),"south","@@check_member",-1,-1);
   add_exit(CVAN(guild/meeting),"up","@@check_member",-1,-1);
   clone_object(CVAN(guild/public_board))->move(TO);
}

void
init()
{
   ::init();
   add_action("join", "enter");
   add_action("my_leave", "leave");
   add_action("list", "list");
   add_action("update","update");
}

join(str)
{
   object shadow,chain;
   int i;
   object *souls;
   
   if(str == "guild")
      {
      
      if(TP->query_race_name() == "goblin")
         {
         NF("The Merchants Guild does not accept barbaric goblins, you can't join!\n");
         return 0;
      }
      
      if (TP->query_guild_member(GUILD_TYPE))
         {
         NF("You can't be a member of two layman guilds!\n");
         return 0;
      }
      shadow = clone_object(GUILD_SHADOW);
      NF("How odd. For some reason you cannot join us.\n");
      if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
               GUILD_NAME)!=1)
      {
         shadow->remove_object();
         return 0;
      }
      TP->set_bit(4,3);
      write("You are now a Merchant of Kabal!\n");
      
      log_file("merchants",TP->query_real_name()+" joined "+
         extract(ctime(time()),4,15)+".\n");
      
      TP->add_cmdsoul(MERCHANT_SOUL);
      
      seteuid(getuid(TO));
      souls = TP->query_cmdsoul_list();
      for (i = 0; i < sizeof(souls); i++)
      TP->remove_cmdsoul(souls[i]);
      TP->add_cmdsoul(MERCHANT_SOUL);
      for (i = 0; i < sizeof(souls); i++)
      if(souls[i] != MERCHANT_SOUL)
         TP->add_cmdsoul(souls[i]);
      
      TP->update_hooks();
      
      chain = present("_sniff_the_roses", TP);
      if(!chain)
         {
         chain = clone_object(CVAN(guild/chain));
         chain -> move(TP);
         write("You receive your gold chain necklace, symbol of the "+
            "Merchants Guild of Kabal.\n");
         say(QCTNAME(TP) + " joins the Merchants Guild of Kabal.\n");
      }
      return 1;
   }
   return 0;
}

my_leave(str)
{
   object chain;
   int result;
   object sould;
   
   if (str!="guild")
      {
      write("What do you wish to leave?\n");
      return 1;
   }
   
   if(TP->query_guild_name_lay()!=GUILD_NAME)
      {
      NF("You cannot leave a guild you are not a member of.\n");
      return 0;
   }
   if(TP->remove_guild_lay())
      {
      write("You are no longer a member of the Merchants Guild.\n");
      write("As you leave the guild, you feel yourself become less skilled.\n");
      TP->set_skill(SS_WEP_KNIFE,10);
      TP->set_skill(SS_DEFENCE,10);
      TP->set_skill(SS_PARRY,10);
      TP->set_skill(SS_TRADING,10);
      TP->clear_bit(4,3);
      chain = present("_sniff_the_roses", TP);
      if(chain)
         {
         chain->remove_object();
         write("You are stripped of your gold chain necklace.\n");
         say(QCTNAME(TP) + " leave the Merchants Guild of Kabal.\n");
         log_file("merchants",TP->query_real_name()+" left   "+
            extract(ctime(time()),4,15)+".\n");
      }
      TP->remove(MERCHANT_SOUL);
      TP->update_hooks();
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
   ob->add_cmdsoul(MERCHANT_SOUL);
   for (i = 0; i < sizeof(souls); i++)
   if(souls[i] != MERCHANT_SOUL)
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
}

int 
update(string str)
{
   object shadow;
   
   if (!str || str != "membership")
      {
      NF("Update what?\n");
      return 0;
   }
   
   if(!IS_MEMBER(TP) && TP->query_guild_name_lay()!=GUILD_NAME)
      {
      write("You are not a member of this guild.\n");
      return 1;
   }
   
   if (!IS_MEMBER(TP))
      {
      write("Updating bit.\n");
      TP->set_bit(4,3);
      if(TP->test_bit("Kalad",4,0))
         if(TP->query_guild_name_occ() != "Blackhands Guild")
         TP->clear_bit(4,0);
   }
   
   if(TP->query_guild_name_lay()!=GUILD_NAME)
      {
      write("Updating shadow.\n");
      shadow = clone_object(GUILD_SHADOW);
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
