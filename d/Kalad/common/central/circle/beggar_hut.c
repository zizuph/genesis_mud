inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include "/d/Kalad/defs.h"

#define NUM sizeof(query_money_types(-1))
#define CLOSED 0
#define CLUB_NAME "beggarsclubmembers"

object ob1;
int closed;
/* by Korat, modified from order of Thanar in Kalad */
   
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   set_short("ramshakle hut");
   set_long("This hut looks better from the inside than from the Circle "+
      "street, but still you are afraid it will suddenly fall down onto "+
      "your head. When you let your eyes scan the items in here, they "+
      "abruptly stop at that wretched human in the corner. She, well you "+
      "think it is a she but to be sure you would have to peel of several "+
      "layers of dirt from that face, looks at you with some pleading eyes "+
      "that @@reaction@@. The rest of the hut is sparsely furnished; All "+
      "you see is a table with a chair next to it in the corner, and "+
      "a wooden sign with some large letters cut roughly into it, hanging "+
      "on the wall next to a door. Well you hesitate to call it a door "+
      "really, since any door-maker guild would frown upon your use of words. "+
      "It does lead out to the street though.\n");
   hear_bell = 2;
   add_item(({"sign","letters","wooden sign"}),"You wonder who made "+
      "this thing, but after studing it you decide it must be a child. "+
      "Or maybe that wretched human in the corner?\n");
   add_item(({"hut","ramshakle hut"}),"Well, its made of old cracked "+
      "wooden boards that probably have been found floating in the sea "+
      "or stranded on the beach, because you see several signs marking "+
      "them as crates used by the local trading company. The hut is lighted "+
      "up by sunbeams, sneaking inside through all the cracks and holes.\n");
   add_item(({"table","chair"}),"Both the table and the chair has two of "+
      "the legs abit shorter than the others, making them pretty unstable "+
      "and fairly useless.\n");
   add_cmd_item(({"letters","sign","wooden sign"}),"read","@@letters");
   add_exit(CENTRAL(circle/s10),"out",0,-1,-1);
   clone_object(CENTRAL(circle/beggar_board))->move(TO);
   
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   create_guild_support();
   create_skill_raise();
   set_up_skills();
   
   set_alarm(1.0,0.0,"reset_room");
}
wizinfo() {
   return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will tmporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Anth.\n");
}
enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (!interactive(ob) || !closed)
      return;
   if (ob->query_wiz_level())
      write("n\\WARNING!\n You shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Kalad/common/central/circle/s10");
   }
}

init() {
   init_guild_support();
   init_skill_raise();
   ::init();
   add_action("become","become");
   add_action("end","end");
}

close_guild()
{
   if (closed) {
      closed = 0;
      return "  **The guild is nowopen**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}

query_closed() {return closed;}

set_up_skills() {
   sk_add_train(SS_PICK_POCKET,   train_text(SS_PICK_POCKET),     0,0,20);
   sk_add_train(SS_AWARENESS,   train_text(SS_AWARENESS),      0,0,30);
   sk_add_train(SS_APPR_MON,   train_text(SS_APPR_MON),      0,0,40);
}

train_text(skill) {
   string what;
   switch(skill) {
      case SS_PICK_POCKET:
      what="pick someone's pocket, a nice thing to know for a beggar";
      break;
      case SS_AWARENESS:
      what="notice things in your environment, maybe some coins around?";
      break;
      case SS_APPR_MON:
      what="compare yourself to someone else, important to avoid trouble!";
      break;
      default:
      what="do nothing. THIS IS A BUG";
      break;
   }
   return what;
}

reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/beggar_master");
      ob1 -> arm_me();
      ob1 -> move_living("xxx", TO);
   }
}

reaction()
{
   if (TP->query_alignment()>500)
      return "makes you feel pity and compassion for her";
   if (TP->query_alignment()<-500)
      return "makes you want to laugh in her face";
   
   return "you don't know how to react on. Should you laugh at her or should "+
   "you feel pity and compassion for this creature..";
}

letters()
{
   return "You read the letters on the board: \n\n"+
   
   " __      _                /\\           _                           \n"+
   "|  \\    /         __     /  |         / \\            _           __\n"+
   "\\   |  /     __   | \\   /__/|        |   |      __  / \\    |    /  \\ \n"+
   " \\__|  |\\_  /  \\  |  | /    |    /|      /   __/    |    | |  | | _|\n"+
   " /  |  |_   | __  | __      |    \\|     /           |    |  \\_/ | \\ \n"+
   " \\_/        |__|  |__|      |    /|    |__|          \\_  |___   |_/ \n";
}


end(string s)
{
   NF("The wretched human wonders: End what? Your life?? Attack "+
      "the High Lord, and "+
      "that should fix itself!\n");
   if(s!="membership")
      return 0;
   
   NF("The wretched human sighs: You're not a member! How can you stop being "+
      "a member when you are not a member??\n");
   if(!present("beggarmember",TP))
      return 0;
   
   present("beggarmember",TP)->remove_object();
   
   if(TP->query_average_stat()>50)
      {
      write("The wretched human smiles and says: Its time for you to leave, "+
         "yes. I do wish you a good life and hope you will earn piles of "+
         "cash! Remember me if you earn that pile?\n");
      say("The wretched human says something to "+ QCTNAME(TP) + "and wishes "+
         TP->query_objective() + " a rewarding life as "+ TP->query_pronoun() +
         " leaves the beggars club.\n");
      return 1;
   }
   
   write("The wretched human fumes: Well good riddance! May your money pouch "+
      "be cursed so that you will loose it hundreds of times!\n");
   say(QCTNAME(TP) + " leaves the Beggars Club. The wretched human doesn't "+
      "look very pleased about it!\n");
   
   return 1;
}
become(string s)
{
   NF("The wretched human laughs: Become what? Rich??\n");
   if (!s)
      return 0;
   NF("The wretched human goes duhh! at you and says: My god, you are "+
      "stupid. Not heard of irony ehh?\n");
   if (s=="rich")
      return 0;
   NF("The wretched human laughs: Become what? Rich??\n");
   if (s != "member")
      return 0;
   
   /* the player can't join... */
   NF("The wretched human sighs: You are too big to be a member of this "+
      "club. Go and earn your coins some other way, and give me some of them?\n");
   if (TP->query_average_stat()>50)
      return 0;
   NF("The wretched human sighs: You are too good to join us. Go and "+
      "resque some rich old ladies instead!\n");
   if (TP->query_alignment()>500)
      return 0;
   NF("The wretched human shivers: You are too evil to join us. Go and "+
      "kill some rich old ladies instead!\n");
   if (TP->query_alignment()<-500)
      return 0;
   
   /* have done the small quest??? */
   
   NF("The wretched human says: Well, you have to answer a simple "+
      "question first...\n");
   if (!TP->test_bit("Kalad",1,1)) return 0;
   
   /* let the player join... */
   say(QCTNAME(TP) + " joins the Beggars Club!.\n");
   write("The wretched human welcomes you to the Beggars Club and says:\n");
   write("To leave the club, return here and type 'end membership'.\n");
   write("Use the bowl with care...\n");
   clone_object("/d/Kalad/common/central/obj/club_bowl")->move(TP);
   seteuid(getuid(TO));
   log_file(CLUB_NAME, extract(ctime(time()),4,15) + " "+
      capitalize(TP->query_real_name()) + " became a member.\n");
   
   return 1;
}
