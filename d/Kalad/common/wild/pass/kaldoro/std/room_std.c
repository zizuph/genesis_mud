/* 
 * /d/Kalad/common/wild/pass/kaldoro/std/room_std.c
 * Purpose    : A standard Kaldoro room to be inherited by such.
 * Located    : 
 * Created By : Rico 20.Sep.96
 * Modified By: 
 */ 

#include "../defs.h"

inherit "/std/room.c";

create_room()
{
   ::create_room();

   set_short("\nKaldoro standard room\n\n");

}

