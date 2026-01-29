// Sarr,
// recoded by Fysix, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object  lady,
        *troopers = allocate(4);
int     trop;   // Have troopers been cloned recently?

void reset_room();

void
create_noble_room()
{
    set_short("In the master bedroom of the High-Lord's Castle");
    INSIDE;
    set_long("You are now within the grand bedroom of the High-Lord. "+
        "This is where the High-Lord retires every night to sleep and "+
        "relax. "+
        "The walls are made of polished oak, and paintings, tapestries and "+
        "all sorts of ornaments hang from them. The ground is covered with "+
        "a lush fur rug. A large, canopy bed sits against one wall, directly "+
        "across from a large dresser. In another corner, you see stacks of "+
        "chests. A table sits in the center of the room here, where it "+
        "stretches off to the north end of the room. Many chairs are set "+
        "around it. There is a large mirror on the wall as well. The windows "+
        "are set high off the ground, near the ceiling, and sunlight streams "+
        "down into the room.\n");
    add_item("walls","The walls are made of large, oak wood panels that "+
        "are polished to a bright shine.\n");
    add_item("paintings","There are many gold-framed paintings on the "+
        "walls. They depict various aspects of city life. One, however, "+
        "shows a scene of a armoured warrior in battle with a bull-headed "+
        "giant with a nasty axe, and a big, blue gem in his belt.\n");
    add_item("tapestries","There are many intricate, symbols covering "+
        "these fine woven tapestries.\n");
    add_item("ornaments","There are old weapons, trophies and coins "+
        "placed around the room.\n");
    add_item("rug","The rug seems to be some kind of animal fur. It "+
        "is very soft and warm.\n");
    add_item("bed","The bed is neatly made. The soft silk sheets feel "+
        "very nice to the touch. A thin veil surrounds it.\n");
    add_item("dresser","The dresser is made of white oak. It has many "+
        "drawers in them, and they are mostly filled with old clothes.\n");
    add_item("chests","There are many iron bound chests stacked in "+
        "one corner. They are all locked tight, except one. In it, you "+
        "see nothing but an old book.\n");
    add_item(({"book","old book"}),"The book is written in a strange "+
        "language you don't understand. However, on the cover, you see "+
        "some words you do understand. They read: The teachings of God.\n");
    add_item("table","The table is made of solid red oak.  On its polished "+
        "surface, you find old platters, goblets and some papers.\n");
    add_item("platters","The platters are made of silver, and old "+
        "left-over food crumbs are on them.\n");
    add_item("goblets","The goblets are made of gold and silver, and "+
        "look very old. There is some wine left in some of them.\n");
    add_item("papers","They look to be official documents of the "+
        "High-Lord's court. Boring political stuff.\n"); 
    add_item("chairs","The chairs are made of oak, and have comfortable "+
        "velvet cusions on them to sit on.\n");
    add_item("mirror","@@mirror@@");
    add_item("windows","The windows let in light to the room.\n");
    
    add_exit(NOBLE + "castle/c50", "east", 0, 0);

    reset_room();
}

void
reset_room()
{
    lady = clone_npcs(lady, NOBLE + "npc/castle_lady");
    trop = 0;
}

string
mirror()
{
    if (TP->query_prop(LIVE_I_UNDEAD))
        return "You see nothing but the wall behind you.\n";
    else
        return "You see yourself staring at the mirror.\n";
}

void
troops3(object enemy)
{
    object *tmp, to;
    
    troopers = clone_npcs(troopers, NOBLE + "npc/castle_guard");

    to = this_object();
    tmp = filter(troopers, &operator(==)(to) @ environment);
    if (sizeof(tmp))
        tmp[0]->command("shout We are here Captain! My lady!");
}

void
troops2(object enemy)
{
    tell_room(TO, "You can hear the sound of many heavy booted "+
        "footsteps very nearby.\n");
    set_alarm(8.0, 0.0, &troops3(enemy));
}

void
troops(object enemy)
{
    object cap, *tmp;

    if (trop == 0)
    {
        cap = present("captain", TO);
        tmp = filter(troopers, objectp);

        if (sizeof(tmp) < sizeof(troopers))
        {
            trop = 1;

            if (cap)
                cap->command("shout Bring in heavy guards to deal with "+
                    "this fool!");
            tell_room(TO, "You can hear the faint sound of " +
                "many heavy booted footsteps near.\n");

            set_alarm(15.0, 0.0, &troops2(enemy));
         }
    }
}

void
call_help(object enemy)
{
    call_other(NOBLE + "castle/c50", "aid_the_queen", enemy);
    set_alarm(10.0, 0.0, &troops(enemy));
}

