// Alebard - librarian
//
//   Coder         Date                Action
// -------------- -------- ----------------------------------------------
// Zima           7/20/98  Recoded
//
#include "defs.h"
inherit  SR_NPC+"monkbase";
inherit  SR_NPC+"monk_specatck";
inherit  SR_NPC+"spintro";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
 
#define  VEST (({"robe","cincture","tonsure","scapular"}))
 
void   equip_me() { vest_me(VEST); }
string defans()
{
   command("say I can say nothing of that.");
   return "";
}
 
void setup_manach()
{
    set_name("alebard");
    add_name(({"monk","manach","librarian","caretaker"}));
    set_title("the Manach of Sean-Rhian and Librarian of Seanchan Tor Abbey");
    set_adj(({"plump","studious"}));
    set_race_name("human");
    set_long(
        "He is a plump studious human, his habit "+
        "identifying him as a monastic member of the Order of Sean-Rhian. "+
        "He is the caretaker of the abbey's libraries.\n");
 
    add_prop(NPC_M_NO_ACCEPT_GIVE,
    "says: I may not accept gifts from you, but you may Return a writing.");
    set_manach_stats((60+random(40)));
    set_act_time(30);
    add_act("emote places a scroll in the cabinet.");
    add_act("emote takes a scroll from a cabinet and peruses it.");
    add_act("emote mumbles to himself.");
    add_act("say Wisdom paves the path to Harmony.");
    add_act("say Mother earth gives us many gifts.");
    add_act("say To master language is to master the mind.");
    add_act("emote glances through the books in the cabinets.");
    add_act("emote bows momentarily for a short prayer.");
    add_act("emote smiles enlightenedly while reading.");
    add_act("emote straightens some scrolls in a cabinet.");
    add_act("emote dusts off some books with his scapular.");
    add_act("emote stacks some manuscripts in the cabinet.");
    add_act("say Great wisdom can be found here by those who seek.");
    add_act("say Immersion in the writings is necessary for a saggart.");
 
    set_default_answer("@@defans");
    add_ask(({"cabinet","cabinets","about cabinets","books","scrolls",
              "documents","writings","for writings","for documents"}),
              "say The cabinets contain reserved writings which only "+
              "I can give you. Ask me for help if you need it.",1);
    add_ask(({"help","for help"}),"@@ask_help",1);
}
 
string ask_help()
{
   if (TP->is_saggart())
      {
      command("say I can lend you some of the writings in the cabinet.");
      command("say But you must Return them.");
      command("say If you need a writing, just Borrow its title.");
      return  "say You may also list the titles you can borrow.";
      }
   return "You may not read these writings, infidel!";
}
 
void create_khalakhor_human()
{
   seteuid(getuid());
   setup_manach();
}
