/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include "../temple/defs.h"

inherit INNER_OUT;
inherit NTEMPLE + "lib/blocking";

#define NUM 7

object *guards = allocate(NUM);

void
set_up_allowed()
{
    int x;
    
    for (x = T_LEADER ; x <= T_PRIEST ; x++)
        add_allowed(x, T_TEAMMEMBER, ({ "northeast" }));
    for (x = T_GENERAL ; x <= T_RECRUIT ; x++)
        add_allowed(x, T_TEAMLEADER, ({ "northeast" }), "red");
    add_allowed(T_WIZARD, 0, ({ "northeast" }));
}

void
reset_neraka_room()
{
    int x;

    setuid();
    seteuid(getuid());
    
    for (x = 0 ; x < NUM ; x++)
    {
        if (!objectp(guards[x]))
        {
            switch (x)
            {
                case 0..2:
                    guards[x] = clone_object(NNPC + "sivak");
                    break;
                case 3..4:
                    guards[x] = clone_object(NNPC + "kapak");
                    break;
                default:
                    guards[x] = clone_object(NNPC + "bozak");
                    break;
            }
            
            guards[x]->set_act_time(19 + random(5));
            guards[x]->set_chat_time(25 + random(5));
            guards[x]->set_colour("red");
            guards[x]->move(this_object());
        }
    }
    
    set_guards(guards);
}

void
create_neraka_room()
{
    set_short("in the Temple Square");
    set_extra_long("You are in the southwest part of the Temple Square. " +
        "The square stretches northwest and east of here. " +
        "Looking northeast, you see the " +
        "Temple of Takhisis that rises from the center of the square " +
        "with a small entrance right infront of it.");

    add_item_citywalls();
    add_item_street1();
    add_item_templesquare();

    setuid();
    seteuid(getuid());
    clone_object(DOOR + "raent2")->move(this_object());

    set_up_allowed();

    add_exit(NINNER + "s13", "northwest");
    add_exit(NINNER + "s15", "east");
//    add_exit(NTEMPLE + "red/entrance", "northeast");

    add_prop(ROOM_I_HIDE, -1);

    reset_neraka_room();

}


