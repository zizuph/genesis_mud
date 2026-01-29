/* created by Aridor 06/21/93 */

inherit "/std/room";

#include "../local.h"


create_room()
{
    set_short("Back exit of the Tower");
    set_long(BS("You stand at a portcullis leading into the "
        +    "fortress, the famous High Clerist Tower. To the "
        +    "northwest a beautiful vale stretches out into the "
        +    "mountains looming above you on the left and right.",SL));

    OUTSIDE;

    add_exit(VIN_MOUNT,"northwest",0);
    clone_object(OBJ + "portculliso")->move(TO);
}



