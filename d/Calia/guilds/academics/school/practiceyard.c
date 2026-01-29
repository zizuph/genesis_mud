/*
 * Start Room for the Academy of Elemental Arts in Gelan
 * 
 * Every member of the Elemental Academy Guild has the option of starting
 * here in this room. It is part of the Elemental Academy of Gelan.
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit SCHOOL_ROOM_BASE;

public void
create_school_room()
{
    set_short("Practice Yard");
    set_long("This is the only space in the entire Academy that is outdoors. "
        + "The space here is basically a large yard with plenty of activity. "
        + "It is surrounded "
        + "by a very tall hedge of thick trees with a slender iron fence as "
        + "support. Everywhere you look, you find training dummies along "
        + "with racks in all shapes, sizes and conditions. Next to these "
        + "dummies you see students practicing their academy talents with "
        + "great vigor. Every now and then it seems there is more vigor "
        + "and less thought. There is no floor tiling here, only normal "
        + "ground. Southwards you see an archway that leads back into the "
        + "main Academy halls.\n\n");

    // Remove items that apply to the inside.
    remove_item("ground");
    remove_item("floor");
    remove_item("ceiling");
    remove_item("paintings");
    remove_item("fresco paintings");
    remove_item("frescoes");
    remove_item("painting");
               
    remove_prop(ROOM_I_INSIDE);
    
    try_item( ({ "hedge", "fence", "black iron fence", "sturdy fence", "thick hedge" }),
        "A sturdy black iron fence with a crystalline sheen surrounds the "
      + "yard. Behind it a thick hedge of trees shields the yard from the "
      + "outside. You get the distinct feeling the fence might protect "
      + "the rest of Gelan against the activities here rather than the "
      + "other way around.\n" ); 
    
    try_item( ({ "dummies", "racks", "rack", "training rack", "training racks",
                 "training dummies", "dummy", "training dummy" }),
        "The training dummies here range from detailed crafted images of "
      + "a tall roaring forest troll to the more common bullseye circle "
      + "dummy. Some of them are in pristine condition, whereas others "
      + "are marred by repeated assaults of different kinds. Students are "
      + "charged with repairing or cleaning them up now and then.\n");
      
    try_item( ({ "ground", "dirt" }),
        "The practice yard doesn't have much on the ground besides the brown "
      + "dirt marked by the footprints of eager students.\n");
    
    try_item( ({ "students", "student" }),
        "Every race and type of student are here. Some are practicing their "
      + "talents on the dummies. A few are cleaning up and repairing the "
      + "dummies. Here and there groups are debating combat tactics while "
      + "pointing at the more fierce looking dummies. Others are simply "
      + "admiring the spectacle and perhaps throwing out a comment or "
      + "two on each other's efforts.\n");

    try_item( ({ "academy", "structure" }),
        "The grey Academy walls are to the south with a doorway leading into "
      + "the assembly hall.\n");
    
    try_item( ({ "wall", "walls" }),
        "A wall houses a doorway to the south. There is a massive window in "
      + "center of the second floor and a smaller square window to the "
      + "top right of it.\n");

    try_item( ({ "massive window", "window" }),
        "It is a grand mosaic with a star-like symbol. Some students in the "
      + "lounge are surveying the yard where you are standing.\n");
   
    try_item( ({ "square window", "taskmaster", "amjal" }),
        "You notice the Taskmaster looking down in the yard from time to time "
      + "behind the small square window.\n");
    
    add_exit(ACADEMIC_SCHOOL + "boardroom", "south", "@@prevent_leave_without_contraption");

    set_tell_time(120);
    add_tell("Someone shouts: Watch out!\n");
    add_tell("A group of students dodge a firebolt gone awry!\n");
    add_tell("A dazzle of colors alerts you to a student wrecking "
        + "havoc to a tall dummy depicting an angry witch.\n");
    add_tell("There's a chill in the air as one of the dummies "
        + "is covered in ice and falls apart.\n");
    add_tell("Uh oh! The ground beneath you turns muddy. You are "
        + "quick enough to escape any misfortune.\n");
    add_tell("A gust of wind strikes your face causing you to blink. "
        + "Good thing that was only a training exercise.\n");
    add_tell("A massive green bolt of acid suddenly changes direction "
        + "and heads towards the trees! Before it can cause any damage "
        + "the black fence shimmers briefly and the bolt vanishes!\n");
    add_tell("There's a brief sprinkle of rain over a tutor who looks "
        + "somewhat displeased with a certain blushing student.\n");
}

public int
prevent_leave_without_contraption()
{
    object player = this_player();
    object contraption;
    if (objectp(player) && IS_MEMBER(player) 
        && (contraption = present("academic_resistance_contraption", player))
        && contraption->query_no_show_composite())
    {
        write("You cannot leave while your contraption is still hanging! "
            + "You can <retrieve contraption from rack> if you need "
            + "to leave.\n");
        return 1;
    }
    
    return 0; 
}

