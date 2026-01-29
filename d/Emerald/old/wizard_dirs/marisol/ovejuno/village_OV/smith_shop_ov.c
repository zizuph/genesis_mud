/* Smith's shop coded by Glidor for the old Re Albi.
 Revised by Marisol for the new Re Albi.
 Modified by Marisol (08/04/98) to be used in the village of
 Ovejuno in Emerald. Firt revision by
 Marisol Ramos (1/20/98) 1998*/

inherit "/d/Emerald/std/room";
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

object smith_ov;

void
create_ov_room()
{
}

void
create_emerald_room()
{

    set_short("Ironfist's shop");
    set_long("This is Ironfist's shop, the village blacksmith of "+
        "Ovejuno. His shop is a sturdy wooden structure. Dark oak "+
        "beams give support to the walls and roof. The counter where "+
        "Ironfist attends his customer is a lustruous oak that "+
        "seems will last forever. Behind the counter the smithy "+
        "blast its burning heat. There is a wooden sign in one of "+
        "the walls.\n");

    add_item(({"oak beams", "beams", "walls", "roof"}),
        "The oak beams are of a very fine grain. Its surface "+
        "glows under the light of the fire, giving it a amber "+
        "color. The walls and roof look sturdy.\n");

    add_item("counter",
        "A very elegant oak counter. Ironfist is famous for his "+
        "good taste with wood.\n");

    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(OBJ_I_HAS_FIRE,1);
    add_prop(ROOM_I_INSIDE,1);

    add_item("sign",
        "If you want to have a weapon repaired, just give it to "+ 
        "blacksmith and he'll tell you how much it will cost. "+
        "Then just pay him or regret.\n");
  
    add_cmd_item(({"sign", "wooden sign"}), ({"read", "examine", "exa"}),
        "If you want to have a weapon repaired, just give it to "+
        "the blacksmith and he'll tell you how much it will cost. "+
        "Then just pay him or regret.\n");

    add_exit("village_ov12.c", "north");

    reset_room();
    create_ov_room();
}

reset_room()

{
    if (!smith_ov)
    {
      tell_room(this_object(),"The blacksmith arrives.\n");
      smith_ov = clone_object(OV_VILLAGE_NPC +"smith_ov");
      smith_ov->move(this_object());                              
      return 1;
    }
}

init()

{
    ::init();
}

leave_inv(obj,to)

{
    ::leave_inv(obj,to);
    if (!living(obj)) return;
    if(smith_ov) smith_ov->someone_left(obj,to);
}
                                                             
