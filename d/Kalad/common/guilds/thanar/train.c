
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <thanardefs.h>

#define NUM sizeof(query_money_types(-1))
#define CLOSED 0

int closed;
object meditate;

create_room() 
{
   ::create_room();
   closed = CLOSED;
   set_short("The training room of the Thanarian Guild");
   set_long("This square-shaped room is dominated by the massive ruby-red "+
      "carpet that completely covers the floor. Hanging from the walls are "+
      "intricate tapestries depicting various highlights in the history of "+
      "Kalad. Golden braziers lie at each of the four corners of the room, "+
      "incense burning from within them to fill this room with its pungent "+
      "and intoxicating aroma. To the north is an archway leading back to "+
      "the main guildhall.\n");
   add_item(({"massive ruby-red carpet","massive carpet","ruby-red carpet","carpet"}),
      "A luxuriant carpet that looks quite comfortable, perfect for meditation.\n");
   add_item(({"walls","wall"}),
      "The black stone of the walls are covered with tapestries. depicting "+
      "various scenes from Kalad's past.\n");
   add_item(({"floor"}),
      "It is completely obscured by the carpet.\n");
   add_item(({"ceiling"}),
      "Only darkness can be seen in that direction.\n");
   add_item(({"darkness"}),
      "It is as endless as the dark heart of Thanar himself.\n");
   add_item(({"intricate tapestries","intricate tapestry","tapestries","tapestry"}),
      "Depicted are the following scenes...\n"+
      "   A man in glistening black armour leading a host of human warriors "+
      "into battle against a cowering group of gnomes.\n"+
      "   A darkly robed wizard, face concealed, setting fire to a huge "+
      "section of forest...while elven children and women run screaming and "+
      "burning.\n"+
      "   A obsidian-cloaked priest, arms raised to the darkened sky, "+
      "calling down bolts of lightning upon a settlement of hobbits.\n"+
      "   A towering figure of darkness, standing triumphant over the blasted "+
      "ruins of a dwarven city.\n");
   add_item(({"golden braziers","braziers","golden brazier","brazier"}),
      "Set upon golden tripods, there is one at each corner of the room, "+
      "spreading a bare minimum of light and an overabundance of incense.\n");
   add_item(({"archway"}),
      "It lies in the northern side of the room, leading to the main guildhall.\n");
   add_item(({"corner"}),
      "Each of the four contains a brazier.\n");
   add_item(({"carpet"}),
      "It looks quite comfortable.\n");
   INSIDE;
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   add_prop("_room_has_fire",1);
   add_exit(THANAR(joinroom),"north",0,-1);
   create_guild_support();
   create_skill_raise();
   set_up_skills();
}
wizinfo() {
   return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Anth.\n");
}
enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (!interactive(ob) || !closed)
      return;
   if (ob->query_wiz_level())
      write("WARNING!!! You should not be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("THANAR(joinroom)");
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
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}
query_closed() {return closed;}
set_up_skills() {
   sk_add_train(SS_WEP_SWORD, train_text(SS_WEP_SWORD), 0,0,40);
   sk_add_train(SS_AWARENESS, train_text(SS_AWARENESS), 0,0,50);
   sk_add_train(SS_SPELLCRAFT, train_text(SS_SPELLCRAFT), 0,0,30);
   sk_add_train(SS_LANGUAGE, train_text(SS_LANGUAGE), 0,0,30);
   sk_add_train(SS_APPR_MON, train_text(SS_APPR_MON), 0,0,40);
}
train_text(skill) {
   string what;
   switch(skill) {
      case SS_WEP_SWORD:
      what="use a sword in the service of Thanar";
      break;
      case SS_AWARENESS:
      what="notice your environment";
      break;
      case SS_SPELLCRAFT:
      what="use magical spells";
      break;
      case SS_LANGUAGE:
      what="understand and speak different languages";
      break;
      case SS_APPR_MON:
      what="appraise possible enemies";
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
   write("You settle down onto the carpet and slowly feel your mind make "+
      "contact with the will of Thanar, slowly you drift into "+
      "a meditative trance. You block off your sense and concentrate upon "+
      "the intracacies of your mind. You can now <estimate> your different stats "+
      "and <set> the learning preferences at your own desire. Just <rise> when "+
      "you are done meditating.\n");
   say(QCTNAME(TP) + " prostrates themself before the shrine to Thanar.\n");
}
int
gs_hook_rise()
{
   write("As if ascending from a great depth, you rise to the surface\n" +
      "of your consciousness. You exhale and feel very relaxed as\n" +
      "you get up and leave the massive ruby-red carpet.\n");
   say(QCTNAME(TP) + " rises from the shrine.\n");
}
