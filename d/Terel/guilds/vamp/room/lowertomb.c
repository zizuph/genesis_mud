//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>
#include <composite.h>

/*
public void configure_shelf(object shelf,int slot)
{
    string side;
    string position;
    shelf->set_name("sarcophagus");
    shelf->add_name("box");
    shelf->add_name("chest");
    shelf->add_name("rack");
    shelf->set_pname("sarcophagi");
    switch (slot)
    {
        case 2:
            side="granite";
            shelf->set_allow_weapon(1);
            shelf->set_allow_armour(1);
            shelf->set_allow_nonglowing(1);
            break;
        case 1:
            side="marble";
            shelf->set_allow_weapon(1);
            shelf->set_allow_armour(1);
            shelf->set_allow_glowing(1);
            break;
        case 0:
            side="sandstone";
            shelf->set_allow_glowing(1);
            shelf->set_allow_nonglowing(1);
            shelf->set_allow_misc(1);
            break;
    }
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
    object heap=clone_object(OBJ_DIR+"rack");
    heap->set_allow_misc(1);
    heap->set_allow_armour(1);
    heap->set_allow_weapon(1);
    heap->set_allow_glowing(1);
    heap->set_allow_nonglowing(1);
    heap->move(TO);
    heap->set_name("heap");
    heap->set_short("heap");
    heap->set_long("This is a heap of undesirable items, unused and left "+
    "alone in the corner of the chamber.\n");

    object * shelves=({ });
    for (int i=0;i<3;i++)
    {
        object shelf=clone_object(OBJ_DIR+"rack");
        configure_shelf(shelf,i);
        shelf->move(TO);
        shelves=({ shelf }) + shelves;
    }
    set_shelves(shelves);
}
*/

public void create_vamp_room()
{

    set_short("Eternal resting place");
    set_long("Once a place of eternal rest, this tomb now shelters the living. "+
        "Even in its neglected state, it is obvious that no expense was spared "+
        "in the building of it. "+
        "The floors, walls, and ceiling are lined with marble carved in a "+
        "variety of bas reliefs. Faint traces of metal still glimmer in the "+
        "funereal seal above the tomb's entrance. "+
        "Twin sarcophagi, long ago opened and deprived of their contents, "+
        "dominate the center. Pallets and bedrolls line the floor along the "+
        "walls, the only concessions to comfort for those who reside here. "+
        "\n");
    add_item(({"floor", "floors" }), 
        "The marble of the floor is scuffed and worn.\n");
    add_item(({"wall", "walls" }), 
        "Covered in marble from floor to ceiling, there are bas reliefs "+
        "on all the walls except the south one, which has a seal carved "+
        "above the doorway.\n");
    add_item(({"ceiling" }), "The ceiling is lined in marble. There is a "+
        "jagged hole or crack in the ceiling.\n");
    add_item(({"hole", "hole in ceiling", "hole in the ceiling", "jagged hole", 
        "crack", "crack in ceiling", "crack in the ceiling"}), 
        "The beautiful marble of the ceiling is marred by a large hole. "+
        "Your eyes cannot penetrate the darkness beyond.\n");
    add_item(({"bas relief", "bas reliefs", "bas", "relief", "reliefs", 
        "panel", "panels"}), 
        "There are three bas relief panels on the north, east and west walls.\n");
    add_item(({"north wall", "north", "north bas relief", "north panel" }), 
        "This bas relief is directly opposite the entrance to the tomb. "+
        "Into it is carved a hand which is cradling a limp body. "+
        "Above it is a starburst depicting the sun's rays falling upon "+
        "the deceased.\n");
    add_item(({"starburst", "rays", "sun"}), 
        "It has been carved into the marble panel to the north. It seems "+
        "to symbolize a god-figure, or at least, comfort after death.\n");
    add_item(({"hand", "hand cradling a limp body", "body", "limp body"}),
        "The north panel depicts a large hand cradling a limp body, "+
        "presumably dead.\n");
    add_item(({"south wall", "south", "door", "doorway", "entrance" }),
        "There is an open doorway with a funereal seal craved into the "+
        "marble above it.\n"); 
    add_item(({"funeral seal", "seal", "funereal seal" }), 
        "It depicts two figures, one living, one dead, divided from each "+
        "other by a lightning bolt. There is a faint gold patina on it.\n");
    add_item(({"gold patina", "patina", "gold leaf"}), 
        "Gold leaf was applied to the funereal seal "+
        "over the doorway. Most of it appears to have faded with time.\n");
    add_item(({"east wall", "east", "east bas relief", "east panel" }), 
        "This panel depicts various scenes from the life of a male.\n");
    add_item(({"west wall", "west", "west bas relief", "west panel" }), 
        "This panel depicts various scenes from the life of a female.\n");
    add_item(({"marble"}), 
        "Every surface of this room is covered in finely-veined white marble.\n");
    add_item(({"metal", "traces" }), 
        "The metallic traces are most apparent on the funeral seal above the door.\n");
    add_item(({"pallet", "pallets", "mat", "mats", "woven mat", "woven mats",
        "sleeping pallet", "sleeping pallets"}), 
        "Thick woven mats serve as sleeping pallets. Most of them have bedrolls "+
        "on them.\n");
    add_item(({"bedroll", "bedrolls" }), 
        "Laying upon the sleeping pallets are bedrolls consisting of one "+
        "blanket, tightly rolled up into a cylinder.\n");
    add_item(({"darkness"}), 
        "Ebbing and flowing through the chamber, this darkness has a "+
        "substance to it that no amount of light can conquer.\n");
    add_cmd_item(({"air", "blood"}), ({"smell", "sniff", "breathe"}),
        "The air is ripe with the coppery scent of blood.\n");
    add_cmd_item(({"bedroll", "bedrolls" }), ({"unroll", "spread", "open"}), 
        "You unroll a bedroll and spead it out on a sleeping pallet.\n");
    add_cmd_item(({"bedroll", "bedrolls", "on bedroll", "down on bedroll" }), 
        ({"sleep", "rest", "lay"}), 
        "You lay down on the bedroll and rest comfortably for a time.\n");
    add_cmd_item(({"pallet", "pallets", "on pallet", "down on pallet" }), 
        ({"sleep", "rest", "lay"}), 
        "You lay down on the pallet and rest your head on the bedroll. "+
        "After a moment or two you realize that the pallet would be "+
        "more comfortable if you unrolled the bedroll, first.\n");
    add_cmd_item(({"north wall", "north", "north bas relief", "north panel"}), 
        ({"push", "press" }),         "@@north_push@@");
    add_cmd_item(({"east wall", "east", "east bas relief", "east panel"}), 
        ({"push", "press" }),         "@@east_push@@");
    add_cmd_item(({"west wall", "west", "west bas relief", "west panel"}), 
        ({"push", "press" }),         "@@west_push@@");
    add_cmd_item(({"funeral seal", "seal", "funereal seal" }), 
        ({"push", "press" }),         "@@south_push@@");
    
    add_exit("chamber","south");
//    create_shelves();
    
//    add_prop(VAMP_CAN_START_HERE,1);

}


public int
start(string str)
{
    if (!IS_BG(TP))
	return 0;

    TP->set_default_start_location(file_name(TO));
    write("You will now enter the lands from this dark place.\n");
    return 1;
}

public string east_push()
{
    string str;

    switch(random(5))
    {
        case 0:
            str = "You feel a warm, tingly feeling zing through you."; break;
        case 1:
            str = "Something blows through you like a warm breeze."; break; 
        case 2:
            str = "You hear a faint click."; break;
        default:
            str = "Nothing happens.";
        break;
    }             
    
    write("You press your hands against the east panel.\n "+
        str +"\n");
    say(TP->query_met_name()+" seems to be pushing on the east panel.\n");    
    return "";
}

public string west_push()
{ 
    string str;
    
    switch(random(5))
    {
        case 0:
            str = "You hear a faint scraping sound."; break;
        case 1:
            str = "The marble under your hands goes inexplicably cold."; break;
        case 2:
            str = "Something causes your palms to prickle."; break;
        default:
            str = "Nothing happens.\n";
        break;
    }             

    write("You push hard on the west panel.\n" + str +"\n");
    say(TP->query_met_name()+" seems to be pushing on the west panel.\n");    
    return "";
}

public string north_push()
{
    string str;
    
    switch(random(5))
    {
        case 0:
            str = "The coppery scent of fresh blood washes over you "+
                "and then rapidly dissipates."; break;
        case 1:
            str = "You hear a sound not unlike the beating of a heart."; break;
        case 2:
            str = "There is a subtle shift in the panel."; break;
        default:
            str = "Nothing happens.\n";
        break;
    }             

    write("You place your hands on either side of the large "+
        "hand cradling the limp body and give a hard push.\n"+
        str +"\n");
    say(TP->query_met_name()+" appears to be pushing against the north wall.\n");    
    return "";
}

public string south_push()
{
    write("You reach up and press your hand against the funereal seal.\n"+
        "Nothing happens.    \n");
    say(TP->query_met_name()+" reaches up and touches the seal above the doorway.\n");    
    return "";
}

/*
public void init()
{
    ::init();
    
//  add_action(start,"start");
    add_action(do_get,"get");
    add_action(do_get,"pick");
    add_action(do_get,"take");
    add_action(do_put,"put");
    add_action(do_put,"drop");
    add_action(do_list,"list");


    int delay = SECURITY->query_uptime_limit() +
        SECURITY->query_start_time() - time();
    if (delay<0)
    {
        object * vamps=VAMPS(users());
        vamps=filter(vamps,&interactive());
        if (!sizeof(vamps))
        {
            object * shelves=(ROOM_DIR+"storage")->query_shelves();
            object * to_move=({ });
            foreach (object shelf : shelves)
            {
                if (!shelf)
                {
                    continue;
                }
                to_move+=all_inventory(shelf);
            }
            foreach (object shelf : query_shelves())
            {
                object * moved=filter(to_move,&operator (==) (0)
                @ &->move(shelf));
                to_move-=moved;
                if (sizeof(moved)>0)
                {
                    tell_room(TO,capitalize(COMPOSITE_DEAD(moved)) +
                    (sizeof(moved)==1 ? " falls" : "fall") + " from a "+
                    "hole in the ceiling into the "+shelf->short()+".\n");
                }
            } 
        }
    }
}
*/