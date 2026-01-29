/*
 * Lounge for the Academy of Elemental Arts in Gelan
 * 
 * Created by Petros, September 2009
 */

#pragma strict_types

#include "defs.h"

inherit SCHOOL_ROOM_BASE;

public void
create_school_room()
{
    set_short("Lounge");
    set_long("This is a lounge where students meet to relax or study. "
        + "Decorations in this room are very sparse. There are a "
        + "few cushion chairs with small tables where students are "
        + "lounging. Some are engaged in their studies, whereas "
        + "others seem to be meeting here for a small reprieve. To the "
        + "south you see a railing as well as a staircase leading down "
        + "into the hall beneath you. The north wall is dominated by a "
        + "vast mosaic window. There are doors both to the east and "
        + "to the west.\n\n");
    
    try_item( ({ "lounge", "room" }),
            "This is probably the only room where one has the opportunity "
          + "to relax in the Academy.\n");
    
    try_item( ({ "chair", "chairs", "table", "tables", "cushion chair",
        "cushion chairs", "small table", "small tables" }),
            "Comfortable chairs matched with the small rustic tables provide "
          + "good comfort for the students who meet here to relax and "
          + "study.\n");
    
    try_item( ({ "student", "students" }),
            "Although not as many as in the assembly hall you notice the "
          + "students here come from all over the realms. Some sit in the "
          + "chairs studying, whereas others are looking down on their "
          + "fellow students in the hall, or out the window into the yard.\n");
    
    try_item( ({ "railing" }),
            "The railing is made from oak and prevents anyone from falling "
          + "down from the lounge to the assembly hall.\n");
    
    try_item( ({ "staircase" }),
            "The railing is made from oak and prevents anyone from falling "
          + "from the lounge down into the assembly hall.\n");
    
    try_item( ({ "window", "mosaic window", "vast mosaic window", "figures" }),
            "The vast mosaic window is beautiful, with colors that dazzle "
          + "with the light that streams in through it. Looking out the "
          + "window you see the practice yard outside, but cannot make "
          + "out the figures outside cleary.\n");
    
    try_item( ({ "yard", "practice yard", "outside", "dummies" }),
            "You can see the outside through both the window and also the "
          + "archway from the assembly hall below. You can see a practice "
          + "yard outside filled with commotion and activity as students "
          + "practice what they are learning against dummies.\n");
          
    try_item( ({ "hall", "assembly hall" }),
            "Looking down from the railing you see that as always the "
          + "assembly hall is filled with students walking here and there.\n");      
          
    try_item( ({ "door" }),
            "Which one? The east door or west door?\n");
   
    try_item( ({ "doors" }),
            "There are two doors that lead out of this room, one to the "
          + "east and one to the west.\n");
    
    try_item( ({ "east door", "east", "study room", "study" }),
            "The east door leads out to the study room. Students go there to "
          + "gain more knowledge and absorb what they have learned in a "
          + "quiet environment.\n");
    
    try_item( ({ "west door", "west", "taskmaster", "office",
                 "taskmaster's office" }),
            "The west door leads out to the Taskmaster's office. Students "
          + "who are looking for tasks that will enhance their learning go "
          + "there.\n");
    
    add_exit(ACADEMIC_SCHOOL + "study", "east");
    add_exit(ACADEMIC_SCHOOL + "taskroom", "west");
    add_exit(ACADEMIC_SCHOOL + "boardroom", "down");
}

