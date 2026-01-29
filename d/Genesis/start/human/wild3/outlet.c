/* 	outlet.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void
create_room()
{
    set_short("At the stream outlet");
    set_long("\n"+
             "Stream outlet.\n"+
             "The stream flows gently out into the sea and the sewage from the village\n"+
             "is dispersed in the bay. To the north you can see the village stockade\n"+
             "where it ends about 15 metres out in the water.\n"+
             "");

    add_exit(THIS_DIR + "stream1","west");


    add_item(({"village" }),
             "");
    add_item(({"stockade" }),
             "It ends about 15 metres out in the water and the surf breaking\n"+
             "against the submerged rocks, prevents you from passing around it.\n"+
             "");
    add_item(({"sewage" }),
             "Yuck!\n"+
             "");
    add_item(({"bay","Pensea","pensea" }),
             "Pensea is as beautiful as ever.\n"+
             "");
    add_item(({"stream","outlet" }),
             "The outlet of the stream is rather filthy but quickly dispersed\n"+
             "in the bay.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
 
    add_cmd_item( ({ "from stream", "from outlet", "from sea", "water" }),
                  "drink", "@@drink" );
}

string
drink()
{
    return "You fail to drink. The water is too polluted.\n";
}
