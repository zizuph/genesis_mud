/*
 * Dust 920813: this room is entered as soon as you loose your path
 * through the maze and puts you back to the entrance with a probability
 * of 10% and keeps you in with a probability of 90%
 */
inherit "/std/room";
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define THISROOM COLDIR + "maze_exit"
#define OUTROOM  COLDIR + "maze_entrance"

create_room()
{
    set_short("maze");
    set_long(break_string("You feel a bit nauseous in this room... " +
	"there's nothing here that could help you finding your way through " +
	"this maze. The floor is foggy and swallows everything lying on " +
	"the floor.\n", 70));
    add_exit("@@select","north",0);
    add_exit("@@select","east",0);
    add_exit("@@select","south",0);
    add_exit("@@select","west",0);
    add_prop(ROOM_I_NO_MAGIC, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
}

/* tidy_up() makes sure all dropped objects are removed (no orientation) */
tidy_up()
{
    object *op;
    int i;

    op = all_inventory(this_object());
    for (i=0; i<sizeof(op); i++)
	if (!interactive(op[i]))
	    (op[i])->remove_object();
}

string
select()
{
    int damage;

    tidy_up();
    if (random(10)) return THISROOM;
    write(break_string("As you leave the room, the floor under your feet " +
	"dissolves and you drop through a long tunnel... after some time " +
	"you land on a very hard floor. OUCH!!! You cry of pain...\n",70));
    damage = this_player()->query_max_hp()/3;
    if (damage < 200) damage = 200;
    this_player()->reduce_hit_point(damage);
    if (this_player()->query_hp() <= 0) this_player()->do_die(this_object());
    return OUTROOM;
}

