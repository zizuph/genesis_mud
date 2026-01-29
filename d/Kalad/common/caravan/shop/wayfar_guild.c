#include "../default.h"
inherit CVAN_ROOM;
#include "/d/Kalad/sys/outlaw.h"

#define STEP "@@step:/d/Kalad/common/caravan/step"

void
create_cvan_room()
{
    (CVAN + "step")->load();

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Wayfarer's Guild");
    set_long("\n   This is the Kalad Wayfarer's Guild, " +
      "a place for travellers and tourists to " +
      "exchange tales and pick up information about " +
      "the city.\n"+
      "   East is a training room, where you " +
      "can learn and improve skills. A door to the south " +
      "leads out to the street, while to the north, you notice "+
      "a small and cozy room. On the wall, there is a " +
      "sign giving some basic tips about Kabal, a plaque and a "+
      "Wanted List with the names of outlaws in the city.\n\n");

    set_hear_bell(1);

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    add_item(({"sign", "tips"}), "@@tips_long");
    add_item(({"list", "wanted list"}), "@@wanted_long");
    add_item(({"plaque"}), "@@plaque_long");

    add_exit(CVAN + "wayfar/s4", "south", STEP);
    add_exit(CVAN + "shop/w_g_train", "east");
    add_exit(CVAN + "shop/wayfar_common", "north");

    clone_object(CVAN + "shop/kabal_board")->move(TO);
    clone_object(CLONE + "clocks/gfather")->move(TO);

    set_alarm(60.0, 0.0, "room_events");
}

room_events()
{
    switch(random(20))
    {
    case 0:
	tell_room(TO, "A dirt-laden stranger walks in, examines the board "+
	  "then leaves.\n");
	break;
    case 1:
	tell_room(TO, "A cloaked group of wanderers arrives, and after a "+
	  "few minutes, leaves.\n");
	break;
    case 2:
	tell_room(TO, "The ticking of the clock fills the room.\n");
	break;
    case 3:
	tell_room(TO, "A small thief arrives and leaves east.\n");
	break;
    case 4:
	tell_room(TO, "A burly warrior arrives and leaves east.\n");
	break;
    case 5:
	tell_room(TO, "A small thief arrives and leaves south.\n");
	break;
    case 6:
	tell_room(TO, "A burly warrior arrives and leaves south.\n");
	break;
    case 7:
	tell_room(TO, "A fat jolly man waddles in, takes a look at the "+
	  "plaque and hurriedly leaves south.\n");
	break;
    case 8:
	tell_room(TO, "A mysterious robed figure appears, glances at the "+
	  "board and leaves south.\n");
	break;
    case 9:
	tell_room(TO, "The murmur of a crowd reaches your ears.\n");
	break;
    case 10:
	tell_room(TO, "A youthful dwarf arrives peering around the room then "+
	  "heads outside.\n");
	break;
    case 11:
	tell_room(TO, "A shiftless gnome slides past you.\n");
	break;
    case 12:
	tell_room(TO, "A hooded stranger bumps into you on his way out.\n");
	break;
    case 13:
	tell_room(TO, "A small brown rat starts chewing on your foot, then "+
	  "hurriedly departs.\n");
	break;
    case 14:
	tell_room(TO, "An elegantly dressed woman passes you on her "+
	  "way out.\n");
	break;
    case 15:
	tell_room(TO, "A road-weary merchant arrives and leaves east.\n");
	break;
    case 16:
	tell_room(TO, "A scream sounds from the south.\n");
	break;
    case 17:
	tell_room(TO, "A dirty-looking dog arrives and begins sniffing "+
	  "you. It leaves before you can get a look at it.\n");
	break;
    case 18:
	tell_room(TO, "The wood of the building creaks slightly.\n");
	break;
    case 19:
	tell_room(TO, "A dark-skinned figure brushes past you.\n");
	break;
    case 20:
	tell_room(TO, "A drunken guard arrives and stumbles out the door.\n");
	break;
    }

    set_alarm(60.0, 0.0, "room_events");
}

string
wizinfo()
{
    return BS(
      "There is a list here of all the players that " +
      "are outlaws in Kabal. If for some reason you " +
      "need to do so, you can outlaw or pardon a " +
      "player in this room. The commands 'outlaw <playername>' " +
      "and 'pardon <playername>' will do this but only " +
      "work for characters in good standing within the city. Please only use these for good"+
      "cause or they won't be available to everyone in " +
      "the future.\n");
}

int
pardon(string str)
{
    object player;

    /* if(!TP->query_wiz_level()) */
    if(TP->query_alignment() < 500)
	return 0;

    NF("Pardon whom?\n");
    if (!str)
	return 0;

    NF(C(str) + " is not on right now.\n");
    if(!(player = find_player(str)))
	return 0;

    NF(C(str) + " is not an outlaw!\n");
    if (!IS_OUTLAW(player))
	return 0;

    write("You remove " + player->query_name() + " from the outlaw list.\n");
    UNOUTLAW(player);
    return 1;
}

int
outlaw(string str)
{
    object player;

    if(TP->query_alignment() < 500)
	return 0;

    NF("Outlaw whom?\n");
    if (!str)
	return 0;

    NF(C(str) + " is not on right now.\n");
    if(!(player = find_player(str)))
	return 0;

    NF(C(str) + " is already an outlaw!\n");
    if (IS_OUTLAW(player))
	return 0;

    write("You add " + player->query_name() + " to the outlaw list.\n");
    ADD_OUTLAW(player);
    return 1;
}

string
wanted_long()
{
    return "\n     WANTED:\n----------------\n\n" +
    sprintf("%-#70s", implode(OUTLAWS, "\n"));
}

string
tips_long()
{
    return
    "   Welcome to the city of Kabal and the domain\n" +
    "of Kalad. This is where you can write notes\n" +
    "concerning this city which will be read and\n" +
    "replied to by the wizard's of Kalad. Tips for\n" +
    "those new to the city will be posted here but\n" +
    "the majority of clues and other useful\n" +
    "information will have to be gained by exploration.\n"+
    "   When exploring the city, you may want to\n" +
    "type 'speak < npc name >' to talk to the\n" +
    "inhabitants and learn valuable information.\n" +
    "<npc name> can be up to 4 words. 1 of these 4\n" +
    "words must be a name, with the 3 optional\n" +
    "words including at most 2 adjectives and\n" +
    "1 other name. Examples are 'fat ugly bob brunley', \n" +
    "'thin human', 'guard', 'small hairy troll', and\n" +
    "'wise wemis wayne'.\n" +
    "   There is no night in Kalad. That is, it doesn't get\n" +
    "dark but there are still off-hours when the inhabitants\n" +
    "sleep and many businesses close. You can type the command\n" +
    "<time> for a rough estimate of the time of day, anywhere\n" +
    "in the city, though you'll get a more accurate idea by\n" +
    "looking at a clock.\n" +
    "        Good Luck and Happy Travelling!\n";
}

string
plaque_long()
{
    return
    "   The list of outlaws may be added to by anyone of good standing\n"+
    "within the city. To add someone to the outlaw list simply type\n"+
    "outlaw <playername>. To remove someone from the outlaw list just\n"+
    "type pardon <playername>. This is a privilege granted to you by\n"+
    "the city council. Should there be _ANY_ misuse of this\n"+
    "privilege, such as outlawing innocents, then this privilege\n"+
    "shall be revoked immediately. Persons outlawing individuals are\n"+
    "dutifully encouraged to post a note on the board stating the\n"+
    "reason for the outlaw.\n";
}

int
do_read(string str)
{
    NF("Read what?\n");
    if (!str || str == "")
	return 0;

    if (str == "wanted list" || str == "list")
    {
	write(wanted_long());
	return 1;
    }

    else if (str == "sign" || str == "tips")
    {
	write(tips_long());
	return 1;
    }

    else if (str == "plaque")
    {
	write(plaque_long());
	return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    AA(do_read, read);
    AA(outlaw, outlaw);
    AA(pardon, pardon);
}
