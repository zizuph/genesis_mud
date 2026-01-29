// file name: quar1
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();
object guard, female;

void
create_room()
{
   quar_long("This place seems to be a sort of study, with "
            +"a couple of writing tables and sitting "
            +"chairs. Some effort has been made to make "
            +"this room comfortable, but it fails for the "
            +"most part. Ragged tapestries hang on the "
            +"walls with bright swirling patterns. An open "
            +"doorway leads south into a hall.");
   AI(({"desk","desks","table","tables"}),"There are two "
            +"tables situated against the east and west walls, "
            +"both angled for writing.\nThe tables are "
            +"both empty.\n");
   AI(({"chair","chairs"}),"The chairs in the room are hard "
            +"wooden frames, with some thin cloth placed over "
            +"them to make them a bit more comfortable.\n");
   AI(({"tapestry","tapestries"}),"The tapestries are hung on "
            +"the east and west walls. They seem to be fairly "
            +"old and faded, and look a bit out of place here. "
            +"There are strange swirling designs on the "
            +"tapestries, and in the center is a symbol.\n");
   AI(({"design","designs","symbol","symbols"}),"In the "
            +"center of the swirling designs on the "
            +"tapestries is a symbol of a long white snake, "
            +"curled into a perfect circle.\n");

   hall_exit("6","south");

   reset_room();
}

void
reset_room()
{
   if(!guard)
     {
        guard = clone_object(MON+"guard");
        guard->arm_me();
        guard->move(TO);
        guard->add_act("emote sits at the west desk and begins "
               +"composing a letter.");
        guard->add_act("emote stares at the west tapestry "
               +"in silence for a short while.");
        guard->add_act("hmm");

     }
   if(!female)
     {
        female = clone_object(MON+"g_infidel");
        female->arm_me();
        female->move(TO);
        female->add_act("emote sits at the east desk and begins "
               +"composing a letter.");
        female->add_act("emote stares at the east tapestry "
               +"for a moment, lost in thought.");
        female->add_act("emote runs her hand along the "
               +"symbol in the center of the east tapestry.");
     }
 
}
