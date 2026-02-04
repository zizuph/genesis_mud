/* silver mine , common features */
/* dust 921105 */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

int resources;

#ifdef ADDS
ADDS
#endif

reset_room() {
#ifdef RESETADD
RESETADD
#endif
    resources = 10;
}


create_room()
{
    set_short("silver mine");
    set_long(BS("You are in a very low and narrow part of an underground " +
	"cave. It's very difficult to walk here, and if you trip you'll " +
	"probably hurt yourself, so take care!! The walls here don't look " +
	"untouched... It seems this used to be a mining area a long " +
	"time ago. You can even see some veins in the wall.\n"));
    /* EXITS: mine-specific exits, macro in real room  */
    EXITS
    add_item("floor",BS("The floor looks extremely stony and it's very " +
	"difficult to walk on it without tripping. And if you fall, you'll " +
	"probably hurt yourself...\n"));
    add_item(({"walls","wall"}),
	BS("The walls seem having been mined a long time ago. " +
	"You can still see some traces in the wall that look like veins.\n"));
    add_item(({"veins","vein"}),"@@check_veins");
    add_item("silver",BS("You try to scrape some silver out of the vein, " +
	"but without appropriate tools you have no chance.\n"));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,0);
    reset_room();
}

string
check_veins()
{
    return(
	BS("Those veins in the wall look like silver veins. " +
	(resources ? 
	("You don't find many of them, but you imagine there's still some " +
	 "silver that could be gained here.\n")
	: ("However, those veins seem to be already exhausted.\n"))));
}

check_boots()
{
    object *boots;
    int i,flag;

    boots = all_inventory(this_player());
    flag = 0;
    for (i=0; i<sizeof(boots); i++)
	if (boots[i]->query_prop("_mining_boots") && boots[i]->query_worn())
	    {flag++; break;}
    if (flag) return 0;
    write("As you leave the room, you trip and hurt yourself... OUCH!!\n");
    say(QCTNAME(this_player()) + " falls, and cries out in pain!\n");
    this_player()->reduce_hit_point(40);
    this_player()->do_die();
    return 0;
}

init()
{
    ::init();
    add_action("do_chisel","chisel");
    add_action("do_chisel","hit");
    add_action("do_chisel","mine");
    add_action("do_chisel","break");
#ifdef INITADD
INITADD
#endif
}

int
do_chisel(string str)
{
    string *arr;
    int i,flag;
    object nugget,gem;

    notify_fail("Yes, but what you try to chisel exactly?\n");
    if (strlen(str) < 3) return 0;
    arr = explode(str," ");
    if (arr[0] != "wall" && arr[0] != "walls" && arr[0] != "stones" &&
	arr[0] != "vein" && arr[0] != "veins" && arr[0] != "silver") return 0;
    notify_fail("You try to chisel the the wall with your bare hands, " +
	"but with no success.\n");
    for (i=1, flag=0; i<sizeof(arr); i++)
	if (arr[i] == "chisel") {flag++; break;}
    if (!flag) return 0;
    notify_fail("But you don't have any chisel...\n");
    if ((!present("chisel",this_player())) &&
	(!present("/d/Terel/mecien/mountains/chisel",this_player()))) return 0;
    notify_fail("You try to chisel, but you feel too weak to do so.\n");
    if (this_player()->query_fatigue() < 30) return 0;
    this_player()->add_fatigue(-10);
    if (resources) {
	resources--;
	write("You chisel the wall, and succeed in gaining a silver nugget.\n");
	if (random(30) == 10) {
	    write("Behind the nugget you just gained, you can see a blue " +
		"gem.\n");
	    gem = clone_object(MANSION + "obj/blue_gem");
	    gem->move(this_object());
	}
	say(QCTNAME(this_player()) + " chisels the wall and gains a " +
	    "silver nugget.\n");
	nugget = clone_object(MANSION + "obj/silver_nugget");
	nugget->move(this_object());
	return 1;
    }
    write("You chisel the wall, but the silver resources seem to be " +
	"exhausted.\n");
    say(QCTNAME(this_player()) + " chisels the wall, but the silver " +
	"resources seem to be exhausted.\n");
    return 1;
}
