/*
 * Board Room for the Academy of Elemental Arts in Gelan
 * 
 * Created by Petros, September 2009
 */

#pragma strict_types

#include "defs.h"

inherit SCHOOL_ROOM_BASE;

// Prototypes
public string       random_commotion();

public void
create_school_room()
{
    set_short("Academy Assembly Hall");
    set_long("You have entered a large room bustling with activity. The area "
        + "appears to be a large assembly hall. It is filled with "
        + "students, some of which are socializing, but most are merely passing "
        + "in and out of the hall, busy attending various aspects of their "
        + "studies. There is no visible furniture here, and the most "
        + "noticeable feature is the grand window in the northern wall. "
        + "Stairs lead up from here to the terrace lounge, overlooking the "
        + "hall. The walls are bare except for a bulletin board mounted on "
        + "the west wall. To the northwest you notice small booths. "
        + "Corridors from here lead west to the racks and east into the "
        + "dormitory. From the northern doorway you sense a great deal of "
        + "commotion.\n\n");

    try_item( ({ "activity", "student", "students" }),
                "They come in every race, shape and sort. Some stand in "
              + "crowds socializing, most go about their business attending "
              + "their studies.\n");
    
    try_item( ({ "hall", "assembly hall", "large hall", 
            "large assembly hall" }),              
                "You stand in the large assembly hall of the Academy.\n");
    
    try_item( ({ "lounge", "terrace", "terrace lounge" }),
                "You cannot tell much from down here, except that there is "
              + "a railing from which those in the lounge can look down.\n");
              
    try_item( ({ "furniture" }),
                "There is none. None.\n");
    
    try_item( ({ "stairs", "staircase", "northeastern corner" }),
                "A simple marble staircase at the northeastern corner will "
              + "take you up to the lounge that overlooks this hall.\n");
    
    try_item( ({ "wall", "walls", "north wall", "west wall" }),
                "The academy walls are hewn from marble, but other than their "
              + "grey exterior, remain quite bare. On the western wall you "
              + "notice a bulletin board next to the corridor that leads "
              + "west. On the northern wall above the doorway arch, you see "
              + "a large window and a terrace lounge above it.\n");
    
    try_item( ({ "railing" }),
                "The railing is made from solid oak and prevents anyone from "
              + "falling from the lounge into the assembly hall.\n");
    
    try_item( ({ "booths", "small booths", "small wooden booths",
                 "wooden booths" }),
                "Small wooden booths stand to the northwest in a secluded "
              + "part of the hall. You could go northwest to see what they "
              + "are.\n");
    
    try_item( ({ "corridors" }),
                "One leads west to the racks, and the other leads east into "
              + "the dormitory.\n");
    
    try_item( ({ "racks", "rack", "rack room", "west" }),
                "You can't see much of them from here. Go west to take a "
              + "closer look.\n");
    
    try_item( ({ "dormitory", "dorms", "east", "east wall" }),
                "The dormitory lies east of here. That is where students go "
              + "to rest after a long day of studying the Elemental Arts.\n");
    
    try_item( ({ "doorway", "northern doorway" }),
                "The northern doorway seems quite sturdy, as if reinforced "
              + "to endure the elements. Through it, you can see a large "
              + "yard outside.\n");
    
    try_item( ({ "window", "mosaic", "color", "grand mosaic", "large window",
                 "crystalline", "colors", "energy", "mystic energy" }),
                "The northern wall above the northern doorway houses a large "
              + "window. The window itself is a grand mosaic of crystalline "
              + "glass shaded in different colors. The mosaic depicts a pentacle "
              + "with each of the five points have a distinct color. The "
              + "circle outlining the pointed star shimmers vaguely, fueled "
              + "by some mystical energy.\n");
    
    try_item( ({ "pentacle", "circle", "star", "points", "five points",
                 "pointed star" }),
                "The pentacle is a five-pointed star with a circle "
              + "outlining it. Each point has a different color, but the "
              + "lighting through the window seems to alter the colors "
              + "so that it is difficult to tell at any point exactly "
              + "what those colors might be.\n");
    
    try_item( ({ "commotion" }),
                random_commotion);
    set_tell_time(120);
    add_tell("Someone goes \"oh oh\" and several students rush excitedly "
        + "out through the northern doorway and into the yard.\n");
    add_tell("A student bumps into you, and papers fly everywhere. She "
        + "quickly picks them up and hurries along her way with barely "
        + "a polite nod.\n");
    add_tell("Someone shouts, \"Come now... off to herbalism class! We "
        + "can't be late again!\"\n");
    add_tell("A small gonme rushes by you to the north, an ambitious gleam "
        + "in his eyes.\n");
    add_tell("A burnt smell wafts in from the doorway to the north.\n");
    add_tell("A red-headed female student walks up to the bulletin board to "
        + "study her grades and goes, \"What?!?! Only A- in brewmastery?\" "
        + "She sighs petulantly and leaves.\n");
    add_tell("A hobbit yawns, munches an apple, yawns again and heads for "
        + "the dormitory.\n");
    add_tell("Looking first a bit out of place a goblin student comes down "
        + "from the lounge. You notice, however, fellow students nodding "
        + "respectfully in her direction.\n");
        
    add_exit(ACADEMIC_SCHOOL + "startroom", "east");
    add_exit(ACADEMIC_SCHOOL + "joinroom", "south");
    add_exit(ACADEMIC_SCHOOL + "rackroom", "west");
    add_exit(ACADEMIC_SCHOOL + "practiceyard", "north");
    add_exit(ACADEMIC_SCHOOL + "lounge", "up");
    add_exit(ACADEMIC_SCHOOL + "postoffice", "northwest");
    add_exit(ACADEMIC_SCHOOL + "commonroom", "common");
    
    // Clone the board and bring it here
    clone_object(ACADEMIC_OBJS + "academy_board")->move(this_object());     
}

public string
random_commotion()
{
    string * commotions = ({
        "BOOOOOO-OOOOO-OOoomm-mmm!!!!",
        "Blinding light! You can't see.. no wait.. it's gone.",
        "What's that burning smell?",
    });
    return commotions[random(sizeof(commotions))] + "\n";
}
