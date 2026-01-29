//
// Laihder - teacher in the class room (guild instructor) in MacDunn abbey
//
// Date       Coder           Action
// ---------  --------------  -------------------------------------------
// 7/19/98    Zima            Created
// Damaris        01/2001    Removed set_short
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
   command("say I am afraid I can not answer that, my child.");
   return "";
}
 
void setup_manach()
{
    set_name("laihder");
    add_name(({"monk","manach","instructor"}));
    set_title("the Manach of Sean-Rhian and Master of the Arcane Arts");
    set_adj(({"stern","balding"}));
    set_race_name("human");
    set_long(
        "He is a stern balding human, his habit "+
        "identifying him as a monastic member of the Order of Sean-Rhian. "+
        "He is one of the abbey's top instructors of the arcane arts.\n");
 
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    set_manach_stats(110);
    set_act_time(45);
    add_act("emote mumbles to himself.");
    add_act("say Wisdom paves the path to Harmony.");
    add_act("say Mother earth gives us many gifts.");
    add_act("say To master language is to master the mind.");
    add_act("emote sniffs condescendingly.");
    add_act("say I can teach you much my child.");
    add_act("emote thumbs through a book in his hand.");
    add_act("emote bows momentarily for a short prayer.");
    set_default_answer("@@defans");
}
 
void create_khalakhor_human()
{
   setup_manach();
   seteuid(getuid());
}
