/* Mabon - gardener of MacDunn Abbey - gives info on incense herbs
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/18/98    Created
** Zima           6/13/98    Mabon is recipient of a letter in postm. tour
** Damaris        01/2001    Removed set_short
** Tapakah        08/2021    Refactored
*/

#pragma strict_types

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

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name(({"monk","manach","gardener"}));
  add_adj(({"dirty","brown-haired"}));
  set_long(
           "He is a dirty brown-haired human, his habit identifying him as "+
           "a monastic member of the Order of Sean-Rhian. His soiled "+
           "vestments, dirty face, and grass-stained hands must mean he "+
           "is a gardener.\n");

  set_manach_stats((40+random(60)));
  set_act_time(30);
  add_act("emote mumbles a silent prayer.");
  add_act("emote digs into the ground with this bare hands.");
  add_act("emote prunes one of the trees.");
  add_act("emote holds a blossom in his hand and inhales deeply.");
  add_act("emote pulls a vine of ivy off the wall.");
  add_act("emote pulls some small weeds from the grass.");
  add_act("emote inspects the leaves of a plant.");
  add_act("emote gazes with pride over the garden.");
  add_act("emote holds out his hands and seems to bless the garden.");
  add_act("emote glances at a sparrow flying between the trees.");
  add_act("emote digs a hole in the ground and plants a bulb.");
  set_default_answer(defans);
  add_ask("honeysuckle",
          "say It is a shrub which looks like a vine that usually grows up "+
          "around fences and posts in the countryside. It has twinned pink "+
          "flowers with a strong sweet fragrance.",1);
  add_ask(({"cedar","aromatic cedar"}),
          "say Cedar is an evergreen tree, rare in these parts, with "+
          "scales instead of needles like pine. It has a strong scent.",1);
  add_ask(({"uaine","uaine pine"}),
          "say Uaine is a rare pine tree, with black bark and long black "+
          "needles, very fragrant with plenty of sap.",1);
  add_ask(({"sap","amber"}),
          "say Sap amber forms on pines when the sap hardens on the bark. "+
          "It is very sticky. Uaine pine has much of it.",1);
  add_ask(({"lilac","lilacs"}),
          "say Ah, now that is a beautiful plant. It is not found in these "+
          "parts, except in gardens. It has a very strong scent, and its "+
          "purple flowers grow in bunches.",1);
  add_ask("saltpeter",
          "say It is a combustible powder, just a pinch will do in most cases. "+
          "Brathair Cimbaeth is the resident expert on that.",1);
  add_ask(({"cimbaeth","Cimbaeth","brathair cimbaeth","Brathair Cimbaeth"}),
          "say Cimbaeth is the abbey refector. He's usually in the kitchen.",1);
  add_ask(({"holy water",}),
          "say It is water blessed by one of our Brathairs. With skillful "+
          "intention, it can be sprinkled on things to produce various "+
          "effects.",1);
  add_ask("beatha",
          "say Ah, it has a red berry, easy to misidentify. It grows wild "+
          "in many places, like the plains.",1);
  add_ask(({"mortar","pestle"}),
          "say I am sure you can find one lying around the kirk somewhere.",1);
  add_ask(({"incense","recipe"}), "say See brathair Finegas about that.",1);
  add_ask(({"Finegas","finegas","brathair Finegas","brathair Finegas"}),
          "say He is an intructor of arcane arts in the abbey. He's usually "+
          "in the classroom.",1);
  add_ask(({"semion","Semion","abbot","abbot semion","abbot Semion"}),
          "say Abbot Semion is in charge of this kirk. He's usually in his "+
          "office in the abbey.",1);
  add_ask("herb",
          "say Ask me about a particular herb, and perhaps I can help you.",1);
  add_ask("herbs",
          "say I know a little about a few herbs. Ask me about a particular "+
          "one and maybe I can help you.",1);
  add_ask("garden",
          "say The garden is a source of herbs and beauty for the brathairs, "+
          "but is open to all who wish to seek.",1);
  add_ask("key",
          "say I have lost the garden key, I'm afraid I do'no have it.",1);
  add_ask("bark",
          "say The bark of some trees can be useful as herbs.",1);
  add_ask(({"wax","beeswax","bee","bees","beehive","hive","honey",
            "comb","honeycomb"}),
          "say I don't know of any bees around here. Perhaps in the "+
          "countryside?",1);
  add_ask(({"grave","martyrs","obelisk"}),
          "say Yes, the martyrs of old died rebuilding the kirk. They "+
          "sleep in the garden where the obelisk stands.",1);
  add_ask(({"vine","ivy","walls"}),
          "say Yes, the vines of ivy do cover the walls here. I try to "+
          "break a few branches away to prune them.",1);
  add_ask(({"mortar","pestle","mortar and pestle"}),
          "say I do not have one.",1);
  add_ask("grind","say Ah, well, examine a pestle closely, and with "+
          "the right skill, you can grind herbs into powders.",1);
}

