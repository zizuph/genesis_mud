#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>

inherit FOREST_IN;
object banner, knight, knight2;
string message = "The banner can probably be removed if you wish, or "+
"replaced, as the case may be.\n";

#define KNIGHT_NPC "/d/Krynn/solamn/vin/std/vin_knight_base"

string
extra_desc()
{
    if (P(banner, TO))
	return "A "+banner->short()+" decorates the wall.\n";
    else
	return "\n";
}

void
reset_flotsam_room()
{
    if(!knight)
    {
	knight = clone_object(KNIGHT_NPC);
	knight->move(TO);
    }
    if (!knight2)
    {
	knight2 = clone_object(KNIGHT_NPC);
	knight2->move(TO);
    }
}

string
banner()
{
    if (P(banner, TO))
	return "A "+banner->short()+" decorates the wall here. "+
	message;
    else
	return "Examine what?\n";
}

string
banners()
{
    return extra_desc() + message;
}

create_flotsam_room()
{
    set_short("Secret Hallway of the Knight Circle");
    set_long("@@long_descr");

    add_item(({"torch", "torches"}), "The torches on the walls provide "+
      "little, but sufficient, light.\n");
    add_item(({"doorway", "door"}), "The door leads out of this secret "+
      "hallway, and is guarded by two knight guards.\n");

    add_exit(FROOM + "startroom", "west");
    add_exit(FROOM + "new_office", "east", "@@exit_message");

    banner = clone_object(FOBJ + "copper_banner");
    banner->set_no_show();
    banner->move(TO);

    add_item(({"banner", "banners"}), "@@banners");
    add_item("copper banner", "@@banner");

    reset_flotsam_room();
}

void
exit_message()
{
    object room;

    write("The knights open the hidden doorway, and let you through.\n");
    room = find_object(FROOM + "new_office");
    if (!room->query_prop("_room_my_door_is_open"))
	tell_room(room, "The tapestry-covered back wall opens just "+
	  "enough to let someone out, then slams shut again.\n");
}

string
long_descr()
{
    return "This hallway is dim, the torches on the walls provide what "+
    "little light there is. It leads west from here, and the guards "+
    "here vigilantly watch the door on the east wall, leading out of "+
    "the secret hallway. "+extra_desc();
}

init()
{
    add_action("replace", "replace");
    add_action("remove", "remove");
    ::init();
}

int
replace(string str)
{
    object ob;

    NF("Replace what? A banner?\n");
    if (!str)
	return 0;

    parse_command(str, TO, " [the] %o ", ob);

    NF("Replace what?\n");
    if (ob != banner)
	return 0;

    NF("You don't have a banner, or you don't have the ones that go here.\n");
    if (!P(banner, TP))
	return 0;

    if (ob == banner && P(ob, TP))
    {
	banner->set_no_show();
	banner->move(E(TP));
	write("You replace the "+banner->short()+".\n");
	say(QCTNAME(TP)+" replaces the "+banner->short()+".\n");
	return 1;
    }
}

int
remove(string str)
{
    object ob;

    NF("Remove what? A banner?\n");
    if (!str)
	return 0;

    parse_command(str, TO, " [the] %o ", ob);

    if (ob != banner)
	return 0;

    NF("The "+banner->short()+" is not here.\n");
    if (ob == banner && !P(banner, TO))
	return 0;

    if (ob == banner)
    {
	banner->unset_no_show();
	banner->unset_no_show_composite();
	banner->move(TP);
	write("You gently take the "+banner->short()+" from the wall.\n");
	say(QCTNAME(TP)+" gently takes the "+banner->short()+" from the "+
	  "wall.\n");
	return 1;
    }
}


