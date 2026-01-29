inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("City Street");
    set_long("Sul street stretches north and south of here, while "
        +"a large gated complex lies off to your west, and a tower "
        +"stands inside a walled courtyard to your east.  Sounds of "
        +"fighting echo from both the east and west, and people "
        +"shuffle past quickly in case any of the violence overflows "
        +"into the street.\n");
    add_item("complex","It lies off to your west, hidden behind a large "
        +"gate.\n");
    add_item("gate","It lies off the road a bit to the west and is "
        +"massive.\n");
    add_item("people","These people look poor.  Ragged clothing and "
        +"timid movements show these people to be poor and afraid.  "
        +"You wonder what they are afraid of.\n");
    add_item("courtyard","It is to your west.\n");
    add_item("tower","Standing perhaps 2 stories tall, it is less a "
    	+"tower than 2 story building with battlements ringing the "
    	+"roof.  It still looks rather sturdy and secure.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_CARAVAN+"rd_cw_01.c", "north", 0, 1);
    add_exit(TYR_WARREN+"rd_vr_04.c", "south", 0, 1);
   add_exit(TYR+"school/ent.c","west");
   add_exit("/d/Cirath/guilds/militia/room/joinroom","east");
}

