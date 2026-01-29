#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/raum/std/jewelry.h"

inherit RAUM(std/jewelry);

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/skull_ring.c
 * Purpose    : Used to initiate others into the Order of Him
 * Located    : In the prop room
 * Created By : Sarr  24.Apr.97
 * Modified By: 
 */



void
create_jewelry()
{
    set_name("ring");
    set_adj("blood-red");
    add_adj("skull");
    set_short("blood-red skull ring");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_LHAND, 
                           ANSALON_JEWELRY_RHAND}));
    
    set_long("This ring is made of black onyx, upon which rests a very "+
    "large and valuable looking ruby shaped into a grim skull. It "+
    "sparkles in the dim light, and you can hear a faint screams coming "+
    "from it. It looks very magical, sparkling like a dark and "+
    "bloody eye.\n");

    set_jewelry_value(2800);
}

int
do_twist(string str)
{
    NF("Twist what? The gem in the ring maybe?\n");
    if(str != "the gem in the ring")
        return 0;
    write("You twist the gem in your "+short()+".\n");
    say(QCTNAME(TP)+" twists the gem in "+HIS(TP)+" "+short()+".\n");
    set_alarm(4.0,0.0,&tell_room(E(TP),"Screams echo all around the room, "+
    "and you see "+
    "faint, ghastly faces of lost souls from the Netherworld begin "+
    "to appear in the room, all eyes on the new soon-to-be servant of "+
    "Him.\n"));
    return 1;
}

void
init()
{
    ::init();
    AA(do_twist,twist);
}

