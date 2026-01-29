
/*
 * pool_room.c
 *
 * Crystal Pool Room for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), August 17th, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

#define ROUNDABOUT  "/d/Calia/mountain/road/road19"
#define THALASSIA   "/d/Calia/sea/thalassia/obelisk"
#define WORSHIPPERS "/d/Calia/guilds/elementalists/temple/old_entrance"
#define CALIANS     "/d/Calia/mountain/croad/croad27"
#define WATERFALL   "/d/Calia/argos/nwterr/rooms/wfcave"

int destination = 1;

void
create_room()
{
    set_short("Crystal Pool Chamber");
    set_long("You have entered a small chamber with shining mirrored "+
        "walls, floor, and ceiling that send light and shadow dancing in "+
        "a myriad of reflections that spin into infinity. Almost lost in "+
        "the cascade of silvery light, a circular pool rests silent and "+
        "perfectly still in the chamber's floor, its surface a looking-glass "+
        "that reflects in equal measure to the room's mirrored surfaces. "+
        "The disorienting effect of the chamber is broken only by an exit "+
        "leading south into the statue chamber.\n");

    add_item(({"wall","walls","ceiling","roof","floor"}),"The walls, "+
        "floor and ceiling are all covered in the same silver coloured, "+
        "reflective material. They are all well polished making them "+
        "almost mirror-like in appearance.\n");
    add_item(({"pool","circular pool","looking-glass"}),"It is a pool "+
        "made from a clear crystal material. This pool lies in the centre "+
        "of the chamber. Looking into the pool you see a reflection of "+
        "your own face, but the surroundings are not this chamber! "+
        "@@current_destination@@ You could enter the pool if "+
        "you wished, or ripple it to blur the surroundings seen within it.\n");
    add_item(({"exit","small exit","statue chamber"}),"There is a small "+
        "exit in the south wall, leading back to the Statue Chamber beyond.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"statue_chamber","south",0,1);
}

string
current_destination()
{
    string current_destination;

    switch (destination)
    {
        case 1:
            current_destination = "The surroundings appear to be at the roundabout ";
            current_destination += "some distance away from here and looks as ";
            current_destination += "though you are looking into this same pool ";
            current_destination += "only from that location.";
            break;
        case 2:
            current_destination = "The surroundings appear to be at the obelisk ";
            current_destination += "in the Ancient City of Thalassia and looks as ";
            current_destination += "though you are looking into this same pool ";
            current_destination += "only from that location.";
            break;
        case 3:
            current_destination = "The surroundings appear to be at the archway ";
            current_destination += "outside of the Elemental Worshippers temple ";
            current_destination += "and looks as though you are looking into this ";
            current_destination += "same pool only from that location.";
            break;
        case 4:
            current_destination = "The surroundings appear to be at the crystal ";
            current_destination += "palace of the Calian Warriors ";
            current_destination += "and looks as though you are looking into this ";
            current_destination += "same pool only from that location.";
            break;
        default:
            current_destination = "The surroundings appear to be at the cavern behind ";
            current_destination += "the waterfall in the mountains northwest of the ";
            current_destination += "city of Argos and looks as though you are looking ";
            current_destination += "into this same pool only from that location.";
            break;
    }
    return current_destination;
}

int
do_enter(string str)
{
    if (str != "pool" && str != "the pool")
    {
        NF("Enter what? The pool? <enter pool>\n");
        return 0;
    }

    if (present(CEREMONIAL_GARB,deep_inventory(TP)))
    {
        write("You cannot leave the temple with ceremonial items! "+
            "Please return them to the sacristy first.\n");
        return 1;
    }

    if (present(CEREMONIAL_GARB,TP))
    {
        write("You cannot leave the temple with ceremonial items! "+
            "Please return them to the sacristy first.\n");
        return 1;
    }

    if (TP->query_skill(SS_SPIRIT_PUNISHMENT) == TEMPLE_RESTRICTED)
    {
        write("You have been restricted to the Temple by the Spirit "+
            "Circle council, so you cannot leave.\n");
        return 1;
    }

    write("You step into the crystal pool and stand in the centre.\n"+
        "You feel yourself sinking into the pool, though you do not "+
        "feel you are getting wet at all. As you sink to just below "+
        "your eyes, you close them.\nWhen you open your eyes you find "+
        "yourself elsewhere.\n");
    say(QCTNAME(TP)+" steps into the crystal pool and stands in the "+
        "centre. "+capitalize(HE)+" sinks into the pool, closing "+
        HIS+" eyes just before sinking totally from sight, disappearing "+
        "altogether.\n");
    switch (destination)
    {
        case 1:
            TP->move_living("M",ROUNDABOUT);
            break;
        case 2:
            TP->move_living("M",THALASSIA);
            break;
        case 3:
            TP->move_living("M",WORSHIPPERS);
            break;
        case 4:
            TP->move_living("M",CALIANS);
            break;
        default:
            TP->move_living("M",WATERFALL);
            break;
    }
    
    tell_room(environment(TP),"A small shadow appears on the ground.\nThe "+
        "shadow begins to grow, elongating into a humanoid type shape. "+
        "The shadow then begins to rise up off of the ground, gaining "+
        "mass and solidifying as it does so. It forms arms, legs, a torso, "+
        "and finally a head.\nIn the blink of an eye, "+QTNAME(TP)+" is "+
        "standing there and the shadow is gone.\n",TP);
    return 1;
}

int
do_ripple(string str)
{
    if (!str)
        return 0;
    if (parse_command(str, ({}),"[the] 'pool'"))
    {
        write("You place your finger into the pool, sending ripples across "+
            "the surface of it, and changing the surroundings viewed in it.\n");
        say(QCTNAME(TP)+" places "+TP->query_possessive()+" finger into the "+
            "pool, sending ripples across the surface of it.\n");
        destination += 1;
        if (destination >= 6)
            destination = 1;
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
    add_action(do_ripple,"ripple");
}
