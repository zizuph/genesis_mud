// St. Keophen Abbey - Cloister (garden)
//
// History:
// Date         Coder       Action
// ----------   ----------- ----------------------------------
// 11/12/98     Zima        Created
//
//
#pragma strict_types
#include "defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
 
inherit "/std/room";
inherit HERBSEARCH;
string  *herbs;
string  extra="";
 
public void setup_kgard_herbs()
{
    herbs = HERBMASTER->query_herbs(({TERRAIN_GARDEN,}));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({"grass","here"}), 2);
}
 
public void reset_room() { set_searched(0); }
 
void setup_cloister_room(string where)
{
   set_short("In the cloister of an old stone abbey");
   set_long("You are "+where+" of the cloister of an old stone "+
            "abbey, a large "+
            "square garden protected by the high abbey walls on its "+
            "four sides. A large fountain stands in the center of the "+
            "cloister grounds, narrow cobblestone paths radiating "+
            "from its base in all directions across the well-kept lawn "+
            "of short green grass. Large arches centered in the stone "+
            "walls mark the four entrances to the cloister, the south "+
            "leading through the base of a high belltower where a gateway "+
            "guards the abbey's main entrance. "+extra+"\n");
 
   add_item(({"cloister","garden"}),
      "It is a square lawn enclosed by the high stone walls of the abbey, "+
      "with a fountain in the center, cobblestone pathways crossing "+
      "the well-kept grass, with arched entrances centered in the stone "+
      "walls on the north, south, east and west sides.\n");
   add_item(({"abbey","walls","structures","structure","wall"}),
      "They abbey consists of four main structures situated around the "+
      "square cloister, the high stone walls forming a protective frame "+
      "around the well-kept lawn. Arched entrances lead into the abbey "+
      "on the west, east and north sides of the cloister, while another "+
      "leads outside the abbey beneath a high belltower situated in the "+
      "center of the south wall.\n");
   add_item(({"statue","fountain"}),
      "There is a stone fountain centered in the middle of the cloister, "+
      "consisting of a large round pool made of stone. A regal statue "+
      "stands in the center of the fountain. You could get a better look "+
      "if you got a little closer.\n");
   add_item(({"path","paths","pathway","pathways","cobblestones",
      "cobblestone"}),
      "Eight cobblestone pathways radiate from the fountain in the center "+
      "of the cloister, crossing the lush grass of the the lawn, leading "+
      "to the four arched entrances and the four corners of the cloister.\n");
   add_item(({"grounds","lawn","grass"}),
      "The grounds of the cloister are carpeted with a lawn of well  "+
      "manicured green grass crossed by the cobblestone paths which "+
      "stretch out from the central fountain.\n");
   add_item(({"arch","arches","entrance","entrances"}),
      "There are four entrances to the cloister of the abbey, one on each "+
      "of its four sides, centered in the surrounding stone walls. Each "+
      "is marked by a high arch, the one to the south leading beneath "+
      "a tall belltower where a gate guards the abbey's main entrance.\n");
   add_item(({"belltower","bell tower","tower"}),
      "A high stone belltower rises in the center of the southern wall "+
      "which frames the cloister, the point of its peaked roof topped with "+
      "a pole on which is set a tricircum emblem gleaming like gold. The "+
      "main entrance to the abbey from the outside passes through the "+
      "tower's base to the south, guarded by a gate.\n");
   add_item(({"gate","gateway"}),
      "A gate made of thick iron poles guards the entrance to the abbey, "+
      "set in the walls of the base of the belltower along the cloister's "+
      "south side. You could get a better look if you got closer.\n");
   add_item(({"emblem","tricircum","tricircum emblem"}),
      "A large gold emblem is placed atop a golden pole on the peak of "+
      "the roof of the belltower. It is composed of three large rings "+
      "joined together in the shape of a shamrock. It gleams brightly "+
      "even in clouded sunlight.\n");
 
   setup_kgard_herbs();
   add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);
}
 
void create_room()
{
   set_short("Cloister base room");
   set_long("Cloister base room.\n");
}
