/* created by Aridor 02/09/94 */

#include "../local.h"

inherit MININGROOM;

#define WHOAMI  2 /*I am this blocklocation*/

object form;
int how_many;

void
create_mining_room()
{
    set_my_long("");
    add_exit(THEIWAR + "r30","northeast");
    add_exit(THEIWAR + "r27","south");
    what1 = "carbon";
    what2 = "silver";
    set_alarm(5.0,0.0,"reset_room");
}

void
reset_mining_room()
{
    num1 = random(4);
    num2 = random(2);

    if (form && !form->query_prop(OBJ_I_BROKEN))
    return;
    form = clone_object(OBJ + "formblock");
    form->add_prop(OBJ_I_HIDE, 20 + random(20));
    restore_object(NUMBER_SOLVED);
    if (how_many % NUM_BLOCK_LOCATIONS == WHOAMI)
    form->set_produce(OBJ + "cogwheel");
    else
    form->set_produce(PRODUCE[random(sizeof(PRODUCE))]);
    form->move(TO);

}

