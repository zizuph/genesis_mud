inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* 	Created by:	Sarr 
 * 	Modified by:	Toby, 971014 (fixed typos)
 */

void
create_room()
{
    set_short("In the entrance of the House of Paullus");
    set_long("You stand inside the grand entrance of the magnificant "+
        "house of Paullus. Before you, a huge and ornate staircase leads "+
        "up to a balcony. There is a doorway right in front of you, while "+
        "three other exits lead to your west, northwest, and northeast. "+
        "A beautiful chandelier hangs from the ceiling, and there is a "+
        "splendid grandfather clock ticking away at the corner. The room "+
        "is decorated with exotic paintings and tapestries. Old and valuable "+
        "looking furniture is placed around the room.\n");
    
    add_item("staircase","It is made of polished oak-wood. The rails "+
        "are carved into beautiful designs, and the steps are covered with "+
        "soft animal fur.\n");
    add_item("balcony","An oak railing adorns the second level above "+
        "you think you can see another hallway leading back further into "+
        "this wonderful house.\n");
    add_item("chandelier","A sparkling myriad of lights shine from "+
        "this masterfully crafted glass and crystal chandelier. Candles "+
        "burn inside it.\n");
    add_item(({"grandfather clock","clock"}),"A very old looking "+
        "but beautiful clock.\n");
    add_item("paintings","Each painting is so real looking. They "+
        "depict various scenic places in the wilderness. Some of the "+
        "great ocean, some of the beautiful desert and forest.\n");
    add_item("tapestries","They are beautifully woven, and are marked "+
        "with the emblem of the house of Paullus.\n");
    add_item("furniture","Ornate chairs and expensive leather couches. "+
        "Tables with wonderful little ornaments are placed along the room.\n");
    add_item("ornaments","Statuttes and candles and glass sculptures.\n");
    
    INSIDE;
    
    add_exit(NOBLE(paullus/m2),"west",0,-1,-1);
    add_exit(NOBLE(paullus/m6),"northwest",0,-1,-1);
    add_exit(NOBLE(paullus/m5),"north",0,-1,-1);
    add_exit(NOBLE(paullus/m4),"northeast",0,-1,-1);
    add_exit(NOBLE(paullus/m10),"stairs",0,-1,-1);
    add_exit(NOBLE(paullus/g3),"south",0,-1,-1);
}
