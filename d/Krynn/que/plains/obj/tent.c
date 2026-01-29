/* An army tent
 *
 * Aridor 08/97
 *
 * Navarre November 2010 : Tent was used for abuse on Nazgul and Yeti.
 *                         I have fixed it so you cannot enter it until
 *                         you are relaxed from previous combat.
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>

int setup = 0;
string tent_inside;
string packed_short,
       packed_long, 
       unpacked_short,
       unpacked_long;

int setup_by_player = 0;

/* prototypes */
void set_packed_short(string str);
void set_packed_long(string str);
void set_unpacked_short(string str );
void set_unpacked_long(string str);
void set_tent_inside(string str);

#define DEBUG find_player("arman")->catch_msg("[tent] " + x + "\n")

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

    set_tent_inside("/d/Krynn/que/plains/obj/tent_inside");
}

void
create_object()
{
    set_name("tent");
    add_name("bundle");
    set_adj("army");
    add_adj("mobile");
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_WEIGHT, 20000);
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

object
query_tent_inside()
{
    if (tent_inside)
      return find_object(tent_inside);
    
    return 0;
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
ld_in_tent(object ob)
{
    int in_tent;
    string tent_room = file_name(query_tent_inside());

    in_tent = wildmatch(tent_room, ob->query_prop("_player_s_ld_in_room")); 

    if (in_tent)
    {
	return 1;
    }

    return 0;
}

int
pack(string str)
{
    /*string dummy;*/
    mixed obarr;

    NF("Pack what?\n");
    if (!str)
      return 0;

    obarr = FIND_STR_IN_OBJECT(str,E(TP));
    if (!obarr || sizeof(obarr) != 1 || obarr[0] != TO)
      return 0;
    /*if (sscanf(str,"%stent%s",dummy,dummy) != 2)
      return 0;*/

    NF("The tent is already packed up.\n");
    if (!setup)
      return 0;

    if (tent_inside && find_object(tent_inside) &&
	sizeof(all_inventory(find_object(tent_inside))))
    {
	write("There is still someone or something inside the tent. " +
	      "You can't pack it that way.\n");
	return 1;
    }

    if(sizeof(filter(users(), ld_in_tent)))
    {
	write("There is someone lost in the void who starts in the tent. " +
	    "You can't pack it away until they return or have left the realms.\n");
	return 1;
    }

    if(sizeof(filter(all_inventory(find_object("/d/Genesis/obj/statue")), 
        ld_in_tent)))
    {
	write("There is someone lost in the Void who starts in the tent. " +
	    "You can't pack it away until they return or have left the realms.\n");
	return 1;
    }

    write("You pack the tent and roll it into a compact bundle.\n");
    say(QCTNAME(TP) + " packs up a tent and rolls it into a compact bundle.\n");
    remove_prop(OBJ_M_NO_GET);
    add_prop(OBJ_I_VOLUME, 10000);
    (tent_inside)->remove_exit("out");
    setup = 0;
    setup_by_player = 0;
    return 1;
}

int
setup(string str)
{
    /*string dummy;*/
    mixed obarr;

    NF("Setup what?\n");
    if (!str)
      return 0;

    if (str[0..1] == "up")
      str = str[3..];

    obarr = FIND_STR_IN_OBJECT(str,E(TP)) + FIND_STR_IN_OBJECT(str,TP);
    if (!obarr || sizeof(obarr) != 1 || obarr[0] != TO)
      return 0;
    /*if (sscanf(str,"%stent%s",dummy,dummy) != 2)
      return 0;*/

    NF("The tent is already set up.\n");
    if (setup)
      return 0;
    
    NF("You can't set the tent up indoors!\n");
    if (E(TP)->query_prop(ROOM_I_INSIDE))
      return 0;

    NF("The ground is too frozen here to setup the tent.\n");
    if (file_name(E(TP)) == "/d/Krynn/icewall/castle2/rooms/ice_clearing2")
      return 0;

    move(E(TP),1); /* just to make sure. */
    
    if (interactive(TP))
    {
        setup_by_player = 1;
    }

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
    /*string dummy;*/
    mixed obarr;

    /* If the tent is packed together, you can't enter it. */
    NF("What?\n");
    if (!setup)
      return 0;

    NF("Enter what?\n");
    if (!str)
      return 0;
    
    obarr = FIND_STR_IN_OBJECT(str,E(TP));
    if (!obarr || sizeof(obarr) != 1 || obarr[0] != TO)
      return 0;
    /*if (sscanf(str,"%stent%s",dummy,dummy) != 2)
      return 0;*/

    NF("It is impossible to enter the tent. You find no entrance!\n");
    if (!stringp(tent_inside))
      return 0;

    if (setup_by_player &&
        !TP->query_relaxed_from_combat())
    {
      NF("Due to your recent combat, you decide to wait a while before " +
         "entering the tent. You could be followed.\n");
      return 0;
    }

    E(TO)->set_dircmd(str);
    TP->move_living("into the tent",tent_inside);
    /*say(QCTNAME(TP) + " enters.\n");*/
    return 1;
}
