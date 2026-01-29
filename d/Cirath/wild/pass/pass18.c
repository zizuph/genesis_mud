/* a_pass18.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are standing on a path leading up a mountain. "+
              "The path turns down and eastward around a huge rock "+
              "here, while still climbing upwards to the southwest."+
              " You are dizzy from the thin air, and your muscles have "+
              "never before felt this sore, probably due to the fact "+
              "that they get far too little of the oxygen they need to "+
              "operate properly. This, combined with the blazing sun "+
              "over your head, makes you doubt you will last long, "+
              "but seeing vultures on the horizon you decide that "+
              "this is not the place to rest.\n");

    ROCK;
    SUN;
    TRAIL;
    VULTURE;
    OUTSIDE
    add_exit(WILD_PASS+"pass19.c","southwest",0,2);
    add_exit(WILD_PASS+"pass17.c","east",0,2);
}
