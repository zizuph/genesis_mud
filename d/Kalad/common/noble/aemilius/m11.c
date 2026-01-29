inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    set_short("In the kitchen of the House of Aemilius");
    set_long("You now find yourself inside a wonderful smelling "+
    "room. Fresh cooking smells waft from the many pots that are "+
    "hanging over the many fires in this kitchen. Tables "+
    "are scattered about the room with ingredients on them. Sacks "+
    "of flour and barrels of salt and water lay about. To the east "+
    "you see what appears to be the dining room, while south and southeast "+
    "there are a short halls.\n");
  
    add_item("pots","Huge iron pots full of boiling water.\n");
    add_item("fires","Many fire pits are set into the walls of "+
    "this room, where blazing fires burn to cook the food.\n");
    add_item("tables","Dirty and messy tables with choped meats and "+
    "vegtables on them.\n");
    
    INSIDE;
    add_exit(NOBLE(aemilius/m6),"east",0,-1,-1);
    add_exit(NOBLE(aemilius/m10),"south",0,-1,-1);
    add_exit(NOBLE(aemilius/m7),"southeast",0,-1,-1);
    
    clone_object(NOBLE(kstuff))->move(TO);
    clone_object(NOBLE(kstuff2))->move(TO);

   
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/cook));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

