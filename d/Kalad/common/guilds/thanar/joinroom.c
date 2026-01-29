/* 
 * /d/Kalad/common/guilds/thanar/joinroom.c
 * Purpose    : Thanar racial guild joining room.
 * Located    : 
 * Created By : Antharanos 
 * Modified By: Rico 24.Mar.97; revamped this room 
 */ 

inherit "/lib/guild_support";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <thanardefs.h>
#include <time.h>
public int
members_only()
{
    if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())

    {
	/* Is a member, pass through as normal */

	return 0;
    }

    write("A magical force prevents you from entering.\nYou are not a "+
      "Thanarian!\n");
    return 1;
}


string title;
public void
create_room()
{
   ::create_room();
   
   set_short("Guildhall of the Thanars");
   set_long("\nThe central hall of the Thanars.\n\n"+
      "This great, circular shaped chamber is constructed entirely "+
      "from strong and enduring granite. In contrast is the floor, "+
      "which has been fashoned from a wondrous white marble. Stone "+
      "pillars guard the sides of the archways to the four corners. "+
      "Here, at the centre of the chamber, stands a night black, "+
      "marble statue. A plaque made of the same dark material has "+
      "been fastened at the base of it.\n\n");

   add_item(({ "central hall", "hall", "guildhall", "chamber",
      "circular shaped chamber", "circular chamber", "guild hall" }),
      "\nA vast and open space constructed from ages old granite. "+
      "Truly a place that will last throughout time.\n\n");
   add_item(({ "strong granite", "enduring granite", "granite",
      "ages old granite", "old granite", "black granite",
      "oddly black granite" }),
      "\nThe chamber is constructed entirely out of the oddly black "+
      "rock. In sharp contrast, the floor is composed of a gleaming "+
      "white marble.\n\n");
   add_item(({ "wondrous white marble", "wondrous marble", "white marble",
      "marble", "floor", "gleaming marble" }),
      "\nFashioned from a ghostly white substance, it contrasts sharply with"+
      " the rest of the chamber. The impression of perpetual night overhead "+
      "is obvious.\n\n");
   add_item(({ "walls", "wall", "ceiling" }),
      "\nThe structures have all been fashioned from oddly black granite."+
      "It's as though night has come early.\n\n");
   add_item(({ "stone pillars", "pillars", "granite pillars", 
      "small pillars", "black pillars", "black pillars", "pillar" }),
      "\nThe black granite constructions flank each of the archways. It "+
      "is as though they are standing guard for the dark god, Thanar.\n\n");
   add_item(({ "archways", "archway", "arch", "arches" }),
      "\nFlanked by a pair of stone pillars, one of the archways leads off "+
      "to the west while another leads north. The remaining two archways "+
      "are flanked by somewhat smaller pillars and lead to the east and "+
      "south respectively. For some reason, this arrangement looks "+
      "natural.\n\n");
   add_item(({ "night black marble statue", "night black statue",
      "marble statue", "statue", "black statue" }),
      "\nThe stature depicts a figure of amazing stature and beauty. Whoever"+
      " the artist was, their creation truly captures the sense of driving "+
      "power and inherent aggressiveness which is found within all humans "+
      "This sculpture represents the very epitome of human perfection.\n\n");
   add_item(({ "plaque", "black plaque", "granite plaque", "marble plaque" }),
      "\nSeveral words have been enscribed upon it.\n\n");
   add_cmd_item(({ "plaque", "black plaque", "marble plaque" }), "read",
     "\n\t _______________________________________________________________\n"+
     "\t/ \\                                                             \\\n"+
     "\t\\_/_____________________________________________________________/\n"+
     "\t|                                                              |\n"+
     "\t|                                                              |\n"+
     "\t|           We are no longer accepting new members.            |\n"+
     "\t|                                                              |\n"+
     "\t|______________________________________________________________|\n"+
     "\t/ \\                                                             \\\n"+
     "\t\\_/_____________________________________________________________/\n"+
     "\n"); 


   INSIDE;

   add_exit(CVAN(lot/order_room), "west", "@@west_msg", -1);
   add_exit(OLDTHANAR(shrine), "north",members_only);
   add_exit(THANAR(chamber), "east", members_only);
   add_exit(THANAR(train), "south", members_only);

   // clone_object(THANAR(public_board))->move(this_object());
   clone_object(THANAR(book))->move(this_object());
}

void
init()
{
   ::init();

//   add_action("do_join", "enter");
   add_action("do_leave", "leave");
   add_action("do_list", "list");
//   add_action("do_update","update");
}
void
west_msg()
{
   write("\nYou pass through the archway and feel yourself "+
      "transported to another place.\n\n");
   say(QCTNAME(this_player()) + " enters the archway to the west.\n\n");

   return 0;
}

int
check_member()
{
   object *ob;

   int    i;

   ob = deep_inventory(this_player());
   for(i = 0; i < sizeof(ob); i++)
   if(ob[i]->id("_sniff_my_licker"))
   {
      write("\nYou easily pass through the stone archway.\n\n");
      say(QCTNAME(this_player()) + " easily passes through a stone archway.\n\n");

      return 0;
   }

   write("\nYou vainly try to pass through the stone archway, but are "+
      "stopped by a dark and powerful force.\n\n");
   write("\nA dark presence inserts itself into your mind and speaks:\n"+
      "\t\tYou are NOT one of us!! Leave NOW!!\n\n");
   say(QCTNAME(this_player()) + " vainly tries to pass through a stone "+
      "archway but is halted in mid-stride. " + QCTNAME(this_player()) +
      "looks visibly shaken.\n\n");

   return 1;
}
 
/**********************************************************************
 * - Commented out -------------------------------------------------- *


do_join(string str)
{
   object shadow,
          symbol,
          *souls;

   int    i;
   
   if(str == "guild")
   {
      
      if(this_player()->query_race_name() != "human")
      {
         notify_fail("\nThe Thanarian human race guild does NOT accept "+
            "demihuman filth!\nYou are NOT permitted to join!\n\n");

         return 0;
      }
      
      if(this_player()->query_guild_member(GUILD_TYPE))
      {
         notify_fail("\nIt is not possible for you to be a member of "+
            "more than one racial guild!\n\n");

         return 0;
      }

      shadow = clone_object(GUILD_SHADOW);
      notify_fail("\nHow odd. For some reason you cannot join us.\n\n");
      if(shadow->shadow_me(this_player(), GUILD_TYPE,
         GUILD_STYLE, GUILD_NAME) != 1)
      {
         shadow->remove_object();

         return 0;
      }

      this_player()->set_bit(4, 4);
      write("\nWelcome to the ranks of the superior Thanar!\n\n");

      log_file("GUILD/thanars", extract(ctime(time()), 4, 15) + " " +
         capitalize(this_player()->query_real_name()) + "\tjoined" +
         "\tStat ave = " + this_player()->query_average_stat() + "\t" +
         "Age = " + TIME2STR(this_player()->query_age() * 2, 2) + "\n");
     
      this_player()->add_cmdsoul(THANAR_SOUL);
      
      seteuid(getuid(this_object()));

      souls = this_player()->query_cmdsoul_list();
      for (i = 0; i < sizeof(souls); i++)
         this_player()->remove_cmdsoul(souls[i]);

      this_player()->add_cmdsoul(THANAR_SOUL);

      for (i = 0; i < sizeof(souls); i++)
      if(souls[i] != THANAR_SOUL)
         this_player()->add_cmdsoul(souls[i]);

      this_player()->update_hooks();

      symbol = present("_sniff_my_licker", this_player());
      if(!symbol)
      {
         symbol =  clone_object(THANAR(symbol));
         symbol -> move(this_player());

         write("\nAn apparition of the great god Thanar appears before "+
            "you.\nTo symbolize your newfound cause for Thanar and humanity,"+
            " you are given a platinum chain necklace.\n\n");
         say("\nAn apparition of the great god Thanar appears before " +
            QCTNAME(this_player()) + ".\n");
         say(QCTNAME(this_player()) + " receives a platinum chain necklace "+
            "as a symbol of " + this_player()->query_possessive() + 
            "newfound cause for Thanar and all of humanity.\n\n");
         say(QCTNAME(this_player()) + " has joined the Thanars!\n");
      }

      return 1;
   }

   return 0;
}
 **********************************************************************/
do_leave(str)
{
   object symbol,
          sound;

   int    result;
   
   if(str != "guild")
   {
      write("\nWhat is it you wish to leave?\n\n");

      return 1;
   }
   
   if((this_player()->query_guild_name_race()) != (GUILD_NAME))
   {
      notify_fail("\nYou can't leave a guild you aren't a member of!\n"+
         "What are you, stupid?!\n\n");

      return 0;
   }

   if(this_player()->remove_guild_race())
   {
      write("\nYou are no longer a member of the Thanars.\n");
      this_player()->clear_bit(4, 4);

      symbol = present("_sniff_my_licker", this_player());
      if(symbol)
      {
         symbol->remove_object();
         write("You are stripped of your platinum chain necklace!\n\n");
         say(QCTNAME(this_player()) + " has left the Thanars! Traitor!!\n\n");

      }
         log_file("GUILD/thanars", extract(ctime(time()), 4, 15) + " " +
            capitalize(this_player()->query_real_name()) + "\tleft" +
            "\tStat ave = " + this_player()->query_average_stat() + "\t" +
            "Age = " + TIME2STR(this_player()->query_age() * 2, 2) + "\n");

      this_player()->remove_cmdsoul(THANAR_SOUL);
      this_player()->clear_guild_stat(SS_RACE);
      this_player()->update_hooks();
   }
   else
      write("\nBecause of an error, you remain with us.\n\n");

   return 1;
}


do_list()
{
   string str;

   str = this_player()->list_major_guilds();
   if (str)
      write("\nYou are a member of the following guilds.\n" + str);
   else
      write("\nYou are not a member of any important guilds.\n");
   
   return 1;
}

void
soul(object ob)
{
   object spells;

   int    i;

   string *souls;
   
   seteuid(getuid(this_object()));

   souls = ob->query_cmdsoul_list();
   for (i = 0; i < sizeof(souls); i++)
      ob->remove_cmdsoul(souls[i]);
      ob->add_cmdsoul(THANAR_SOUL);

   for (i = 0; i < sizeof(souls); i++)
      if(souls[i] != THANAR_SOUL)
         ob->add_cmdsoul(souls[i]);
         ob->update_hooks();
}

int 
do_update(string str)
{
   object shadow,
          symbol;
   
   if ((!str)||(str != "membership"))
   {
      notify_fail("\nUpdate what?\n");

      return 0;
   }
   
   if(!IS_MEMBER(TP) && TP->query_guild_name_race()!=GUILD_NAME)
   {
      write("\nYou are not a member of this guild.\n\n");

      return 1;
   }
   
   if(!IS_MEMBER(this_player()))
   {
      write("\nUpdating bit.\n\n");
      this_player()->set_bit(4, 4);

      if(this_player()->test_bit("Kalad", 4, 0))
         if(this_player()->query_guild_name_occ() != "Blackhands Guild")
            this_player()->clear_bit(4, 0);
   }

   if(this_player()->query_guild_name_race() != GUILD_NAME)
   {
      write("\nUpdating shadow.\n\n");
      shadow = clone_object(GUILD_SHADOW);
      if(shadow->shadow_me(this_player(), GUILD_TYPE, GUILD_STYLE,
               GUILD_NAME) != 1)
      {
         write("\nUnable to update your shadow.\nPlease contact a "+
            "wizard about this.\n\n");

         shadow->remove_object();
      }
   }

   symbol = present("_sniff_my_licker", this_player());
   if(!symbol)
   {
      seteuid(getuid(this_object()));

      symbol = clone_object(THANAR(symbol));
      symbol -> move(this_player());
   }

   write("Done!\n\n");

   return 1;
}

