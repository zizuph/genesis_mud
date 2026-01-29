/*
**  MCLUB - Memorial Shrine, Sanctuary (Chapel)
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       4/7/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"
#include "../specials/check_memlist.c"
#define  INCENSE_BEAT 60.0
int incensing=0;
#define IncenseStreaming (({                                               \
  "Incense streams from the censor filling the room with its aroma",       \
  "Incense continues to stream from the censor thickening the cloud",      \
  "Incense boils from the censor dancing in the rays of sunlight",         \
  "Incense rises from the censor saturating you with its sweet smell",     \
  "Incense continues to issue forth from the vents of the censor",         \
  "Incense spouts from the censor in balls of aromatic smoke",             \
  "Incense gushes from the censor in rivulets of smoke",                   \
  "Incense continues to boil from the censor in elegant patterns of smoke",\
  "Incense pours from the censor perfuming all it touches",                \
  "Incense streams from the censor mystifying the sanctuary"}))
 
#define IncenseRising (({                                                  \
  "Incense rises gracefully from the censor in thinning whisps",           \
  "The cloud begins to thin as the incense burns low",                     \
  "Whisps of incense rise from the vents of the censor",                   \
  "Incense whisps gracefully from the silver censor",                      \
  "Incense rises slowly from the dieing embers of its ash",                \
  "Thinning plumes of incense rise solemnly from the censor",              \
  "Incense smokes lightly from the silver censor"}))
 
#include "shsanct.ext"
 
 
create_room() {
   set_short("The sanctuary of a shrine");
   set_long(
      "Sunlight filters through the stained-glass windows of "+
      "this modest but solemn chamber, scattering rays of colored "+
      "light throughout. This seems to be the sanctuary or chapel "+
      "of the stone shrine, a place filled with ancient memories. " +
      "A wooden altar stands near the east wall, beneath the "+
      "largest of the hand-crafted windows, the focal point of the "+
      "sanctuary. A copper brazier sits on one side of the "+
      "altar, while a silver censor sits atop a slender tripod on "+
      "the other. A few rows of wooden benches face the front "+
      "of the sanctuary, running between the windows on the north "+
      "and south walls. A large arch marks an entrance to the "+
      "central chamber of the shrine to the west.\n");
 
   add_item(({"sunlight","light"}),
      "It shines through the windows of colored glass, casting "+
      "somber spots of color about the chamber.\n");
   add_item(({"windows","window"}),
      "Three stained-glass windows adorn the sanctuary, one on each "+
      "of the northern, southern and eastern walls. Perhaps you "+
      "should take a closer look at each.\n");
   add_item(({"north window","northern window","window on north wall",
      "window on the north wall","window on northern wall",
      "window on the northern wall","first window"}),
      "@@exa_window1");
   add_item(({"east window","eastern window","second window","window on east wall",
      "window on the east wall","window on eastern wall","large window",
      "largest window", "window on the eastern wall","third window"}),
      "@@exa_window2");
   add_item(({"south window","southern window","window on south wall",
      "window on the south wall","window on southern wall",
      "window on the southern wall","third window"}),
      "@@exa_window3");
   add_item(({"chamber","sanctuary","chapel"}),
      "The sanctuary is built of smooth stones of all shapes and sizes, "+
      "its walls a fortress against any enemies who would intrude. The "+
      "ceiling is covered with plaster, upon which a fresco is painted, "+
      "while the floor is set with a matrix of clay tiles.\n");
   add_item(({"ceiling","roof","fresco"}),"@@exa_fresco");
   add_item(({"wall","walls"}),
      "The walls are constructed of irregular stones of various sizes "+
      "and shapes. They seem to be very natural, smoothed by centuries "+
      "of water and wind. The fact that they fit together so well "+
      "seems amazing.\n");
   add_item(({"floor","tile","tiles","matrix"}),
      "The floor of the sanctuary is covered with gray tiles etched "+
      "with an intricate blue frame around each. They are set into "+
      "the floor in an orderly matrix of columns and rows.\n");
   add_item("altar",
      "It is a long narrow altar made of antique wood, supported by "+
      "two hand-carved pedestals on either end. An emblem has been "+
      "etched on its polished surface, while an inscription is "+
      "written along the front edge.\n");
   add_item(({"pedestal","pedestals"}),
      "The two pedestals of the altar are made of wood and carved "+
      "into the likeness of coiled serpent-like creatures.\n");
   add_item(({"inscription"}),
      "It is written across the front edge of the altar facing the "+
      "west.\n");
   add_cmd_item("inscription","read","Remember the Ancient Ones\n");
   add_item("emblem",
      "Carved into the top of the altar, the emblem is that of a "+
      "four-pointed star centered in a circle.\n");
   add_item("brazier",
      "It is a large copper container, bowl-like in shape, cast with "+
      "runes on its outer surface. A large blue flame burns solemnly "+
      "from it, warming the cold stones of the chamber.\n");
   add_item("flame",
      "The large blue flame burns quietly and evenly in the brazier, "+
      "giving the sanctuary a warm ambieance.\n");
   add_item("censor","@@exa_censor");
 
   add_item("tripod",
      "The tripod is made of three long rods made of silver, joined "+
      "together at the top providing a stand for the censor.\n");
   add_item("benches",
      "The simple wooden benches run north to south, bisected by "+
      "an aisle leading to the altar.\n");
   add_item("aisle","It cuts between the benches from the entrance "+
       "to the altar.\n");
 
   add_item(({"arch","entrance","central chamber"}),
      "The large wooden arch rises to a gothic point, "+
      "polished and well-oiled. It demarks the entrance to the central "+
      "chamber to the west.\n");
 
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"shtemple","west","@@west");
}
 
string exa_window1() {
   string desc="The window on the northern wall is a mosaic of stained "+
               "glass portraying a large tree, the canopy of its branches "+
               "and leaves flowing out of the view of the scene. The "+
               "depiction is framed with squares of dark blue glass. ";
   if (InMClub(this_player()))
      desc=desc+"You recognize it as the Ancient Tree.\n";
   else
      desc=desc+"\n";
   return desc;
}
 
string exa_window2() {
   string desc="The mosaic of colored glass in the second window depicts "+
               "a mysterious ancient human, clothed in a long white robe "+
               "and a silver mantle. His face is hidden beneath a deep "+
               "cowl, and he holds a book of prophecy in his hand. ";
   if (InMClub(this_player()))
      desc=desc+"You recognize the figure as Mecien the Prophet of Mystery.\n";
   else desc=desc+"\n";
   return desc;
}
 
string exa_window3() {
   string desc="The stained-glass window on the southern wall depicts "+
               "a robust many-petaled red flower in full bloom. ";
   if (InMClub(this_player()))
      desc=desc+"You recognize it as Liyil.\n";
   else desc=desc+"\n";
   return desc;
}
 
string exa_censor() {
   string desc = "It is a silver censor, a bowl with a vented lid, used "+
                 "to burn incense during ceremonies. ";
   object incense=present(INCENSE_CLOUD,this_object());
   if ((incense)||(incensing))
      desc=desc+"A bitter-sweet aroma pervades the air as incense "+
                "streams from the censor filling the sanctuary.\n";
   else
      desc=desc+"\n";
   return desc;
}
 
string read_inscription() {
   if (InMClub(this_player()))
      return "The words in the ancient language read: Glory Wisdom Truth.\n";
   else
      return "You are unable to read the ancient writing.\n";
}
 
string exa_fresco() {
   string desc="The ceiling is plastered with a fresco depicting a "+
               "mysterious creature with the head of a horned-goat "+
               "with the body of a green-scaled fish in place of its "+
               "legs. It holds three evergreen leaves in its hand. ";
   if (InMClub(this_player()))
      desc=desc+"You recognize the creature as the Capricorn, Keeper "+
                "in the grotto.\n";
   else desc=desc+"\n";
   return desc;
}
 
int west() {
   object TP=this_player();
   object kneeling=present(KNEELING_OBJ,TP);
   object layobj=present(MCLUB_LAYOBJ,TP);
 
   if (kneeling) {
      write("You are kneeling. You must rise first.\n");
      return 1;
      }
   if (layobj) layobj->remove_object();
   return 0;
}
 
 
void init() {
   ::init();
   add_action("kneel","kneel");
   add_action("do_remember","Remember");
   add_action("induct","induct");
   add_action("break_oath","break");
   add_action("rise","rise");
   add_action("load","load");
   add_action("lay","lay");
}
