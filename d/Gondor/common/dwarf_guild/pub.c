/*
 * /Gondor/common/dwarf_guild/pub.c
 *
 * Copyright (C) Stas van der Schaaf - January 9 1994
 *               Mercade @ Genesis
 * 
 * This is the pub in the dwarven race guild. It sells booze, but what else
 * do you expect from a pub?
 *
 * Note that the alcohol values of the beverages sold here must correspond
 * with the values in the individual drink-files. Also, the price per pair
 * of dice must be the same as twice the value per die as it is defined in
 * the die-file.
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

/*
 * This define is an array of arrays defining the drinks that are sold in
 * the pub. The format of the sub-array is:
 * - short description for on the meny
 * - parse string with optional descriptions
 * - filename of the drink (without dir)
 * - alco level of the drink in ml
 */
#define SERVED_DRINKS                                              \
 ({ ({ "orange juice",                                             \
	"[orange] 'juice' / 'juices'",                             \
	"juice",                                                   \
	0 }),                                                      \
    ({ "sweet shandy",                                             \
	"[sweet] 'shandy' / 'shandies'",                           \
	"shandy",                                                  \
	3 }),                                                      \
    ({ "tasteful light beer",                                      \
	"[tasteful] [light] 'beer' / 'beers'",                     \
	"beer",                                                    \
	6 }),                                                      \
    ({ "dry white wine",                                           \
	"[dry] [white] 'wine' / 'wines'",                          \
	"wine",                                                    \
	13 }),                                                     \
    ({ "hot lemon brandy",                                         \
	"[hot] [lemon] 'brandy' / 'brandies'",                     \
	"brandy",                                                  \
	20 }),                                                     \
    ({ "mellow green liquor",                                      \
	"[mellow] [green] 'liquor' / 'liquors'",                   \
	"liquor",                                                  \
	30 }),                                                     \
    ({ "firebreathing spirit",                                     \
	"[fire] [breathing] [firebreathing] 'spirit' / 'spirits'", \
	"spirit",                                                  \
	40 }),                                                     \
    ({ "mind blasting brew",                                       \
	"[mind] [blasting] [mindblasting] 'brew' / 'brews'",       \
	"brew",                                                    \
	50 }) })

#define KEEPER             (DWARVEN_RACE_GUILD_NPCS + "bartender")
#define CHESSPLAYER        (DWARVEN_RACE_GUILD_NPCS + "player")
#define INDEX_DRINKS_SHORT 0 /* indices to the SERVED_DRINKS mixed */
#define INDEX_DRINKS_ALCO  3

/*
 * Prototypes
 */
string pricelist();
void   reset_room();

/*
 * Global variables
 */
static mixed  served_drinks = SERVED_DRINKS;
static object keeper;
static object chessplayer;

void
create_room()
{
    set_short("the pub of the " + DWARVEN_RACE_GUILD_NAME +
	", \"The Staggering Dwarf\"");
    set_long(BSN("You are in the pub of the " + DWARVEN_RACE_GUILD_NAME +
	", \"The Staggering Dwarf\". Here you can buy different types " +
	"of drinks to forget your sorrow or to heal yourself from the " +
	"terrors of war. The pub is decorated with oak panels, trophies " +
	"and other nice items. There are several tables here with chairs " +
	"beside them. A few lamps are hanging from the ceiling, creating " +
	"a pleasant atmosphere. Behind the counter you see the pricelist. " +
	"The shop is to the west and the main guildcave is to the " +
	"northwest."));

#include "cavedesc.h"

    remove_item("wall");
    add_item( ({ "wall", "walls" }),
	BSN("The walls of this cave are decorated with oak panels, " +
	"trophies donated by customers and other nice items."));
    add_item( ({ "trophy", "trophies" }),
	BSN("Several preserved deer-heads and other trophies are on the " +
	"walls. They are donated by several visitors."));
    add_item( ({"panels", "wooden panels", "oak panels" }),
	BSN("Many oak panels decorate the walls of this pub. In them you " +
	"can see carvings and inscriptions."));
    add_item( ({ "carving", "carvings" }),
	BSN("Several of the oak panels carry carvings of settings " +
	"depicting life, hunt and combat."));
    add_item( ({ "inscription", "inscriptions" }),
	BSN("Many inscriptions can be read on the panels on the walls in " +
	"this pub. On them you can read sayings like: \"There is no place " +
	"like home. this is home!\" and \"A dwarf without his axe is no " +
	"dwarf.\"."));
    add_item( ({ "chair", "chairs" }),
	BSN("It is a bar, obviously there are many chairs here. They are " +
	"simple, yet comfortable chairs, made of wood."));
    add_item( ({ "table", "tables" }),
	"@@table_description@@");
    add_item( ({ "counter" }),
	"@@counter_description@@");
    add_item( ({ "list", "menu", "pricelist", "prices", "poster" }),
	BSN("On the pricelist you can read all about the drinks sold in " + 
	"this bar."));

    /* The pricelist is computed only once when the room is initialized.
     * There is no need to recompute the list each time someone types the
     * command 'read'.
     */
    add_cmd_item( ({ "list", "menu", "pricelist", "prices", "poster" }),
	({ "read" }), pricelist());

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "guild", "northwest");
    add_exit(DWARF_DIR + "shop",  "west");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

string
table_description()
{
    string str = "There are several wooden tables in this establishment. " +
	"Chairs are grouped around the table. A chessboard is laid in one " +
	"of the tables.";

    if (objectp(chessplayer) && (ENV(chessplayer) == TO))
    {
	str += " An old dwarf is sitting at the table with the chessboard.";
    }

    return BSN(str);
}

string
counter_description()
{
    string str = "Above the wooden counter is a lamp and a shelf. On the " +
	"shelf you see several brands of liquor. ";

    if ((!objectp(keeper)) || (ENV(keeper) != TO))
    {
	str += "Currently the counter is unattended. This means that you " +
	    "cannot order. However, this does not mean that you can help " +
	    "yourself to booze.";
    }
    else
    {
	str += "Behind the counter you see " + keeper->query_art_name(TP) +
	    ", the barkeeper of this pub.";
    }

    return BSN(str);
}

void
reset_room()
{
    FIX_EUID;

    if (!objectp(keeper))
    {
	keeper = clone_object(KEEPER);
	keeper->arm_barkeeper();
	keeper->set_drinks(served_drinks);
	keeper->move(TO, 1);
	tell_room(TO, QCNAME(keeper) +
	    " enters the pub and steps behind the counter.\n");
    }
    else if (ENV(keeper) != TO)
    {
	keeper->move_living("X", TO);
    }

    if (!objectp(chessplayer))
    {
	chessplayer = clone_object(CHESSPLAYER);
	chessplayer->arm_chessplayer();
	chessplayer->move(TO, 1);
	tell_room(TO, QCNAME(chessplayer) +
	    " enters the pub and seats himself at one of the tables.\n");
    }
    else if (ENV(chessplayer) != TO)
    {
	chessplayer->move_living("X", TO);
    }
}

string
pricelist()
{
    int index = -1;
    int size = sizeof(served_drinks);
    string str =
"Welcome to \"The Staggering Dwarf\"!\n\n" +
"               PRICELIST\n" +
"=======================================\n\n";

    while(++index < size)
    {
	str += sprintf("   %-30s   %3d\n",
	    served_drinks[index][INDEX_DRINKS_SHORT],
	    F_VALUE_ALCO(served_drinks[index][INDEX_DRINKS_ALCO]));
    }

    return str +
// "\n   ivory dice (per pair)            114\n" +
"\nIf you wish so, we serve more than one drink in one single order too.\n";
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!living(ob) ||
	!objectp(to))
    {
	return;
    }

    keeper->player_leaves(ob);
    chessplayer->player_leaves(ob);
}