
/*  

    The flame board room for Cadets of Gelan. 

    Coded by Maniac@Genesis 19/4/99. 

*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <money.h>
#include "cadet.h"


int
gc_query_private_room()
{
    return 1;
}


void
create_room()
{
    set_short("Cadet flame board");
    set_long("Here cadets may post flames. " +
             "There is a sign here.\n");  

    add_cmd_item("sign", ({ "read" }), 
             "Although you are freer to be insulting here, the " +
             "rules about harassment in Genesis still apply. " +
             "In other words, don't use it as a license to " +
             "be obscene or set out to make the game hell " +
             "for someone. A good flame usually gives the " +
             "audience a good laugh and doesn't need " +
             "profanities.\n"); 

    add_item("sign", "It has readable text on it.\n"); 

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(GC_BOARDROOM, "up"); 
    clone_object(GC_DIR + "cadet_flame_board")->move(this_object()); 
}

