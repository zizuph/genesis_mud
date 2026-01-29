/*
 *  Herb Shop
 *
 *  Coded by Falke@Angalon
 *  Modified for Minas Morgul in Gondor@Genesis by Olorin, July 1994
 *
 *  Modification Log:
 *   Changed to include herb_base so we can sell unique
 *   objects to the Mages
 *  -- Morbeche Feb 2000
 *
 *   Added herb gloves to list removed herb wraps.
 *  -- Palmer June 24, 2006
 *
 *   Modifications started to list Middle Earth herbs first
 *         In the long run an appointed Herbalist can register
 *         a list of herbs to get a report on (new command).
 *         BSN removed.
 *  -- Toby Oct 4, 2006
 *
 *   The new look is implemented - 6 Oct 2006
 *
 *
 *   2006-11-19, Toby: Implemented support for appointing a 
 *                     Herbalist in the Society. 
 *                     New commands: 'fadd'/'fremove'   (defined in this file)
 *                                   'list focus herbs' (defined in herb_base)
 */

inherit "/d/Gondor/morgul/cellar/herb_base.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_herbs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
// Still necessary for definition of CELLAR_DIR:
#include "/d/Gondor/morgul/cellar/cellar_defs.h"


/*
 * Defines and prototypes for handling the herbalist appoinment.
 */
#define ME_DOMAINS ({ "Gondor", "Mordor", "Shire" })

private string     Herbalist;
private string     *FocusHerbs = ({});
public  string     *query_focus_herbs();

public string      query_herbalist();
public int         appoint_herbalist(mixed mage);
public int         release_herbalist(mixed mage);

private int        do_add_fherb(string str);
private int        do_remove_fherb(string str);

string read_plaque();

void
create_morgul_cellar_room()
{
    FIX_EUID

    /* this line needed to created default trade configuration */
    config_default_trade();

    set_money_greed_buy(60);
    set_money_greed_sell(150);
    set_money_give_out(   ({ 10000,   700,  50,   10 }));
    set_money_give_reduce(({     0,     2,   4,    6 }));

    set_room_type("new herb shop");
    set_extra_long("A small lamp gives some light here, illuminating " +
      "a narrow wooden counter. On the newly re-built counter stands a sign. " +
      "Hooks in the ceiling hold bunches of drying herbs.");

    /* set the room to be used as storage room for this shop */
    set_store_room(CELLAR_DIR + "herb_storage");
    call_other(store_room, "load_me");

    set_level(1);

    add_floor();
    add_walls();
    add_stones();
    add_item(({"roof","ceiling"}),
	"From the high vaulted ceiling several hooks and a small " +
	"lamp are hanging.\n");
    add_item(({"small shop", "herb shop","shop"}), 
	"This dark and dusty room is a herb shop. Here you can " +
	"buy and sell herbs. But you will probably be robbed in " +
	"the process.\n");
    add_item(({"counter", "wooden counter"}),
	"A simple wooden counter made from rough boards. On the " +
	"counter, you can see a sign. At the front of the counter there is a small plaque.\n");
    add_item(({"lamp", "light"}), 
	"A single lamp hanging from the ceiling tries to give light " +
        "to the room. It is a rather feeble attempt, of course.\n");
    add_item(({"windows"}), "There are no windows here.\n");
    add_item(({"hooks", "hook"}), 
	"Wrought iron. From some of them are hanging dried herbs, " +
        "but they are out of your reach.\n");
    add_item(({"herbs", "herb", "bunches of herbs", "bunches"}), "Herbs, "+
      "tied in bunches, hanging from the ceiling to dry.\n");
    add_item(({"sign", "poster"}), read_sign());
    add_cmd_item(({"sign", "poster"}), "read", read_sign());
    add_item(({"plaque", "small plaque", "small copper plaque", "copper plaque"}), "@@read_plaque");
    add_cmd_item(({"plaque", "small plaque", "small copper plaque", "copper plaque"}), "read", "@@read_plaque");

    add_exit(CELLAR_DIR + "pass_1e2", "southeast", 0);

    add_prop(ROOM_I_LIGHT, 1);   /* A lamp is giving light in here */
    add_prop(ROOM_I_HIDE, 25);   /* But it's not much light, so it's easy to hide */

    setuid();
    seteuid(getuid());

    restore_object( MORGUL_APPOINT_SAVE );
}

void
init()
{
    ::init();

    add_action("do_add_fherb",    "fadd");
    add_action("do_remove_fherb", "fremove");

    init_herb_shop();
}

/* Set in the herb_base.c
string
read_sign()
{
    return "A quite ordinary looking sign that has nothing written upon its surface.\n";
}
*/

string
read_plaque()
{
    if(!strlen(this_player()->query_morgul_title()))
       return "The small copper plaque looks well polished though nothing is written upon its surface.\n";

    if(strlen(Herbalist))
    {
      // Add here support to find the Mage name if there is one and print that instead.

        return "The small copper plaque looks well polished. Nothing is " +
        "scribbled upon its surface. The air just above the surface shimmer " +
        "in a faint green glow which forms the words:\n" +
        "\tThe current herbalist of the Society is: " + Herbalist + ".\n";
    }
    else
        return "The small copper plaque looks well polished. Nothing is " +
        "scribbled upon its surface. The air just above the surface " +
        "shimmer in a faint green glow which forms the words:\n" +
        "\tThe brave, or foolish, may seek audience with the Nine \n" +
        "\tto ask to fill the place as the Society's Herbalist! \n";
}


int
query_shop_no_business(mixed pl)
{
    if (stringp(pl))
	pl = find_living(pl);

    if (SECURITY->query_wiz_rank(pl->query_real_name()) >= WIZ_ARCH)
        return 0;

    if (query_verb() == "buy")
    {
        if (IS_MORGUL_MAGE(pl) || IS_GONDOR_WIZARD(pl)) return 0;
     
//	if (query_feeling(pl) >= 0)
	    return 1;
    }
    else
    {
	if (query_feeling(pl) > 0)
	    return 1;
    }

    return 0;
}

int
query_shop_hook_restricted_herb(object pl, string str)
{
    if (SECURITY->query_wiz_rank(pl->query_real_name()) >= WIZ_ARCH)
        return 0;

    if (IS_MORGUL_MAGE(pl))
	return 0;
    if (member_array(lower_case(str), MORGUL_HERBS) >= 0)
	return 1;
    else
	return 0;
}

void
shop_hook_restricted_herb(object pl, string str)
{
    notify_fail("The Nazgul forbid the selling of that herb to non-"
      + "Society members!\n");
}

/*
 *  BELOW IS SUPPORT FOR HERBALIST APPOINMENT AND HIS/HER COMMANDS
 */

/*
 * Function name: query_herbalist
 * Description  : Return the current Herbalist.
 * Returns      : The name
 */
public string query_herbalist()
{
    if(!strlen(Herbalist))
        return "None";

    return Herbalist;
}

public int appoint_herbalist(mixed mage)
{
   if (objectp( mage ))
   {
      mage = mage->query_name();
   }
   else if (stringp( mage ))
   {
      mage = capitalize(mage);
   }

   Herbalist = mage;

   setuid();
   seteuid( getuid() );
   save_object( MORGUL_APPOINT_SAVE );

   return 1;
}

public int release_herbalist(mixed mage)
{
   if (objectp( mage ))
   {
      mage = mage->query_name();
   }
   else if (stringp( mage ))
   {
      mage = capitalize(mage);
   }

   if(Herbalist != mage)
   {
       notify_fail("But " +mage+ " is not appointed as the Herbalist of Morgul!\n");
       return 0;
   }

   Herbalist = "";

   setuid();
   seteuid( getuid() );
   save_object( MORGUL_APPOINT_SAVE );

   return 1;
}


int do_add_fherb(string str)
{
    if(this_player()->query_name() != Herbalist && 
       !this_player()->query_nazgul() &&
       (member_array( SECURITY->query_wiz_dom( this_player()->query_real_name()), ME_DOMAINS ) == -1) )
        return 0;

    notify_fail("Add what, a herb?\n");

    if(!str)
       return 0;

    str = lower_case(str);

    if(member_array( str, FocusHerbs ) > -1)
    {
        notify_fail(capitalize(str) + " is already listed as a herb of focus!\n");
        return 0;
    }

    FocusHerbs += ({ str });
    FocusHerbs = sort_array( FocusHerbs );

    setuid();
    seteuid( getuid() );
    save_object( MORGUL_APPOINT_SAVE );

    write(capitalize(str) + " is now added as one of the herbs of focus.\n");
    return 1;
}


int do_remove_fherb(string str)
{
    if(this_player()->query_name() != Herbalist && 
       !this_player()->query_nazgul() &&
       (member_array( SECURITY->query_wiz_dom( this_player()->query_real_name()), ME_DOMAINS ) == -1) )
        return 0;

    notify_fail("Remove what, a herb?\n");

    if(!str)
       return 0;

    str = lower_case(str);

    if(member_array( str, FocusHerbs ) == -1)
    {
        notify_fail(capitalize(str) + " is not listed as a herb of focus!\n");
        return 0;
    }

    FocusHerbs -= ({ str });
    FocusHerbs = sort_array( FocusHerbs );

    setuid();
    seteuid( getuid() );
    save_object( MORGUL_APPOINT_SAVE );

    write(capitalize(str) + " is now removed as one of the herbs of focus.\n");
    return 1;
}

/*
 * Function name: query_focus_herbs
 * Description  : Return the list of the herbs of focus.
 * Returns      : Array of strings with the herbs.
 */
public string *query_focus_herbs()
{
    return ({ })+ FocusHerbs;
}

