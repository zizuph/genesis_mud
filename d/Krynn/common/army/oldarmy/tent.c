/* An army tent */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <macros.h>

int setup = 0;
string tent_inside;
string packed_short,
       packed_long, 
       unpacked_short,
       unpacked_long;

/* prototypes */
void set_packed_short(string str);
void set_packed_long(string str);
void set_unpacked_short(string str );
void set_unpacked_long(string str);



void
create_tent()
{
    set_packed_short("tent bundle");
    set_packed_long("This is a bundle of a soft material. Apparently it can " +
		    "be set up into a tent.\n");

    set_unpacked_short("large army tent");
    set_unpacked_long("A fairly large tent, which can easily hold several " +
		      "people. It is possible to enter the tent through the " +
		      "entrance, but you could also just pack the tent and " +
		      "walk off with it.\n");
}

void
create_object()
{
    set_name("tent");
    add_name("bundle");
    set_adj("army");
    add_adj("mobile");
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_SELL,1);
    create_tent();
    set_short("@@my_short@@");
    set_long("@@my_long@@");
}

void
init()
{
    ADA("pack");
    ADA("setup");
    ADD("setup","set");
    ADA("enter");
    ::init();
}

void
set_packed_long(string str)
{
    packed_long = str;
}

void
set_unpacked_long(string str)
{
    unpacked_long = str;
}

void
set_packed_short(string str)
{
    packed_short = str;
}

void
set_unpacked_short(string str)
{
    unpacked_short = str;
}

void
set_tent_inside(string str)
{
    if (tent_inside)
      return;
    seteuid(getuid(TO));
    tent_inside = file_name(clone_object(str));
}

string
my_long()
{
    if (setup)
      return check_call(unpacked_long);
    return check_call(packed_long);
}

string
my_short()
{
    if (setup)
      return check_call(unpacked_short);
    return check_call(packed_short);
}

int
pack(string str)
{
    string dummy;

    NF("Pack what?\n");
    if (!str)
      return 0;
    if (sscanf(str,"%stent%s",dummy,dummy) != 2)
      return 0;

    NF("The tent is already packed up.\n");
    if (!setup)
      return 0;

    NF("There is still someone or something inside the tent. You " +
       "can't pack it that way.\n");
    if (tent_inside && find_object(tent_inside) &&
	sizeof(all_inventory(find_object(tent_inside))))
      return 0;

    write("You pack the tent and roll it into a compact bundle.\n");
    say(QCTNAME(TP) + " packs up a tent and rolls it into a compact bundle.\n");
    remove_prop(OBJ_M_NO_GET);
    add_prop(OBJ_I_VOLUME, 10000);
    (tent_inside)->remove_exit("out");
    setup = 0;
    return 1;
}

int
setup(string str)
{
    string dummy;

    NF("Setup what?\n");
    if (!str)
      return 0;
    if (sscanf(str,"%stent%s",dummy,dummy) != 2)
      return 0;

    NF("The tent is already set up.\n");
    if (setup)
      return 0;
    
    NF("You can't set the tent up indoors!\n");
    if (E(TP)->query_prop(ROOM_I_INSIDE))
      return 0;

    move(E(TP),1); /* just to make sure. */

    write("You roll out the tent pack and set up the tent.\n");
    say(QCTNAME(TP) + " rolls out a bundle and sets it up into a tent!\n");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_VOLUME, 16000000); /* 2*4*2 meters */
    (tent_inside)->add_exit(file_name(E(TO)),"out");
    setup = 1;
    return 1;
}

int
enter(string str)
{
    string dummy;

    /* If the tent is packed together, you can't enter it. */
    NF("What?\n");
    if (!setup)
      return 0;

    NF("Enter what?\n");
    if (!str)
      return 0;
    if (sscanf(str,"%stent%s",dummy,dummy) != 2)
      return 0;

    NF("It is impossible to enter the tent. You find no entrance!\n");
    if (!stringp(tent_inside))
      return 0;

    E(TO)->set_dircmd("tent");
    TP->move_living("into the tent",tent_inside);
    /*say(QCTNAME(TP) + " enters.\n");*/
    return 1;
}
