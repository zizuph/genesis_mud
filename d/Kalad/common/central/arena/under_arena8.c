/* 
 * /d/Kalad/common/central/arena/under_arena8.c
 * Purpose    : Adventure guild beneath the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Under the arena - the training room. */
/* made by Korat */
/* The guild code is copied from /d/Kalad/common/caravan/shop/jeinn */
/* and is made by Antharanos and Vladimir */

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#define NUM sizeof(query_money_types(-1))
#define CLOSED 0
int closed;     
object ob1;
object ob2;
object ob3;

create_room()
{
   ::create_room();
   closed = CLOSED;
   hear_bell = 1;
   add_prop(ROOM_I_INSIDE,1);
   set_short("Training room");
   set_long("You enter a large room that both smells and looks like "+
      "a training room. Some thick straw-mats covers parts of the floor, "+
      "to help break some of the hard falls the athletes endure while "+
      "wrestling. Along the southern wall you see four wooden poles "+
      "that you think is used for learning all those difficult strikes "+
      "one can do with weapons. In a corner you see an unlocked "+
      "weapon cabinet.\n");
   
   add_item(({"weapon cabinet","cabinet"}),"The wooden cabinet contains "+
      "all kinds of weapons that are used for training purposes. They "+
      "are all of wood, so that they won't do too much damage when "+
      "someone gets a good hit in during the practicing.\n");
   add_item(({"mat","mats","straw-mat","straw-mats"}),"They are fairly "+
      "thick and covers most of the floor in this room. You see a few "+
      "dark stains on them; sometimes blood are spilled in here when "+
      "the trainer gets too eager.\n");
   add_item(({"floor"}),"It is almost covered with some thick mats "+
      "that are softer to walk on than the hard ground around them.\n");
   add_item(({"pole","poles"}),"These red-wood poles have been pounded "+
      "into the ground and looks fairly battered. Alot of strikes from "+
      "swords, polearms and other weapons has fallen upon them.\n");
   add_item(({"walls"}),"The walls are of rough-cut stones that are "+
      "damp to the touch.\n");
   add_item("plaque", "@@exa_plaque");
   
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   create_guild_support();
   create_skill_raise();
   set_up_skills();
   
   add_exit (CENTRAL(arena/under_arena6),"north",0,-1,-1);
   set_alarm(1.0,0.0,"reset_room");
}

wizinfo() {
   return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Korat.\n");
}

enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (!interactive(ob) || !closed)
      return;
   if (ob->query_wiz_level())
      write("\n\nWARNING!\n You shouldn't be here. "+
      "I'm doing some work on the training room.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Kalad/common/central/arena/under_arena6");
   }
}

init() {
   init_guild_support();
   init_skill_raise();
   ::init();
}

close_guild() {
   if (closed) {
      closed = 0;
      return "  **The training room is now open**";
   }
   closed = 1;
   return "  **The training room is now closed**";
}

query_closed() {return closed;}

set_up_skills() {
   sk_add_train(SS_WEP_SWORD,   train_text(SS_WEP_SWORD),      0,0,30);
   sk_add_train(SS_WEP_AXE,   train_text(SS_WEP_AXE),      0,0,30);
   sk_add_train(SS_WEP_CLUB,   train_text(SS_WEP_CLUB),     0,0,30);
   sk_add_train(SS_WEP_KNIFE,   train_text(SS_WEP_KNIFE),      0,0,25);
   sk_add_train(SS_WEP_POLEARM,   train_text(SS_WEP_POLEARM),      0,0,20);
}

train_text(skill) {
   string what;
   switch(skill) {
      case SS_WEP_SWORD:
      what="use a sword";
      break;
      case SS_WEP_AXE:
      what="use an axe";
      break;
      case SS_WEP_CLUB:
      what="use a club";
      break;
      case SS_WEP_KNIFE:
      what="use a knife";
      break;
      case SS_WEP_POLEARM:
      what="use a polearm";
      break;
      
      default:
      what="do nothing. THIS IS A BUG";
      break;
   }
   return what;
}

void
reset_room()
{
   if(!ob1){
      ob1 = clone_object("/d/Kalad/common/central/npc/trainer");
      ob1 -> move_living("M",TO);
      tell_room(TO,"An experienced gladiator comes walking into the room.\n");
      ob1 -> command("say Ahhh, are you here to train? I will gladly help you "+
         "for some petty cash!\n");
      ob1 -> command("cackle");
   }
   if(!ob2){
      ob2 = clone_object("/d/Kalad/common/central/npc/student1");
      ob2 -> move_living("M",TO);
      tell_room(TO,"A warrior comes walking in and talks abit to the trainer. "+
         "Then he starts to train with a club.\n");
   }
   if(!ob3){
      ob3 = clone_object("/d/Kalad/common/central/npc/student2");
      ob3 -> move_living("M",TO);
      tell_room(TO,"A new hopefull gladiator strolls in and starts to train.\n");
   }
}

exa_plaque()
{
   say(QCTNAME(TP) + " examines the plaque and seems to brighten up "+
      "as ->he<- understands how to use this room.\n");
   return("You study the plaque for a while, and then start to read it:\n\n"+
      "If you want to train here, then you can either learn how to use"+
      "a new weapon or improve your skill in one.\n"+
      "    Budhead, Master trainer of the Arena in Kabal.\n");
}
