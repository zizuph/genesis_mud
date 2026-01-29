inherit "/lib/guild_support";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/duergar/default.h"

string title;

create_room()
{
   ::create_room();

   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The main hall of the Duergar clan");
   set_long("This is the main hall of the Duergar-clan, and it "+
      "shows. No pictures adorn the walls, no marble statues can "+
      "be seen. The hall more resembles an old crypt that has "+
      "been occupied by some untidy creatures instead of the "+
      "more tidy and silent corpses. The masoned roof vaults above "+
      "you in an arch that ends on the rubble-covered floor, and "+
      "has two main exits to the east and to the west. Someone "+
      "seems to have scribbled some grafitti on the floor.\n");
   add_item("rubble","It is the usual rubbish that the hundreds "+
       "of duergars has left behind them.\n");
   add_item(({"grafitti","floor"}),"Several words have been written upon it.\n");
   add_cmd_item("grafitti","read","Be smart and join or be mad and leave "+
      "the Duergar race guild here. As a member of this dwarven clan, we "+
      "will grab a total tax of 2% from you. You may <list> to see what "+
      "guilds you are already a member of. Use <enter> or <leave> guild. "+
      "You can also do <update membership>.\n");
   add_exit("/d/Kalad/common/guilds/duergar/train","east","@@check_member",-1,-1);
   add_exit("/d/Kalad/common/guilds/duergar/hall1","west",0,-1,-1);
   set_noshow_obvious(1);
   clone_object(CPASS(dwarf/guild/public_board))->move(TO);
}

check_member()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for(i = 0; i < sizeof(ob); i++)
   if(ob[i]->id("_sniff_the_duergar"))
      {
      write("You walk east in the hope of meeting others of your "+
         "own kind; Duergars!\n");
      say(QCTNAME(TP) + " walks eastwards with a greedy smile on the face.\n");
      return 0;
   }
   write("You try to walk east, but the harsh noises in there frighten "+
      "you too much!\n");
   say(QCTNAME(TP) + " tries to walk east but fails!\n");
   return 1;
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
   object shadow,symbol;
   int i;
   object *souls;

   if(str == "guild")
      {

      if(TP->query_race_name() != "dwarf")
         {
         NF("With contempt, you are told that only dwarves may join!\n");
         return 0;
      }

      if (TP->query_guild_member(GUILD_TYPE))
         {
         NF("With contempt, you are told to leave those gully "+
            "rockfriend dwarves before joining here. You can't "+
            "be member of two race guilds!\n");
         return 0;
      }
      shadow = clone_object(DUERGAR_SHADOW);
      NF("How odd. For some reason you cannot join us.\n");
      if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
               GUILD_NAME)!=1)
      {
         shadow->remove_object();
         return 0;
      }
      TP->set_bit(4,6);
      write("You are now a member of the Duergar-clan.\n");

      log_file("duergar",TP->query_real_name()+" joined "+
         extract(ctime(time()),4,15)+".\n");

      TP->add_cmdsoul(DUERGAR_SOUL);

      seteuid(getuid(TO));
      souls = TP->query_cmdsoul_list();
      for (i = 0; i < sizeof(souls); i++)
      TP->remove_cmdsoul(souls[i]);
      TP->add_cmdsoul(DUERGAR_SOUL);
      for (i = 0; i < sizeof(souls); i++)
      if(souls[i] != DUERGAR_SOUL)
         TP->add_cmdsoul(souls[i]);

      TP->update_hooks();

      symbol = present("_sniff_the_sniffer", TP);
      if(!symbol)
         {
         symbol = clone_object(CPASS(dwarf/guild/symbol));
         symbol -> move(TP);
         write("You receive a token to remember you of your heritage.\n");
         say(QCTNAME(TP) + " joins the Duergars of Underhome.\n");
      }
      return 1;
   }
   return 0;
}

my_leave(str)
{
   object symbol;
   int result;
   object sould;

   if (str!="guild")
      {
      write("What do you wish to leave?\n");
      return 1;
   }

   if(TP->query_guild_name_race()!=GUILD_NAME)
      {
      NF("You cannot leave a guild you are not a member of.\n");
      return 0;
   }
   if(TP->remove_guild_race())
      {
      write("With contempt, your token are ripped away from you. You "+
         "are no longer among the Duergars of Underhome.\n");
      TP->clear_bit(4,6);
      symbol = present("_sniff_the_sniffer", TP);
      if(symbol)
         {
         symbol->remove_object();
         say(QCTNAME(TP) + " leaves the Duergar-clan of Underhome.\n");
         log_file("duergar",TP->query_real_name()+" left   "+
            extract(ctime(time()),4,15)+".\n");
      }
      TP->remove(DUERGAR_SOUL);
      TP->clear_guild_stat(SS_RACE);
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
   ob->add_cmdsoul(DUERGAR_SOUL);
   for (i = 0; i < sizeof(souls); i++)
   if(souls[i] != DUERGAR_SOUL)
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
}

int
update(string str)
{
   object shadow, symbol;

   if (!str || str != "membership")
      {
      NF("Update what?\n");
      return 0;
   }

   if(!IS_MEMBER(TP) && TP->query_guild_name_race()!=GUILD_NAME)
      {
      write("You are not a member of this guild.\n");
      return 1;
   }

   if (!IS_MEMBER(TP))
      {
      write("Updating bit.\n");
      TP->set_bit(4,6);
   }

   if(TP->query_guild_name_lay()!=GUILD_NAME)
      {
      write("Updating shadow.\n");
      shadow = clone_object(DUERGAR_SHADOW);
      if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
               GUILD_NAME)!=1)
      {
         write("Couldn't update your shadow. Please contact a wizard about "+
            "this.\n");
         shadow->remove_object();
      }
   }

   /* check for the symbol */
   symbol = present("_sniff_the_sniffer", TP);
   if(!symbol)
      {
      symbol = clone_object(CPASS(dwarf/guild/symbol));
      symbol -> move(TP);
      write("You receive a token to remember you of your heritage.\n");
   }

   write("Done!\n");
   return 1;
}
