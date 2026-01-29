/* This is the main Pirates guild room.*/

inherit "/lib/guild_support";
inherit "/std/room";

#include "defs.h"


object meditate;

void
create_room()
{
   object scroll;
   set_short("Pirates guild room");
   set_long(
      "This room looks like the quarterdeck of an old ship. "
      + "It is a place of tradition and ceremony. "
      + "In this room you can join the guild <pledge life>, "
      + "further more, you can "
      + "leave the guild <commit treason>, "
      + "and also list the guilds that you are a member of <list>. "
      + "If you are a member of the guild, you can start here if you "
      + "wish to <start here>. "
      + "If you ever lose your eyepatch, all you have to do is ask "
      + "for another one <eyepatch>."
      + "\n",);

   add_prop(ROOM_I_INSIDE, 1);
   add_exit(THIS_DIR+"boardroom","down",0);
   add_exit(THIS_DIR+"cave2","east",0);
   seteuid(geteuid());
   scroll = clone_object(PIRATES_DIR+"obj/pir_scroll");
   scroll ->move(TO);
   
   add_item(({"walls","wall"}),
      "The walls are warm and damp to the touch. Some of the "+
      "walls are covered with beautiful planks of wood.\n"
   );
   add_item(({"floor","ground"}),
      "The floor has been covered with beautiful planks "+
      "of wood. They gleam in the torch light.\n"
   );
   add_item(({"planks","plank","planks of wood","beautiful planks",
            "beautiful plank"}),
      "The rich hardwood planks are fitted together with brilliant "+
      "artistry.\n");
   add_item(({"torches","torch","torch light","light"}),
      "The torches line the walls of the room. The light "+
      "from their flames flickers playfully across the "+
      "hardwood floor.\n"
   );
   add_item(({"display case","case","display"}),
      "The display case contains a scroll that you can read.\n");
   
}

void
init()
{
   ::init();
   add_action("join", "pledge");
   add_action("leave", "commit");
   add_action("eyepatch","eyepatch");
   add_action("start", "start");
   add_action("list", "list");
   add_action("read","read");
}

int
read(string arg)
{
   notify_fail("Read what?\n");
   if(!arg || arg != "scroll")
      return 0;
   cat(PIRATES_DIR+"pirates.txt");
   return 1;
}


int
join(string str)
{
   object eyepatch, shadow, pegleg;
   int yes_bit, quest_done, quest_with_yes, result;
   
   yes_bit = TP->query_prop("_said_yes");
   quest_done = TP->test_bit(DOMAIN_NAME,QUEST3_GROUP,PIRATE_DONE_BIT);
   quest_with_yes = TP->test_bit(DOMAIN_NAME,QUEST3_GROUP,PIRATE_ENTRY_BIT);
   if (str!="life")
      {
      write("What do you want to pledge?\n");
      return 1;
   }
   
   if (this_player()->query_guild_name_occ())
      {
      write("You are already a member of an occupational guild!\n");
      return 1;
   }
   if(quest_done && !yes_bit && !quest_with_yes)
      {
      write("If you want to join the Pirates, "+
         "you must first redo the quest. Before you redo the quest you "+
         "must tell the old mariner in the shipwreck that you wish to "+
         "join the Pirates. After you have done the quest, come back "+
         "here, and we shall wellcome you to our guild.\n");
      return 1;
   }
   if(!quest_with_yes && yes_bit)
      {
      write("After having answered yes to the mariner, you "+
         "must still finish the quest.\n");
      return 1;
   }
   if(!quest_done && !quest_with_yes)
      {
      write("You must first prove yourself "+
         "worthy.\n");
      return 1;
   }
   else
      {
      seteuid(getuid());
      shadow = clone_object(PIRATE_SH);
      notify_fail("Unable to clone shadow.\n");
      if (!shadow)
         return 0;
      notify_fail("How odd. For some reason you cannot join us.\n");
      if((result = shadow->shadow_me(this_player(), GUILD_TYPE,
                  GUILD_STYLE, GUILD_NAME)) != 1)
      {
         shadow->remove_object();
         return 0;
      }
      TP->clear_guild_stat(7);
      write("Welcome to the ranks of the Pirates of el Diablo.\n");
      log_file("pirates_joined",CAP(TP->query_real_name())+
         " joined the Pirates     "+ctime(time())+"\n");
      seteuid(getuid());
      pegleg = present("pegleg", this_player());
      if(!pegleg)
         {
         pegleg = clone_object(PIRATES_DIR+"obj/peg_leg");
         pegleg ->move(this_player());
         write("You gain a peg leg.\n");
      }
      eyepatch = present("eyepatch", this_player());
      if (!eyepatch)
         {
         eyepatch = clone_object(PIRATES_DIR+"obj/eyepatch");
         eyepatch -> move(this_player());
         write("You gain an eyepatch.\n");
         say(QCTNAME(this_player())+" joins the Pirates!\n");
      }
      return 1;
   }
}

int
leave(string str)
{
   object eyepatch, peg_leg;
   int knife, sword, defense, back, pick, trade, swim;
   notify_fail("Commit what?\n");
   if(str != "treason")
      return 0;
   if (this_player()->query_guild_name_occ()!=GUILD_NAME)
      {
      notify_fail("You can't leave a guild you are not a member of.\n");
      return 0;
   }
   if (this_player()->remove_guild_occ())
      {
      write("You are no longer a member of the Pirates.\n");
      log_file("pirates_quit",CAP(TP->query_real_name())+
         " quit the Pirates     "+ctime(time())+"\n");
      TP->remove_skill(70005);
      TP->remove_skill(SS_UNARM_COMBAT);
      knife = TP->query_skill(SS_WEP_KNIFE);
      sword = TP->query_skill(SS_WEP_SWORD);
      defense = TP->query_skill(SS_DEFENSE);
      back  = TP->query_skill(SS_BACKSTAB);
      pick  = TP->query_skill(SS_PICK_POCKET);
      trade = TP->query_skill(SS_TRADING);
      swim  = TP->query_skill(SS_SWIM);
      if(knife >= 30)
         TP->set_skill(SS_WEP_KNIFE,30);
      if(sword >= 30)
         TP->set_skill(SS_WEP_SWORD,20+random(sword/5));
      if(defense >= 30)
         TP->set_skill(SS_DEFENSE,10+random(defense/3));
      if(back >= 30)
         TP->set_skill(SS_BACKSTAB,7+random(back/3));
      if(pick >= 30)
         TP->set_skill(SS_PICK_POCKET,7+random(pick/3));
      if(trade >= 30)
         TP->set_skill(SS_TRADING,20+random(trade/7));
      eyepatch = present("eyepatch", this_player());
      peg_leg = present("eyepatch",TP);
      if (eyepatch)
         {
         eyepatch->remove_object();
         peg_leg->remove_object();
         write("Your eyepatch and peg leg are taken from you.\n");
         say(QCTNAME(this_player())+" leaves the guild.\n");
       }
      set_alarm(3.0,0.0,"keel_haul",TP);
   }
   else
      write("Because of a strange error, you are stuck with us!\n");
   return 1;
}

int
list()
{
   string str;
   
   str = this_player()->list_major_guilds();
   if (str)
      write("You are a member of the following guilds.\n" + str);
   else
      write("You are not a member of any important guilds.\n");
   
   return 1;
}

int
eyepatch()
{
   object eyepatch;
   
   if (this_player()->query_guild_name_occ()!=GUILD_NAME)
      {
      write("But you are not a member of this guild. "
         + "Only members get an eyepatch.\n");
      return 1;
   }
   eyepatch = present("eyepatch", this_player());
   if (eyepatch)
      {
      write("You already have one!\n");
      return 1;
   }
   eyepatch = clone_object(PIRATES_DIR+"obj/eyepatch");
   eyepatch -> move(this_player());
   write("You are presented a brand new eyepatch.\n");
   say(QCTNAME(this_player())+" is given a new eyepatch.\n");
   return 1;
}

int
start(string str)
{
   if (str!="here")
      {
      notify_fail("Start what?\n");
      return 0;
   }
   if (this_player()->query_guild_name_occ()!=GUILD_NAME)
      {
      notify_fail("This guild is not your home.\n");
      return 0;
   }
   if (this_player()->query_guild_name_occ()==GUILD_NAME)
      {
      write("In future you will start here.\n");
      this_player()->set_default_start_location(THIS_DIR+"main");
      return 1;
   }
   else
      {
      notify_fail("Odd. Some error prevents that.\n");
      return 0;
   }
}


int
keel_haul(object ob)
{
   tell_room(TO,
      "Two large pirates arrive through a secret "+
      "entrance. They immediately leave through "+
      "the secret passage draging "+QCTNAME(ob)+
      " with them.\n",ob);
   ob->catch_msg("Two large pirates arrive through a "+
      "secret entrance.\n");
   ob->catch_msg("They immediately leave through the "+
      "secret passage draging you with them.\n");
   ob->move_living("M",PIRATES_DIR+"guild/blasphemy");
   return 1;
}
