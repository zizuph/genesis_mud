#include "defs.h"
#include <tasks.h>
inherit SHADOWS_ROOM;

/* West Forest Room, Sarr. 
 * Updated, Nerull.
 * 2017-05-24 Malus: Added description
 * 2017-08-28 Malus: Making room beneath a bridge
 */ 
object steed, knight;

int do_climb(string str);

void
create_room()
{
    ::create_room();
    set_short("Beneath a stone bridge");
    set_long("You stand under a stone bridge, shielded from the sky and " +
            "any light it might provide. The arch above leaves little " +
            "headroom, but there is plenty of bare ground adjoining the " +
            "stream bank. The stream makes soft burbling sounds as it " +
            "journies north.\n"); 
    add_item(({"stream"}), "It is flowing south to north at a " +
            "leisurely pace.\n");
    add_item(({"arch","bridge"}), "The stone looks old, but sturdy.\n");
    add_item(({"ground"}), "It looks surprisingly well-trodden.\n");
    add_item(({"bank", "stream bank", "banks"}), "The stream banks are wet " +
           "and look slippery.\n"); 
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_DARK_LONG, "Beneath a bridge, in darkness.\n");
    add_prop(ROOM_M_CANNOT_TELL_TIME, "You cannot see the sky to make such " +
            "a determination.\n");
    add_prop(ROOM_NO_TIME_DESC, 1);
    
    seteuid(getuid(TO));
    clone_object(COMMON_OBJ_DIR + "iron_cage")->move(TO);
    reset_room();
}

void
init()
{
    ::init();
    add_action("drink", "drink");
    add_action(do_climb, "climb");
}

int
do_climb(string str)
{
    if (!strlen(str))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(str, ({}), " [up] [the] [stone] 'bridge'")
            && str != "up")
    {
        notify_fail("Climb where? Up the stone bridge?\n");
        return 0;
    }

    if (TP->resolve_task(TASK_ROUTINE, ({SS_CLIMB, TS_STR, TS_DEX})))
    {
        write("You pull yourself up on the bridge.\n");
        say(({
            METNAME + " climbs up on top of the bridge.\n",
            TART_NONMETNAME + " climbs up on top of the bridge.\n",
            "You hear the sounds of someone climbing up the bridge.\n"
        }));
        TP->move_living("M", FOREST_DIR + "wforest84", 1);
        say(({
            METNAME + " climbs up from the side of the bridge.\n",
            ART_NONMETNAME + " climbs up from the side of the bridge.\n",
            "You hear sounds of movement on the bridge.\n"
        }));
    }
    else
    {
        write("You try to pull yourself up on the bridge, but fail to find " +
            "a good handhold.\n");
        say(({
            METNAME + " tries to climb up on the bridge, but fails.\n",
            TART_NONMETNAME + " tries to climb up on the bridge, but fails.\n",
            "Your hear the sounds of someone trying to climb up the bridge, " +
            "but it doesn't sound like they succeeded.\n"
        }));
    }
    return 1;
}

int
drink(string str)
{
    object obj = TP;
    if (str == "from stream")
    {
        write("Ahh! Refreshing!\n");
        say(QCTNAME(obj) + " drinks from the stream.\n",obj);
        obj->drink_soft(300);
        return 1;
    }
    notify_fail("Drink from what? The stream?\n");
    return 0;
}

void
reset_room()
{
    if(!knight)
    {
        knight = clone_object("/d/Raumdor/common/npc/death_knight");
        knight->move_living("M",TO);
        tell_room(TO, "A "+knight->short() + 
                " drops down from above with a heavy clank!\n");
    }
}

// Prevent this
void
call_monsters(object player, object location)
{
    return;
}

int *
query_coordinates()
{
    return ({12, 3, -1});
}
