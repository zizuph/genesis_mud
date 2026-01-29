inherit "/d/Kalad/room_std.c";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

void
create_room()
{
    set_short("Within the Netherworld");
    set_long("\n"+
    "   You stand on an stretch of reddish sand and rock that extends "+
    "in all directions as far as you can see. Along the horizon, you "+
    "see black sillouettes of twisted shapes of things you know not "+
    "what. The horizon glows with an eerie greenish light, and gently "+
    "fades into blackish nothing into the star-less sky.\n"+
    "   Jutting out of the ground before you like a twisted claw out "+
    "of a grave is a large, black-stoned tower. It soars into the "+
    "abysmal black sky as far as you can see. A large arched doorway "+
    "faces you, leading into the mysterious tower.\n\n");
    add_item("sky","The sky is a pure abysmal black color, that "+
    "reflects absolutely no light. No star mars its perfect blackness.\n");
    add_item("horizon","The horizon is glowing with an eerie green "+
    "color, upon which you see reflected black twisted shapes.\n");
    add_item(({"shapes","twisted shapdes"}),"The shapes seems to be "+
    "of unholy looking rock-formations, but you do not know for sure.\n");
    add_item("tower","The tower is made of thoudsands of black stones "+
    "that soar high into the sky. The sheer height of it makes you wonder "+
    "why it doesn't tople over. You do not see the top of it, as it "+
    "melts away into the blackish sky. There is a large archway on the "+
    "side facing you, of which a soft red light glows from within.\n");
    add_item("stones","The stones of the tower are decorated with many "+
    "arcate and ornate symbols.\n");
    add_item(({"doorway","archway"}),"The doorway before you leads "+
    "into the temple. You can only see a soft red light coming from "+
    "within.\n");
    INSIDE;
    add_exit(KHIRAA_DIR(temple/rooms/netherworld2),"tower",0,-1);
}
