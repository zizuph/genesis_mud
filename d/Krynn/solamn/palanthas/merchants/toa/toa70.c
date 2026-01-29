/* Mortis 9.2014
 * 
 */

#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

int sdopen;
object tguard1, tguard2, tguard3, tguard4;

#define FOUND_TOWER_HOLE     "_i_found_tower_hole"
#define VIEWPLAZA           (ROOM + "plaza")
#define VIEWSHOP            (MERCH + "shop")
#define VIEWBANK            (MERCH + "bank")
#define VIEWINN             (MERCH + "green_twitch")
#define VIEWSMITHY          (MERCH + "smith")
#define VIEWLEATHER         (MERCH + "leather")
#define VIEWKAL             ("/d/Krynn/solamn/palan/shipX/flotsam_pier")
#define VIEWCAL             ("/d/Krynn/solamn/palan/ship4/pier")
#define VIEWLIB             (ROOM + "sr1")
#define VIEWPLAI            (NOBLE + "nplaza")
#define VIEWWEST            (MERCH + "wr5")
#define VIEWSOUTH           (MONKS + "sr5")
#define VIEWEAST            (NOBLE + "er5")
#define THISROOM            (TOA + "toa70")
#define ROOMIN              (TOA + "toa71")

/* prototypes */
void open_secret_door();
void close_secret_door();
void remote_open_secret_door();
string tower_search();
string hole_search();


string
query_to_jail()
{
    return "down";
}

void
reset_palan_room()
{
    if (!objectp(tguard1))
    {
        tguard1 = clone_object(TOA + "living/toa_guard");
        tguard1->move(TO);
    }
    if (!objectp(tguard2))
    {
        tguard2 = clone_object(TOA + "living/toa_guard");
        tguard2->move(TO);
    }
    if (!objectp(tguard3))
    {
        tguard3 = clone_object(TOA + "living/toa_guard");
        tguard3->move(TO);
    }
    if (!objectp(tguard4))
    {
        tguard4 = clone_object(TOA + "living/toa_guard");
        tguard4->move(TO);
    }
}

void
create_palan_room()
{
    SHORT("The crenellated roof of the Tower of Arms in Palanthas");
    LONG("You stand atop the mighty, square Tower of Arms leering five "
    + "stories high across the entire city. The view is expansive. You "
    + "are ringed by stout, crenellated walls, and marble stairs descend "
    + "back down. From the west end of the roof rises an additional one "
    + "story silver-plated tower with no doors.\n");

    ITEM(({"silver-plated tower", "tower"}), "On the west side of "
    + "the roof is a fifteen foot marble tower ringed with silver-plated "
    + "shields. It also is crenellated at the top. There is no door, so the "
    + "entrance inside must be from the level below, probably the "
    + "Constable's quarters.\n");
    ITEM(({"shields", "silver-plated shields"}), "The shields are ornamental, "
    + "approximately a half meter tall, and patterned with weapons. They are "
    + "affixed tightly, side by side, and you cannot tell how they were "
    + "attached. They are well polished and gleam in the light."
    + "@@tower_search@@" + "\n");
    ITEM(({"hole", "small hole"}), "@@hole_search@@");
    ITEM(({"stair", "stairs"}), "A spiral staircase of marble descends "
    + "from here.\n");
    ITEM(({"view"}), "The view from atop the Tower of Arms covers nearly the "
    + "entire city. From here you can <view> the following places of "
    + "interest:\n"
    + "  plaza               - the city's central plaza\n"
    + "  shop                - the shop in the merchants quarter\n"
    + "  bank                - the bank in the merchants quarter\n"
    + "  inn                 - the Green Twitch Inn in the merchants quarter\n"
    + "  smithy              - the weaponsmith in the arms district\n"
    + "  leather             - the leather arms shop in the arms district\n"
    + "  kalaman             - the pier to Kalaman\n"
    + "  calia               - the pier to Calia\n"
    + "  library             - the court outside the Library\n"
    + "  plaisir             - the Court d'Plaisir in the nobles district\n"
    + "  west                - the west gate of Palanthas\n"
    + "  south               - the south gate of Palanthas\n"
    + "  east                - the east gate of Palanthas\n");

    CMD(({"plaza", "the plaza"}), "view", "@@view_plaza");
    CMD(({"shop", "the shop"}), "view", "@@view_shop");
    CMD(({"bank", "the bank"}), "view", "@@view_bank");
    CMD(({"inn", "the inn"}), "view", "@@view_inn");
    CMD(({"smithy", "the smithy"}), "view", "@@view_smithy");
    CMD(({"leather", "the leather"}), "view", "@@view_leather");
    CMD(({"kalaman", "the kalaman"}), "view", "@@view_kalaman");
    CMD(({"calia", "the calia"}), "view", "@@view_calia");
    CMD(({"library", "the library"}), "view", "@@view_library");
    CMD(({"plaisir", "the plaisir"}), "view", "@@view_plaisir");
    CMD(({"west", "the west"}), "view", "@@view_west");
    CMD(({"south", "the south"}), "view", "@@view_south");
    CMD(({"east", "the east"}), "view", "@@view_east");

    EXIT(TOA + "toa62", "down", 0, 0);

    reset_palan_room();

    ROOMIN->teleledningsanka();
}

string
tower_search()
{
    if (TP->query_prop(FOUND_TOWER_HOLE) == 1)
    {
        return " Wait... you notice a small hole between two of the shields. "
        + "It's about the size of a blueberry in diameter.";
    }

    if (TP->query_skill(SS_AWARENESS) > 19 + random(21))
    {
        TP->add_prop(FOUND_TOWER_HOLE, 1);
        return " Wait... you notice a small hole between two of the shields. "
        + "It's about the size of blueberry in diameter.";
    }

    return "";
}

string
hole_search()
{
    if (TP->query_prop(FOUND_TOWER_HOLE) == 1)
    {
        return "It's a small hole about the size of a blueberry in diameter "
        + "between two of the silver-plated shields adorning the wall of the "
        + "roof's tower. It appears to go deep into the wall. You think you "
        + "see the glint of metal within. You could try to insert something "
        + "long and thin into the hole, but it would have to be really thin "
        + "and tight like a rapier.\n\nYou also notice what may be the "
        + "faint outline of a door in the stone around it.\n";
    }

    else
    {
        return "You find no hole.\n";
    }
}

void 
init()
{    
    ::init();
    add_action("action_insert", "insert");
}

int
action_insert(string str)
{
    if (TP->query_prop(FOUND_TOWER_HOLE) == 0)
    {
        return 0;
    }

    if (!str || !parse_command(str, ({}), "'rapier' [in] / [into] 'hole'"))
    {
        TP->catch_msg("Insert what?\n");
        tell_room(E(TP), QCTNAME(TP)+ " tries to insert something "
        + "between a pair of shields but fails completely.\n", ({TO, TP}));
        return 1;
    }
    if (!present("rapier", TP))
    {
        TP->catch_msg("What rapier? You don't have one!\n");
        return 1;
    }
    if (sdopen != 0)
    {
        TP->catch_msg("Nothing happens.\n");
        return 1;
    }
    
    TP->catch_msg("You insert your rapier into the hole until you feel "
    + "resistance and hear a 'Click.'\n");
    tell_room(E(TP), QCTNAME(TP)+ " inserts " + HIS(TP) + " rapier into a "
    + "small hole in between two silver-plated shields on the tower"
    + ".\n", ({TO, TP}));

    set_alarm(1.0, 0.0, &open_secret_door());
    return 1;
}

void
open_secret_door()
{
    sdopen = 1;
    mixed roomin = find_object(ROOMIN);

    roomin->remote_open_secret_door();
    roomin->remote_set_sdopen(1);

    tell_room(E(TP), "A secret door grinds open allowing you to enter the "
    + "tower.\n", 0);
    tell_room(roomin, "A secret door grinds open unexpectedly allowing you to "
    + "exit the tower.\n", 0);
    EXIT(TOA + "toa71", "in", 0, 0);
    set_alarm(30.0, 0.0, &close_secret_door());
}

void
close_secret_door()
{
    mixed roomout = find_object(THISROOM);

    remove_exit("in");
    sdopen = 0;
    tell_room(roomout, "The secret door slowly grinds closed.\n", 0);
}

void
remote_open_secret_door()
{
    sdopen = 1;

    EXIT(TOA + "toa71", "in", 0, 0);
    set_alarm(30.0, 0.0, &close_secret_door());
}

view_plaza()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWPLAZA->long());
    target = find_object(VIEWPLAZA);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_shop()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWSHOP->long());
    target = find_object(VIEWSHOP);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_bank()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWBANK->long());
    target = find_object(VIEWBANK);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_inn()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWINN->long());
    target = find_object(VIEWINN);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_smithy()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWSMITHY->long());
    target = find_object(VIEWSMITHY);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_leather()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWLEATHER->long());
    target = find_object(VIEWLEATHER);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_kalaman()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWKAL->long());
    target = find_object(VIEWKAL);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_calia()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWCAL->long());
    target = find_object(VIEWCAL);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_library()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWLIB->long());
    target = find_object(VIEWLIB);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_plaisir()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWPLAI->long());
    target = find_object(VIEWPLAI);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_west()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWWEST->long());
    target = find_object(VIEWWEST);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_south()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWSOUTH->long());
    target = find_object(VIEWSOUTH);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}

view_east()
{
    /* This function returns an equivalent of 'look' from the target room
     * most importantly without any supporting code from the target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWEAST->long());
    target = find_object(VIEWEAST);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write("From your view atop the Tower of Arms, you can make out "
        + vdesc + " on the ground.\n");
    }

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write("Down below you see " + vdesc + ".\n");
    }

    say(QCTNAME(TP) + " gazes out across the city at something.\n");
 
    return 1;
}
