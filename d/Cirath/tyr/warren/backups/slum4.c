/* slum4: A place for the dregs of the earth to rob you.
   Casimir, March 2001:

   Added Avena (/athas/gladiator/guruquest/Avena). She must
   be defeated as part of the gladiator guru quest.
 */

inherit "/std/room";

#include "/d/Cirath/tyr/warren/defs.h"

//Global variables
object Npc; //the slum mob
object Avena; //object pointer to Avena

void reset_room()
{
    if(!objectp(Npc))
    {
	Npc=clone_object (TYR_NPC+"poor_mob");
	Npc->move_living ("into the room", TO);
    }

    //Added by Casimir
    if(!objectp(Avena))
    {
        Avena = clone_object("/d/Cirath/athas/gladiator/guruquest/Avena");
        Avena->move_living ("into the room", TO);
    }
}

void create_room()
{
    set_short("northern slums");
    set_long ("Possibly in the best condition of any area of slum in Tyr, "+
              "if such is possible, the north benefits from "+
              "close proximity to the main square. A road lies to the "+
               "northwest, while you can venture into deep "+
              "urban blight south and southwest.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_WARREN+"rd_cw_06.c", "northwest", 0, 1);
    add_exit(TYR_WARREN +"slum3.c", "southeast", 0, 1);
    add_exit(TYR_WARREN +"slum1.c", "south", 0, 1);

    reset_room();
}


