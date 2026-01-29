/* Finegas - teacher in the class room (adv guild)
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Damaris        01/2001    Removed set_short
** Tapakah        08/2021    Refactored
*/
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"

inherit  SR_NPC+"monkbase";
 
#define  VEST (({"robe","cincture","tonsure","scapular"}))
 
void
arm_me ()
{
  vest_me(VEST);
}
 
string
ask_recipe ()
{
  object tp=this_player();
  if (tp->query_prop(SEMIONS_BLESSING)) {
    (clone_object(SR_OBJ+"increcipe"))->move(this_object());
    command("emote opens a book and takes a piece of parchment from it.");
    command("give recipe to "+lower_case(tp->query_name()));
    command("drop recipe");
    command("say There you are. Follow it precisely.");
  }
  else
    command("say Abbot Semion has not given you this task. Ask him first.");
  return "";
}

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name(({"monk","manach","instructor"}));
  set_adj(({"stern","long-faced"}));
  set_long(
           "He is a stern long-faced human, his habit "+
           "identifying him as a monastic member of the Order of Sean-Rhian. "+
           "He is one of the abbey's instructors of the arcane arts.\n");
 
  add_prop(NPC_M_NO_ACCEPT_GIVE,1);
  set_manach_stats((60+random(40)));
  set_act_time(30);
  add_act("emote places a scroll on the shelves.");
  add_act("emote takes a scroll from a shelf and peruses it.");
  add_act("emote cleans a mortar and places it on the shelves.");
  add_act("emote mumbles to himself.");
  add_act("emote scrapes wax off his fingers.");
  add_act("say Wisdom paves the path to Harmony.");
  add_act("say Mother earth gives us many gifts.");
  add_act("say To master language is to master the mind.");
  add_act("emote sniffs condescendingly.");
  add_act("say Are you here to learn or to waste my time?");
  add_act("say I can teach you much, for a small donation of course.");
  add_act("emote glances through the books in the shelves.");
  add_act("emote bows momentarily for a short prayer.");
  set_default_answer(defans);
  add_ask(({"task","job","quest","chore","for task","for job",
            "for quest","for chore"}),
          "say See Abbot Semion about that.",1);
  add_ask(({"book","books","about books","for book","for books",
            "about book"}),
          "say Books contain words of wisdom and of folly. Beware!",1);
  add_ask(({"library","about library","where library","where is library"}),
          "say The library is down the hall.",1);
  add_ask(({"learn","improve","teach","teaching","lesson","lessons",
            "about learning","about teaching","about lesson",
            "help","alchemy","arcane arts","skills","arts",
            "about lessons","for lesson","for lessons","about skills"}),
          "say Try 'improve' and 'learn' lad.",1);
  add_ask(({"recipe","for recipe","incense recipe","for incense recipe"}),
          "@@ask_recipe",1);
  add_ask(({"incense","for incense","about incense"}),
          "say It is a combustible powder which gives off a powerful "+
          "pleasing aroma when burnt. I have a recipe for it.",1);
  add_ask(({"uaine pine","pine","sap","amber","bark","cedar","lilac",
            "aromatic cedar","honeysuckle","herb","herbs"}),
          "say See brathair Mabon about that.",1);
  add_ask(({"saltpeter","about saltpeter","for saltpeter"}),
          "say See brathair Cimbaeth about that.",1);
  add_ask(({"holy water","for holy water"}),
          "say It can be found in the kirk if you look for it.",1);
  add_ask(({"mortar","pestle","vial","for mortar","for pestle","for vial"}),
          "say I don't have one I can lend you, though you might find "+
          "one somewhere in the abbey.",1);
  add_ask(({"mabon","Mabon","brathair mabon","brathair Mabon"}),
          "say He is the abbey gardner, so you can guess where to "+
          "find him.",1);
  add_ask(({"cimbaeth","Cimbaeth","brathair Cimbaeth","brathair cimbaeth"}),
          "say He is the abbey refector. He's usually in the kitchen.",1);
  add_ask(({"semion","Semion","abbot","Abbot","abbot semion","Abbot Semion"}),
          "say He is usually in his office in the abbey.",1);
  seteuid(getuid());
}
