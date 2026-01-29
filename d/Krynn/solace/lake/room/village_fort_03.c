/*
 * Fortess room in the Toron minotaur village  
 * Made to inherit village_base_in.
 * Made y Cherek Jan 2007.
 */
 
#include "../local.h"

inherit VILLAGE_BASE_IN;

object kadez;

void
reset_toron_room()
{
    if (!objectp(kadez))
    {
    
        kadez = clone_object(NPC + "minotaur_kadez.c");
    
        kadez->move(TO, 1); 
    
        tell_room(TO, "A minotaur arrives.\n", kadez);     
    }
}

void
create_toron_room() 
{
    set_location("FORT");
    set_short("Inside a throne room in a wooden fortress");
    set_start_desc("You stand inside a throne room in the northern " +
                   "part of a fortress made almost entirely of wood. ");
    set_long_desc("This room is as beautiful as it is intimidating. " +
                  "A very fine brown rug leads from the entrance " +
                  "and all the way across the room until it reaches " +
                  "an enormous throne made of finest wood. The walls " +  
                  "are covered with deep green tapestries everywhere " +
                  "except right behind the throne where a painting " +
                  "of a minotaur hangs, overlooking the entire room. " +
                  "Two large torches at either side of the throne " +
                  "enlightens the room while casting ghostly shadows. " +
                  "You cannot help feeling small in here. There is " +
                  "a doorway in the south wall. ");
                  
    add_prop(OBJ_I_LIGHT, 5);

    add_item("fortress",
             "You can smell the fresh wood it is made of. \n"); 

    add_item("wood",
             "Every peice of wood is sleek and well-polished. \n"); 
             
    add_item(({"wall", "walls", "tapestry", "tapestries"}),
               "The walls are almost completely covered in deep " +
               "green tapestries. \n");

    add_item(({"rug", "brown rug", "fine rug", "fine brown rug"}),
               "It seems to be made of a very expensive fabric. " +
               "Two intricate golden stripes follow each side of " +
               "the rug. \n");
               
    add_item("fabric",
             "It is surprisingly soft in this otherwise coarse " +
             "place. \n");
             
    add_item("stripes",
             "They are made of golden thread. \n");             
             
    add_item("painting",
             "Ah rather large painting of a dangerous brutal " +
             "male minotaur. He looks proud yet slightly rugged " +
             "and tired. He sits on a large wooden throne, quite " +
             "similar to the one in this room. It is actually " +
             "possible this painting was made here in this very " +
             "room. You notice a plaque below the frame. \n");

    add_item("plaque",
             "It is made of gold with engraved text. \n");

    add_item(({"torch", "torches", "large torch", "large torches", "flames"}),
               "They are almost the size of bonfires. " +
               "They seem practically impossible to extinguish " +
               "and will probably burn for a very long time. \n");

    add_item(({"throne", "wooden throne"}),
               "This throne must be the work of a real artist " +
               "rather than a carpenter. It actually seem to " +
               "have been carved from one single piece of wood " +
               "and the detail is amazing. \n");
               
    add_item(({"shadows", "ghostly shadows"}),
             "They dance just like the flames. \n");               

    add_item(({"doorway", "entrance"}),
             "It leads back into the main hallway. \n");

    add_item("throne room",
             "It is a very impressive room. \n");
             
    add_cmd_item("torch","extinguish","You do not think you " +
                 "even could carry enough water to put out these " +
                 "enormous torches. .\n"); 

    add_cmd_item("fire","extinguish","You do not think you " +
                 "even could carry enough water to put out these " +
                 "enormous torches. .\n");

    add_cmd_item("plaque","read","Kadez de-Toron, 47th " +
                 "Chieftain of the Toron tribe of Kothas.\n");

    add_cmd_item("text","read","Kadez de-Toron, 47th " +
                 "Chieftain of the Toron tribe of Kothas.\n");

    add_exit(ROOM + "village_fort_01","south",0,3);  

    reset_room();
}

/*
 * Function name: make_kadez_do_dam
 * Description  : Calls Kadez if he is present and makes him
 *                do damage against "bouncers".
 */
void make_kadez_do_dam(object ob, object kadez)
{ 
    if(present(ob, TO))
    {
        kadez->bouncer(ob, kadez);
    }
}

/*
 * Function name: enter_inv
 * Description  : Checks every player who enters and if Kadez
 *                is present.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    
    if(interactive(ob))
    {   
        if(present(kadez, TO))	 
        {
            set_alarm(1.0, 0.0, &make_kadez_do_dam(ob, kadez));
        }
    }
}
