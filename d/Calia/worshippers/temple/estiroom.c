
 /* Worshippers skill estimation/meditation  room */
 /* by Jaacar 1996                                */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"
#include WORSHIP_HEADER


void
create_room()
{
    set_short("Meditation chamber");
    set_long("This small chamber has many small straw mats on the "+
        "floor which you can <kneel> upon to <estimate> your "+
        "stats and <set> your preferences. You may also <list "+
        "guilds> here as well. There is a small "+
        "exit to the north. On the southern wall, you notice a small "+
        "glowing stone, as well as a small statue.\n");

    add_item(({"stone","glowing stone","small glowing stone","small stone"}),
        "This small glowing stone is luminous enough to light the entire "+
        "chamber with a soft light.\n");
    add_item(({"statue","small statue"}),"It is a small statue "+
        "depicting a fellow Worshipper praying.\n");


    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(WOR_TEMPLE+"medroom","north",0,1);
    create_guild_support();
}

void
gs_hook_start_meditate()
{
    write("You kneel down and close your eyes. A feeling of great "+
        "ease and self control falls upon you. You block off "+
        "your senses and concentrate solely upon your own mind. You "+
        "find yourself able to <estimate> your different preferences "+
        "and <set> them at your own desire.\nJust <rise> when you "+
        "are done meditating.\n");
    say(QCTNAME(this_player())+" sits down and starts to meditate.\n");
}

int
touch(string str)
{
    if (!str || str != "stone")
        return 0;

    write("As you touch the stone, you find yourself elsewhere.\n");
    say(QCTNAME(TP)+" vanishes suddenly.\n");
    tell_room(WOR_TEMPLE+"granted",QCTNAME(TP)+" appears.\n");
    TP->move_living("M",WOR_TEMPLE+"granted");
    return 1;
}

int
pray(string str)
{

    write("As you begin praying, a vision of a beautiful shrine "+
        "floods into you head. It appears so real, that you reach "+
        "out to touch the walls of the shrine. As you firmly place "+
        "your hand upon a wall you realize "+
        "it is not just a vision!\n");
    say(QCTNAME(TP)+" kneels down to pray, then suddenly vanishes before your eyes.\n");
    tell_room(WOR_SHRINE+"entrance",QCTNAME(TP)+" suddenly appears before you.\n");
    TP->move_living("M",WOR_SHRINE+"entrance");
    return 1;
}


void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface "+
        "of your consciousness. You exhale and feel very relaxed as "+
        "you stand up.\n");
    say(QCTNAME(this_player())+" comes out of a trance and stands up.\n");
}
 

int query_prevent_snoop()
{
    return 1;
}
 
void
init()
{
    ::init();
    init_guild_support();
    add_action(gs_meditate,"kneel");
    add_action(touch,"touch");
    add_action(pray,"wpray");
    add_action(pray,"pray");
}

