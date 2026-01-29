// backex.c
/* created by Aridor 06/21/93 */
// modified by Grace

#include "../local.h"

inherit "/std/room";

create_room()
{
    set_short("Back exit of the Tower");
    set_long(BS("You stand at a portcullis leading into the "
        +    "curtain wall of the Knights' Spur at Westgate Pass. "
        +    "The famous High Clerist Tower is directly west. To "
        +    "the northwest a beautiful vale stretches out into the "
        +    "mountains looming above you on the left and right.",SL));

    OUTSIDE;

    add_exit(VIN_MOUNT,"northwest",0);
     clone_object(SOBJ + "portculliso")->move(TO);
} 
