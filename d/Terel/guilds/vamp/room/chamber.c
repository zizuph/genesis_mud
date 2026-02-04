//-*-C++-*-
// file name:      chamber.c
// creator(s):     Lilith June 2008
// last update:    Lilith 1 Dec 2008
//                  making this a start room for BG who are not dhampir
// note: 
// bug(s):
// to-do:

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>
#include <composite.h>

public int check_allowed()
{
    if (member_array(TP->query_real_name(),
        OCC_MANAGER->query_allowed())>=0)
    {
        return 0;
    }

    if (IS_VAMP(TP))
    {
        return 0;
    }
    
    if (IS_BG(TP))
    {
        if (TP->query_master())
        {
            return 0;
        }
        write("You sense that you cannot progress in that direction until "+
        "you have a master.\n");
        return 1;
    }
    
    write("Despite your misgivings, you continue onward.\n");
    return 0;
}


public void configure_shelf(object shelf,int slot)
{
    string side;
    string position;
    shelf->set_name("sarcophagus");
    shelf->add_name("box");
    shelf->add_name("chest");
    shelf->add_name("rack");
    shelf->set_pname("sarcophagi");
    side="alabaster";
    shelf->set_allow_weapon(1);
    shelf->set_allow_armour(1);
    shelf->set_allow_nonglowing(1);
    shelf->set_allow_glowing(1);
    shelf->set_allow_misc(1);
    shelf->add_adj(side);
    shelf->set_short(side+" "+"sarcophagus");
    shelf->set_pshort(side+" "+"sarcophagi");
    shelf->set_long("This "+shelf->short()+" appears to have once housed "+
    "the deceased, but someone has emptied out the remains and turned it "+
    "into a storage container.\n");
    shelf->unset_no_show_composite();
    shelf->remove_prop(CONT_I_ATTACH);
}


public void create_shelves()
{
    object * shelves=({ });
    for (int i=0;i<1;i++)
    {
        object shelf=clone_object(OBJ_DIR+"rack");
        configure_shelf(shelf,i);
        shelf->move(TO);
        shelves=({ shelf }) + shelves;
    }
    set_shelves(shelves);
}
public void create_vamp_room()
{

    set_short("Central chamber");
    set_long("Cut like a gaping wound into the natural stone, this circular "+
        "chamber is empty save for the rubble of a ruined staircase and a "+
        "handful of sleeping pallets. "+
        "This area serves as an intersection between archways leading off "+
        "into the darkness that flows along the walls and fills the space "+
        "with the coppery scent of blood.\n");

    add_item(({"darkness"}), 
        "Ebbing and flowing through the chamber, this darkness has a "+
        "substance to it that no amount of light can conquer.\n");
    add_cmd_item(({"air", "blood"}), ({"smell", "sniff", "breathe"}),
        "The air is ripe with the coppery scent of blood.\n");
    add_item(({"archway", "archways", "arch", "arches"}), 
        "Which one did you wish to examine more closely? It looks like "+
        "there are three--no four--archways. Your eyes almost missed the "+
        "east one, partially concealed as it is by a pile of rubble. The "+
        "north, west, and south archways are clearly visible.\n");
    add_item(({"east archway"}), 
        "Peering over the pile of rubble, you catch a glimpse of stairs "+
        "leading upwards.\n");
    add_item(({"west archway"}), 
        "There is another chamber beyond the archway.\n");
    add_item(({"north archway"}), 
        "There is another chamber beyond the archway. Along either side "+
        "are some sleeping pallets.\n");
    add_item(({"south archway"}), "@@south_sense@@");
    add_item(({"rubble"}), 
        "This is the rubble of a ruined staircase that once lead up to the "+
        "balcony that encircles the room.\n");
    add_item(({"staircase", "ruined staircase"}), 
        "The staircase once lead up to the balcony that encircles this room.\n");
    add_item(({"balcony"}), "There is a balcony encircling this chamber, "+
        "but the stairway used to access it now lies in ruins on the floor.\n");
    add_item(({"floor"}), "The floor is level, unpolished and unadorned, the "+
        "same material as the rest of the room. Some pallets are lined up "+
        "along either side of the north archway.\n");
    add_item(({"pallet", "pallets", "mat", "mats", "woven mat", "woven mats",
        "sleeping pallet", "sleeping pallets"}), 
        "Thick woven mats serve as sleeping pallets. Most of them have bedrolls "+
        "on them.\n");
    add_item(({"bedroll", "bedrolls" }), 
        "Laying upon the sleeping pallets are bedrolls consisting of one "+
        "blanket, tightly rolled up into a cylinder.\n");

    add_item(({"ceiling"}), "The ceiling is quite high, about twice "+
        "the height of most of the other ceilings in this place.\n");
    add_item(({"wall", "walls", "stone", "natural stone"}), 
        "The walls are cut from the natural subterranean stone. They are "+
        "completely unadorned and unpolished.\n");
    add_item(({"slab", "slab of stone", "large slab"}),
        "It is a large slab of stone that is fitted in such a way that "+ 
        "only someone with preternatural strength could move it.\n");
   
//  add_prop(VAMP_CAN_START_HERE,1);

    /* Can't see?  You can still feel the ambiance */
    add_prop(ROOM_S_DARK_LONG, "The darkness here is like a living "+
        " thing. You can practically feel it pulsing along your skin.\n");
    add_prop(ROOM_S_DARK_MSG, "The darkness flowing around you is much "+
        "too thick to");
    
    add_exit("crypt","south");
    add_exit("library","west");
    add_exit("lowertomb","north", "@@check_allowed@@");
    add_exit("m6","east","@@check_vampire2@@");
    add_exit("upperchamber","up","@@check_vampire@@",1,1);

    object b;

    setuid();
    seteuid(getuid());



//    create_shelves();
    
}

public int check_vampire2()
{
        write("You follow the steps up and move the stone "+
            "block out of your way.\n");
        
        return 0;
}


public int check_vampire()
{
        write("You easily leap up onto the balcony through the opening "+
            "left by the fallen staircase.\n");
        
        return 0;

}


/* add_item */
public string 
south_sense()
{
    string see_long, reg_long, mem_long;
    reg_long = "Peering into the deep darkness beyond the south archway, "+
            "you feel as if a giant hand is pressing down on you.  "+ 
            "Whatever lies beyond, it fills you with a sense of foreboding.\n";        
    if (IS_VAMP(TP))
        mem_long = "You feel the power of the Eldest emanating from the "+
            "south. The darkness seems to pulse with the richness of "+
            "His pervasive presence.\n";
    if (IS_BG(TP))
        mem_long = "Your flesh tingles with apprehension as you sense "+
            "the brooding presence of the Eldest emanating from the south.\n";
    if (mem_long)
        see_long = mem_long;
    else    
       see_long = reg_long;
    return see_long;
}
