
#define CREATEADD \
    add_exit(MANSION + "crt/Dive21","west","@@try_hor"); \
    reset_room();

#include "Dive.h"

object gold;


reset_room()
{
    if (!gold || !present(gold,this_object()))
    {
/* Doesn't exist any longer.. Mortricia 
	gold = clone_object(MECIENDIR + "valley/guild/quest/gold");
	gold->move(this_object());
 */
    }
}

