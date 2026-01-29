/*
 * temple.c
 * Inner Sanctum of the Seeker Temple
 * Haven town
 * Created by Tibbit, 11 Mar 1998
 */

#include "../local.h"

inherit HAVENINBASE;

object seeker1,seeker2;

void
enter_inv(object ob,object from)
{
    object t;

    ::enter_inv(ob,from);

    if((interactive(ob)) &&
        ((t = present("tour8",ob))))
    {
        set_alarm(1.0,0.0,"do_tour",ob,t);
    }
}

void
do_tour(object ob,object t)
{
    t->set_arr("temple");

    ob->catch_msg("This is the temple you were told to "+
        "to find by the Solace Questmaster.  You may return "+
        "to him for your reward.\n");

}

void
reset_haven()
{
    reset_euid();

    if(!seeker1)
        (seeker1 = clone_object(HNPC+"seeker"))->move(TO);

    if(!seeker2)
        (seeker2 = clone_object(HNPC+"seeker2"))->move(TO);


}

void
create_haven()
{
    set_short("Inner sanctum of the Seekers' Temple");

    set_long("By far the most impressive room in town, you stand "+
        "at the center of the temple of the Seekers in haven. "+
        "The ceiling arches away, and everything is a gleaming white, "+
        "save the heavily varnished pews themselves. The religious "+
        "center of much of Abanasinia, you definitely feel something "+
        "unusual in this room."+
        "\n");

    add_item(({"building","temple"}),
        "This is the temple of the Seekers, the largest and finest "+
        "buiding in the town of Haven.\n");
    add_item(({"paint","painting","white","wall","walls"}),
        "The walls of this building are painted gleaming white, "+
        "in contrast to the wood-colored homes of the local citizens.\n");
    add_item(({"vestibule","entryway"}),
        "The entryway of the Seekers' temple is to the west.\n");
    add_item(({"pew","pews","varnish","varnished pews"}),
        "The pews are all alike, simple wooden benches. These have been "+
        "heavily varnished, and they shine as the light glances off "+
        "them.\n");
    add_item(({"ceiling","arch","arches"}),
        "The ceiling of this room is a great connection of four large "+
        "arches, an impressive architectural feat when compared to "+
        "the rest of this small and simple village.\n");

    add_exit(HROOM+"vestibule","west");

}

