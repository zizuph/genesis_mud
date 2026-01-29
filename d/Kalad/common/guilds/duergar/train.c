inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define NUM sizeof(query_money_types(-1))
#define CLOSED 0
int closed;
object meditate;
create_room()
{
   ::create_room();
   closed = CLOSED;
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Duergars of Underhome, training room");
   set_long("You find yourself in the middle of a large vaulted "+
      "room. In the center of it you see some dewars training hard "+
      "to hone their skills, while others seems to be raving around "+
      "looking utterly mad; They must be in some sort of meditative "+
      "state. You see a small room to the north, while the main exit is "+
      "back west. Another chamber is to the south. "+
      "Someone has scribbled some grafitti on the wall.\n");
   add_item(({"duergar","duergars"}),"They are training and meditating.\n");
   add_item(({"grafitti","wall"}),"Several words have been carved upon the wall.\n");
   add_cmd_item("grafitti","read","Here you may train in the following skills:\n"+
      "Axe, have to kill them first.                 Superior Acolyte\n"+
      "Appraise Value, GOLD!!!                       Superior Journeyman\n"+
      "Appraise Object, got to know what things are! Superior Acolyte\n"+
      "Pick Pocket, they might have nice loot.       Superior Layman\n"+
      "Language, to learn our own jargon             Superior Layman\n");

   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   add_exit("/d/Kalad/common/guilds/duergar/start","north","@@msg",-1,-1);
   add_exit("/d/Kalad/common/guilds/duergar/joinroom","west",0,-1,-1);
   add_exit("/d/Kalad/common/guilds/duergar/meeting","south",0,-1,-1);
   set_noshow_obvious(1);
   create_guild_support();
   create_skill_raise();
   set_up_skills();
}

string
wizinfo()
{
   return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Korat.\n");
}

void
enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (!interactive(ob) || !closed)
      return;
   if (ob->query_wiz_level())
      write("\n\n\WARNING!\n You shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Kalad/common/guilds/duergar/joinroom");
   }
}

void
init() 
{
   init_guild_support();
   init_skill_raise();
   ::init();
}

string
close_guild() 
{
   if (closed) 
   {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}

int query_closed() {return closed;}

void
set_up_skills() 
{
   sk_add_train(SS_WEP_AXE, train_text(SS_WEP_AXE), 0,0,40);
   sk_add_train(SS_APPR_VAL, train_text(SS_APPR_VAL), 0,0,50);
   sk_add_train(SS_APPR_OBJ, train_text(SS_APPR_OBJ), 0,0,40);
   sk_add_train(SS_PICK_POCKET, train_text(SS_PICK_POCKET), 0,0,30);
   sk_add_train(SS_LANGUAGE, train_text(SS_LANGUAGE), 0,0,30);
}

string
train_text(skill) 
{
   string what;
   switch(skill) {
      case SS_WEP_AXE:
      what="fight with an axe";
      break;
      case SS_APPR_VAL:
      what="checking the value of items";
      break;
      case SS_APPR_OBJ:
      what="checking what items is";
      break;
      case SS_PICK_POCKET:
      what="check for loot on living things";
      break;
      case SS_LANGUAGE:
      what="learn and understand our jargon";
      break;
      default:
      what="do nothing. THIS IS A BUG";
      break;
   }
   return what;
}

void
gs_hook_start_meditating()
{
   write("You start to think about gold ... that shining substance "+
      "that intriges you so much, so much that you soon can't think "+
      "of anything else than GOLD, GOLD!! You dig deeper and deeper "+
      "into these thoughts, until you suddenly feel yourself able to "+
      "<estimate> your different stats and <set> the learning "+
      "preferences at your own desire. Just <rise> when you are "+
      "done meditating.\n");
   say(QCTNAME(TP) + " goes into a frenzy, looking utterly mad.\n");
}

int
gs_hook_rise()
{
   write("As if ascending from a great depth, you rise to the surface\n" +
      "of your consciousness. You exhale and feel very relaxed as\n" +
      "you get up and prepare to actually get all that gold!.\n");
   say(QCTNAME(TP) + " seems to calm down again.\n");
}

int
msg()
{
   write("As you walk north, a sudden silence and peace settles down "+
      "on you.\n");
   return 0;
}
