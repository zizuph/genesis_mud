//-*-C++-*-
// file name:      storage.c
// creator(s):     Novo  May 2008
// last update:    Lilith  June 2008 - added room desc
// note: 
// bug(s):
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>

/*
public void configure_shelf(object shelf,int slot)
{
    string side;
    string position;
    shelf->set_name("shelf");
    shelf->add_name("recess");
    shelf->add_name("arcosolium");
    if (slot>=3)
    {
        side="west";
        shelf->set_allow_glowing(1);
    }
    else
    {
        side="east";
        shelf->set_allow_nonglowing(1);
    }
    shelf->add_adj(side);
    switch (slot % 3)
    {
        case 0:
            position="north";
            shelf->add_adj(position);
            shelf->set_allow_weapon(1);
            break;
        case 1:
            position="central";
            shelf->add_adj(position);
            shelf->set_allow_armour(1);
            break;
        case 2:
            position="south";
            shelf->add_adj(position);
            shelf->set_allow_misc(1);
            break;
    }
    shelf->set_short(position+" "+side+" arcosolium");
    shelf->set_long("This is an arched recess in the wall, once intended "+
    "to hold the remains of the deceased. There is no body here however, "+
    "and the " + shelf->short() + " appears to be used now for "+
    "storage.\n");
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
    heap->add_name("pile");
    heap->set_short("heap");
    heap->set_long("This is a heap of undesirable items, unused and left "+
    "alone in the corner of the chamber.\n");
    object * shelves=({ });
    for (int i=0;i<6;i++)
    {
        object shelf=clone_object(OBJ_DIR+"rack");
        configure_shelf(shelf,i);
        shelf->move(TO);
        shelves+=({ shelf });
    }
    set_shelves(shelves);
}
*/

public void create_vamp_room()
{

    set_short("Burial chamber");
    set_long("A long burial chamber with arched recesses on the "+
        "east and west walls. It has been entirely lined with "+
        "blocks of limestone, which is useful in the dessication "+
        "of corpses. The stones are steeped in darkness that "+
        "would defy the strongest light, as if the spirits of "+
        "the ancient ones who were laid to rest here are "+
        "deeply disturbed. The air is very dry and somewhat stale, "+
        "but there is no scent of death or decay. The north wall "+
        "bears the faded remains of a mural, and on the floor "+
        "at its base is a haphazard pile.\n");

    add_item(({"walls", "wall"}), "Which wall?\n");
    add_item(({"limestone", "stones", "blocks"}), 
        "The limestone has a pale cast. It appears to have been placed "+
         "here a long time ago.\n");
    add_cmd_item(({"limestone", "stones", "blocks"}), "feel", 
        "The limestone feels porous and somewhat chalky.\n");
    add_item(({"north wall", "mural", "painting"}),
        "The north wall bears the remnants of an ancient and crumbling "+
        "mural. Large areas of the painting have broken away from the "+
        "wall, exposing stained limestone. The paint has faded to such "+
        "an extent that no details are visible, just broad outlines of "+
        "a single figure and a structure before it, perhaps a table.\n");
    add_item(({"base", "base of the north wall"}), 
        "There is a pile at the base of the north wall. Some of it "+
        "appears to be fragments of the murual above.\n");
    add_item(({"fragment", "fragments"}), "They are pieces of paint "+
        "that have fallen from the mural.\n");
    add_item(({"stain", "stains", "stained limestone"}),
        "The stone of the wall has been discoloured by the paint from "+
        "the mural that was painted on it.\n");
    add_item(({"floor", "travertine"}), 
        "The floor is paved in a beautiful limestone formation of "+
        "travertine. There is a pile on the floor, against the north wall.\n");
    add_item(({"air"}), "It is dark, and heavy with a disturbed feeling.\n");
    add_cmd_item(({"air"}), "smell", "It smells stale.\n");
    add_item(({"darkness"}), 
        "Ebbing and flowing through the chamber, this darkness has a "+
        "substance to it that no amount of light can conquer.\n");
    add_item(({"east wall"}), "Three arcosoliums are located on this wall.\n");
    add_item(({"west wall"}), "Three arcosoliums are located on this wall.\n");
    add_item(({"south wall", "south", "door", "doorway", "entrance" }),
        "There is an open doorway with a funereal seal carved into the "+
        "limestone above it.\n"); 
    add_item(({"funeral seal", "seal", "funereal seal" }), 
        "A funereal seal depicts two figures, one living, one dead, "+
        "divided from each other by a lightning bolt. There is a "+
        "faint gold patina on it.\n");
    add_item(({"gold patina", "patina", "gold leaf"}), 
        "Gold leaf was applied to the funereal seal "+
        "over the doorway. Most of it appears to have faded with time.\n");
    add_cmd_item(({"north wall", "north", "north mural", "mural"}), 
        ({"push", "press", "touch"}),         "@@north_push@@");
    add_cmd_item(({"east wall", "east"}), 
        ({"push", "press", "touch" }),         "@@east_push@@");
    add_cmd_item(({"west wall", "west"}), 
        ({"push", "press", "touch" }),         "@@west_push@@");
    add_cmd_item(({"funeral seal", "seal", "funereal seal" }), 
        ({"push", "press", "touch" }),         "@@south_push@@");

    
    add_exit("upperchamber","south");
    
//    create_shelves();
//  add_prop(VAMP_CAN_START_HERE,1);

}
/*
public void init()
{
    ::init();
    add_action(do_get,"get");
    add_action(do_get,"pick");
    add_action(do_get,"take");
    add_action(do_put,"put");
    add_action(do_put,"drop");
    add_action(do_list,"list");
}
*/

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
            str = "It feels chalky and dry under your hands.";
        break;
    }             
    
    write("You press your hands against the limestones of the east wall.\n "+
        str +"\n");
    say(TP->query_met_name()+" seems to be pushing on the east wall.\n");    
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
            str = "The limestone under your hands goes inexplicably cold."; break;
        case 2:
            str = "Something causes your palms to prickle."; break;
        default:
            str = "It feels chalky and dry under your hands.";
        break;
    }             

    write("You push hard on the west wall.\n" + str +"\n");
    say(TP->query_met_name()+" seems to be pushing on the west wall.\n");    
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
            str = "It feels chalky and dry under your hands.";
        break;
    }             

    write("You place your hands against the crumbling ancient mural "+
        "and give a hard push.\n"+
        str +"\n");
    say(TP->query_met_name()+" appears to be pushing against the north wall.\n");    
    return "";
}

public string south_push()
{
    write("You reach up and press your hand against the funereal seal.\n"+
        "Nothing happens.    \n");
    say(TP->query_met_name()+" reaches up and touches the seal above "+
        "the doorway.\n");    
    return "";
}
