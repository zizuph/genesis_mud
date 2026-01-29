inherit "/std/room";
inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Emerald/carriages/carriage.h"
#include <ss_types.h>
#include <chapel.h>

/* Prototypes */
int flowers_left  = 15;
int CarriageExists = 0;
string PlaqueText();
int ThrowCoins(string str);
void GoodThrow();
void BadThrow();
int ReadPlaque(string str);
int pick_flower(string arg);
int illegal(string arg);

void
create_room()
{
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(IS_CARRIAGE_STOP, 1);
    set_short("Chapel garden");

    set_long("   You stand in a beautifully terraced garden outside "+
      "of the chapel. There is a smooth stone path that wanders north "+
      "from the gate to the doors of the chapel. It also branches off " +
      "and winds its way along a small creek and over a small stone bridge. "+
      "There is a small pond here, being fed by the small creek that winds its way "+
      "back to the gazebo you can see in the distance. Next to the "+
      "pond is a new wooden pedestal with a plaque mounted on top. You"+
      " notice "+
      "that the branch of the path follows the direction of the creek back " +
      "to the far garden.\n\n");

    add_item(({"flower", "flowers"}), "The flowers are absolutely " +
      "breathtaking! There are hundereds of varieties all swaying " +
      "softly in the breeze which surrounds the garden. The blossoms of the  " +
      "flowers seem to beckon to you. Perhaps you could pick one?\n");
    add_item(({"tree", "trees"}), "The trees stand magestically as a  "+
      "border around the entire garden. Their dark green foliage blends " +
      "in harmony with the vibrant colours of the flowers.\n");
    add_item(({"path", "stone", "stones", "ground"}), "The path "+
      "is made of smooth polished stones. The path winds its " +
      "way along the creek and over a small stone bridge, " +
      "winding around the far garden before returning.\n");
    add_item(({"pond", "pool"}), "The pond is crystal clear "+
      "water with sunlight shimmering off of the surface. You " +
      "notice small bubbles on the surface of the water and when " +
      "you take a closer look you can see a school of brightly coloured fish "+
      "swimming and playing close to the surface of the water.\n");
    add_item(({"door", "doors"}), "The chapel doors are made of a " +
      "dark, highly polished wood. The door handles are crafted from crystal, "+
      "fragile looking, yet extremely durable.\n");
    add_item("gazebo","In the distance you see a small white gazebo surrounded by a beautiful garden, not unlike the one you are standing in.\n");
    add_item("creek","This creek is really nothing more that a trickle of water connecting the ponds in the two gardens.\n");
    add_item("bridge","This small bridge is crafted from stones and crosses the creek.\n");
    add_item("garden","As you look at the flowers and trees you can't "+
      "help but think how appropriate it's beauty is "+
      "for being outside of a wedding chapel.\n");
    add_item("gate","You notice the small gate you passed through to "+
      "enter the garden. It seems to stay perpetually ajar.\n");
    add_item(({"pedestal","new pedestal","plaque"}), "The pedestal"+
     " and the plaque themselves are not too interesting..try"+
      " reading the plaque.\n");

    add_exit(VILLAGE_DIR + "centre", "southwest", 0);
    add_exit(CHAPEL_DIR + "rectory", "enter", "@@check_thrown_out");
    add_exit(CHAPEL_DIR + "outside_chapel","bridge","@@b_msg@@");
}

int
check_thrown_out()
{
    if (TP->query_prop(THROWN_OUT) > 2) {
	write("You step up to the doors, but they didn't open. " +
	  "Seems you aren't wanted there.\n");
	say(QCTNAME(TP) + " tries to enter the chapel, " +
	  "but cannot open the door.\n");
	return 1;
    }
    write("As you step up to the doors, they magically open.\n");
    write("After you have passed, they silently close.\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(illegal, "defile");
    add_action(pick_flower,"pluck");
    add_action(pick_flower,"pick");
    add_action(illegal, "destroy");
    add_action("ReadPlaque", "read");
    add_action("ThrowCoins", "throw");
}

int
illegal( string arg )
{
    int i;

    NF(capitalize(query_verb()) + " what?\n");
    if (!arg)
	return 0;
    for ( i=0 ; i<sizeof(obj_items) ; i++ )
	if (member_array(arg, obj_items[i][0]) >= 0) {
	    write("That wasn't too smart...!\n");
	    TP->add_tmp_stat(SS_STR, 10 - TP->query_stat(SS_STR), 90);
	    TP->add_tmp_stat(SS_DEX, 10 - TP->query_stat(SS_DEX), 90);
	    TP->add_tmp_stat(SS_CON, 10 - TP->query_stat(SS_CON), 90);
	    TP->add_tmp_stat(SS_INT, 10 - TP->query_stat(SS_INT), 90);
	    TP->add_tmp_stat(SS_WIS, 10 - TP->query_stat(SS_WIS), 90);
	    TP->add_tmp_stat(SS_DIS, 10 - TP->query_stat(SS_DIS), 90);
	    return 1;
	}
    return 0;
}

int
pick_flower(string str)
{
    if (!str) return 0;

    if ( (str!="flower") && (str!="flowers") )
    {
	notify_fail("Pick What?\n");
	return 0;
    }
    if (!flowers_left)
    {
	notify_fail("You notice that there are no more grown flowers. "+
	  "Maybe you should wait until some grow back?\n");
	return 0;
    }
    clone_object("/d/Emerald/leah/chapel/obj/flower"+(random(3)+1))->move(TP, 1);
    flowers_left--;
    write("You pluck a flower from the ground.\n");
    say(QCTNAME(TP)+" plucks a flower from the ground.\n");
    return 1;
}

reset_room()
{
    flowers_left = 15;
}

int
b_msg()
{
    write("You step over the bridge toward the gazebo ... \n\n");
    say(QCTNAME(this_player())+" steps over the bridge toward the gazebo.\n");
    return 0;
}

string
PlaqueText()
{
    write("The plaque on the little wooden pedestal reads:\n"+
     "\nNewley weds are encouraged to take advantage our wedding"+
     " carriage services. Simply throw ten platinum coins into"+
     " the air to order a carriage.\n\nA note is hung on it saying:"+
     "  We are on holidy so please hold off your wedding or go without until"+
     " then.\n");
}

int
ReadPlaque(string str)
{
    if (str != "plaque")
        return 0;
    PlaqueText();
    return 1;
}

int
ThrowCoins(string str)
{
    object coin;
    int size;
    if (!str || str != "ten platinum"+
     " coins into the air")
    {
        notify_fail("Throw what where?\n");
        return 0;
    }

    if (!(coin = present("platinum coin", this_player())))
    {
        notify_fail("You don't have any platinum coins!\n");
        return 0;
    }

    if (CARRIAGECOST > (size = coin->num_heap()))
    {
        notify_fail("You don't have enough platinum coins!\n");
        return 0;
    }

    if (size == 10)
        coin->remove_object();
    else
        coin->set_heap_size(size-CARRIAGECOST);

    write("You throw the coins high into the air..\n");
    allbb(" throws some coins high into the air..\n");

    if (!CarriageExists)
        GoodThrow();
    else
        BadThrow();

    return 1;
}

void
BadThrow()
{
    object coin;

    coin = clone_object("std/coins");
    coin->set_coin_type("platinum");
    coin->set_heap_size(CARRIAGECOST);
    coin->move(environment(this_player()));

    write("..and they land on the ground a few feet away. It seems"+
     " the carriage service is on duty elsewhere for the moment.\n");
    allbb(" frowns as "+ this_player->query_possessive()+ " coins"+
     " fall to the ground.");
}

void
GoodThrow()
{
    object carriage;
     carriage = clone_object(CARRIAGE_PATH + "wedding_carriage");
    carriage->start_carriage();
    carriage->move(environment(this_player()));
    CarriageExists = 1;

    write("..and they are caught out of the air by a halfling!"+
     " You are startled to suddenly notice a stationary white"+
     " carriage next to you!\n");
    allbb(" jumps two feet into the air as " + 
     this_player()->query_possessive()+ " suddenly notices"+
     " the white carriage and a halfling pocketing the coins"+
     ". Wait a minute! Where did the carriage come from anyway?\n");
}
