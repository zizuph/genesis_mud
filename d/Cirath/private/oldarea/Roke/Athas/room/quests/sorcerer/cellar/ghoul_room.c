inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <macros.h>
 
#define NUM	5

	object *ghoul;
 
void make_monster(int i)
{
	ghoul[i]=clone_object(A_NPC_D+"ghoul");
    ghoul[i]->move(this_object());
}

void reset_room()
{
    int i;
    for(i=0; i<NUM; i++)
	if(!ghoul[i])
	    call_out("make_monster", 1, i);
}

create_room()
{
	object door;
	ghoul = allocate(5);

    set_short("Nifty dark room");
	set_long(BSS("This room is dark and cold, there is no light here, and "+
		"you can hear sounds all over. There is a small sign here, but "+
		"you don't feel like sticking around to read it.\n"));

	add_item(({"sign","sign"}),BSS(
		"The sign have some writing on it, you might want to read "+
		"it. But since you look at the sign, you now know more "+
		"about it; It is made of steel, it must have been created "+
		"by a blacksmith, and it is nice crafted. The writing "+
		"is stamped into the sign, making it impossible to remove "+
		"without removing or damaging the sign. Also, you see some "+
		"biting marks on the top, and on the sides of the sign. "+
		"By these biting marks, you understand that the creature who "+
		"obviously has created them, have to have a wide mouth, "+
		"sharp teeth, and cannot be to tall. The sign is planted into "+
		"the ground, so that it is impossible to pick up, besides "+
		"you estimate the sign to be somewhat heavy.\n"));

    add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
 
    call_out("reset_room", 1);

	door = clone_object(DOOR_D+"stone_door_b");
    door->move(this_object());
    door->set_key(230686);
}

init()
{
    ::init();
    add_action("do_read","read");
}

int
do_read(string str)
{    
    if (!str)
    return 0;

    if (str != "sign")
    {
       notify_fail("What do you want to read ?");
       return 0;
    }
    
	write("You read:\n           Do not feed the ghouls.\n");
	say(QCTNAME(this_player())+" reads the sign.\n");
    return 1;

}
