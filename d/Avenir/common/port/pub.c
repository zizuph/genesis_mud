// file name:        pub.c
// creator(s):       Ilyian
// revision history: April 15, 1995
//                   Feb, 1996, updated it for Bakona's Hat quest
//		     Denis, Sep'96: Changes due to the port inheritance recode.
//                   Lilith Jun 2004: linking start areas from the bazaar here
//                     in preparation for adding areas of the village where the
//                     sybarites live.
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "port.h"
# include <money.h>

inherit "/std/room";
inherit "/lib/pub";
inherit "/lib/trade";
inherit "/d/Avenir/inherit/room_tell";

static object waitress;

static void stock();
string price_long();

# define MY_PRICES ({ 11, 13, 71, 189, 250, 1000 })

void
create_room()
{
    set_short("The Stormy Haven Inn and Pub");
    set_long("This room of the Stormy Haven Inn and Publick House has a "+
        "smoky, relaxed atmosphere to it, in stark contrast to the "+
        "raging port outside. The walls are hewn out of the natural rock "+
        "of the cavern, but they are " +
        "covered in thick tapestries and pictures. There is a simple " +
        "fireplace set into the south wall, and the mahogany bar is " +
        "to the north, above which is a menu. Scattered throughout " +
        "the room are small tables and chairs. A square doorway leads "+
        "north into the inn proper. You can hear the muted noise from the " +
        "stormy lake outside.\n");

    IN
    LIGHT

    stock();

    add_exit("port10", "south");
    add_exit(BAZAAR +"intr/inn", "north");

    seteuid(getuid(this_object()));
    clone_object(PORT + "obj/table.c")->move(this_object(),1);

    add_item(({ "pricelist", "list", "prices", "menu"}),
	     "It has a list of " +
             "popular drinks written on it in beautiful script.\n");

    add_item(({ "fire", "fireplace" }),
	     "The fire keeps the room warm and cozy, " +
             "a nice change from the biting wind outside.\n");

    add_item(({ "table", "tables" }),
	     "They are short round tables that stand on three legs.\n");

    add_item(({ "chair", "chairs "}),
	     "The chairs are wooden and seem to be of solid construction.\n");

    add_item("bar",
             "It is long and made from polished mahogany, with stools lined " +
             "up in front of it. Over the bar are shelves containing all " +
             "sorts of strange liquours, spirits, wines, and other drinks. A " +
             "pricelist hangs under the shelves with some of the more " +
             "popular drinks listed.\n");

    add_item(({ "tapestry", "tapestries" }),
	     "The tapestries are done in mellow colours, depicting various "+
             "kinds of sailing " +
             "ships and cargo boats.\n");

    add_item(({ "picture", "pictures" }),
	     "The picture is a view of the great " +
             "cavern from the ledge that overlooks it. It is done in mostly " +
             "dark colours, and there are winged shapes shown near the " +
             "cavern ceiling.\n");

    add_item(({ "shapes", "winged shapes", "aglyna" }),
        "The winged shapes are fairly indistinct, but from what you can "+
        "see, they appear to be winged reptiles of some sort, perhaps "+
        "they are the rumoured aglyna.\n");

    set_tell_time(200);
    add_tell("A strong gust of wind blows in through the doorway, " +
             "making you suddenly chilly.\n");
    add_tell("The fire in the fireplace crackles and pops, sending " +
             "some more smoke into the air.\n");

    config_default_trade();
    set_money_give_out(({100,70,10,10}));
    set_money_give_reduce(({0,4,0,6}));

    add_drink("water", "water", "fresh", 90, 0, MY_PRICES[0],
             "glass of water", "glasses of water",
             "It is simply water, sparkling fresh and clear.\n",0);

    add_drink(({"pint","beer"}),({"pint","beer"}),"strong",110,33,MY_PRICES[1],
             "pint of strong beer", "pints of strong beer",
             "The prime beer is of prime quality. It was brewn "
             +"in and imported from an Elven village in the Grey "
             +"Havens.\n", 0);

    add_drink("wine", "wine", "white", 70, 40, MY_PRICES[2],
             "glass of white wine", "glasses of white wine",
             "The sparkling white tinge of this wine comes from "
            +"the ripened grapes that were harvested in the "
            +"vinyards of Argos.\n", 0);

    add_drink("cognac", "cognac", "dark",10, 60, MY_PRICES[3],
             "glass of dark cognac", "glasses of dark cognac",
             "The dark cognac is a bit warm and has a strong "
            +"smell to it.\n",0);

    add_drink("mead", "mead", "foul smelling",10, 70, MY_PRICES[4],
             "mug of thick mead", "mugs of thick mead",
             "Foul smelling vapors rise from this thick, dark brown "
            +"liquid. You feel dizzy even inhaling the fumes.\n",0);
	
	add_drink(({"melomel", "gods melomel", "godsmead", "gods mead"}), 
	         ({"mead", "melomel"}), ({"gods", "godly"}), 100, 250, MY_PRICES[5],
			  "gods' melomel", "gods' melomels",
			  "Ah, what an intoxicating scent arises from the opening "
			  +"to this skin of gods' mead, a drink worthy of the Gods! "
			  +"It smells like the best of every "
			  +"delicious fruit and drink you've ever tasted, and "
			  +"then some. You find yourself wondering if you've "
			  +"got the fortitude to down such a godly drink.\n", 0);

    seteuid(getuid(this_object()));
    clone_object(PORT + "obj/chair")->move(this_object(), 1);
}

int my_order(string str)
{
    if (!present(waitress, TO))
    {
        NF("The waitress dosen't seem to be here, so you " +
           "cannot order anything.\n");
        return 0;
    }

    return(::order(str));
}

void
init()
{
   ::init();

   add_action(my_order, "buy");
   add_action(my_order, "order");
   add_action("do_read","read",0);
}

int
order(string str)
{
   if(!present(waitress, TO))
      {
        NF("The waitress dosen't seem to be here, so you "
                  +"cannot order anything.\n");
        return 0;
       }

    return(::order(str));
}

int
do_read(string str)
{
    if (!str || str == "")
       return 0;

    if (str == "pricelist" || str == "list" || str == "menu")
    {
        write(price_long());
        return 1;
    }

    return 0;
}

string
price_long()
{
    return (
      "The pricelist reads:\n\n" +
      "   Fresh Water         -   " + MY_PRICES[0] + " copper coins\n" +
      "   Dark Beer           -   " + MY_PRICES[1] + " copper coins\n" +
      "   White Wine          -   " + MY_PRICES[2] + " copper coins\n" +
      "   Fine Cognac         -   " + MY_PRICES[3] + " copper coins\n" +
      "   Gorgoroth Mead      -   " + MY_PRICES[4] + " copper coins\n" +
      "   NEW:\n" +
      "   Gods melomel           -   " + MY_PRICES[5] + " copper coins\n");
}

static void
stock()
{
    object obj;

    if (!present("board", this_object()) &&
         (obj = clone_object("/std/board")) != 0)
    {
        obj->set_board_name(PUB_BOARD_DIR);
        obj->set_num_notes(20);
        obj->set_anonymous(1);
        obj->set_silent(0);
        obj->set_show_lvl(0);
        obj->set_remove_lvl(0);
        obj->set_remove_str("The notes are too firmly attatched to remove.");
        obj->move(this_object());
        obj->add_name(({"board","chalkboard","chalk board"}));

        obj->set_short("a chalk board leaning against the south wall, upon " +
                       "which people scrawl notes of interest");

        obj->set_err_log(PUB_BOARD_DIR);
    }

    reset_room();
}

void
reset_room()
{
    if (!waitress)
    {
        waitress = clone_object(PORT + "mon/waitress");
        waitress->equip_me();
        waitress->move_living("M", this_object());
    }
    waitress->lose_hat();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */


