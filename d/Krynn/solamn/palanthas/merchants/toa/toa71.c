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

#define FOUND_TOWER_HOLE        "_i_found_tower_hole"
#define VIEWPLAZA               (ROOM + "plaza")
#define VIEWSHOP                (MERCH + "shop")
#define VIEWBANK                (MERCH + "bank")
#define VIEWINN                 (MERCH + "green_twitch")
#define VIEWSMITHY              (MERCH + "smith")
#define VIEWLEATHER              (MERCH + "leather")
#define VIEWKAL                 ("/d/Krynn/solamn/palan/shipX/flotsam_pier")
#define VIEWCAL                 ("/d/Krynn/solamn/palan/ship4/pier")
#define VIEWLIB                 (ROOM + "sr1")
#define VIEWPLAI                (NOBLE + "nplaza")
#define VIEWWEST                (MERCH + "wr5")
#define VIEWSOUTH               (MONKS + "sr5")
#define VIEWEAST                (NOBLE + "er5")
#define THISROOM                (TOA + "toa70")
#define ROOMIN                  (TOA + "toa71")

/* Prototypes */
void open_secret_door();
void close_secret_door();
void remote_open_secret_door();

string
query_to_jail()
{
    return "down";
}

void
reset_palan_room()
{
}

void
create_palan_room()
{
    SHORT("The crenellated roof of the Constable's private tower atop "
    + "the Tower of Arms in Palanthas");
    LONG("The view from the top of this crenellated, silver-plated tower "
    + "rising one story from the top of the mighty, square Tower of Arms is "
    + "expansive. You are ringed by stout, crenellated walls and covered by "
    + "a siver-plated marble roof. Marble stairs descend back down, and torch "
    + "sconces line the crenellated stone.\n");

    ITEM(({"silver-plated tower", "tower"}), "On the west side of "
    + "the roof is a fifteen foot marble tower ringed with silver-plated "
    + "shields. It also is crenellated at the top. You are in it looking "
    + "over the expansive view of the city of Palanthas.\n");
    ITEM(({"shields", "silver-plated shields"}), "The shields are ornamental, "
    + "approximately a half meter tall, and patterned with weapons. They are "
    + "affixed tightly, side by side, and you cannot tell how they were "
    + "attached. They are well polished and gleam in the light.\n");
//    + "@@tower_search@@" + "\n");
    ITEM(({"sconce", "sconces"}), "Burnished iron sconces are set into the "
    + "high points of the crenellated walls. One of them has no mortar "
    + "around it. It looks like you could twist it. You also notice what may "
    + "be the faint outline of a door in the stone below it.\n");
    ITEM(({"stair", "stairs"}), "A spiral staircase of marble descends "
    + "from here.\n");
    ITEM(({"view"}), "The view from the Constable's tower atop the Tower of "
    + "Arms covers nearly the entire city. From here you can <view> the "
    + "following places of interest:\n"
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

    EXIT(TOA + "toa67", "down", 0, 0);

    reset_palan_room();

    THISROOM->teleledningsanka();
}

void 
init()
{    
    ::init();
    add_action("action_twist", "twist");
}

int
action_twist(string str)
{
    if (!str || !parse_command(str, ({}), "'sconce' / 'sconces'"))
    {
        TP->catch_msg("Twist what?\n");
        tell_room(E(TP), QCTNAME(TP)+ " twists one of the torch sconces.\n", ({TO, TP}));
        return 1;
    }
    if (sdopen != 0)
    {
        TP->catch_msg("Nothing happens.\n");
        return 1;
    }
    TP->catch_msg("You give the sconce a half twist and hear a 'Click.'\n");
    tell_room(E(TP), QCTNAME(TP)+ " twists one of the torch sconces"
    + ".\n", ({TO, TP}));

    set_alarm(1.0, 0.0, &open_secret_door());
    return 1;
}

void
open_secret_door()
{
    sdopen = 1;
    mixed roomin = find_object(THISROOM);

    roomin->remote_open_secret_door();
    roomin->remote_set_sdopen(1);

    tell_room(E(TP), "A secret door grinds open allowing you to exit the "
    + "tower.\n", 0);
    tell_room(roomin, "A secret door grinds open unexpectedly allowing you to "
    + "enter the silver-plated tower.\n", 0);
    EXIT(TOA + "toa70", "out", 0, 0);
    set_alarm(30.0, 0.0, &close_secret_door());
}

void
close_secret_door()
{
    mixed roomin = find_object(ROOMIN);

    remove_exit("out");
    sdopen = 0;
    tell_room(roomin, "The secret door slowly grinds closed.\n", 0);
}

void
remote_open_secret_door()
{
    sdopen = 1;

    EXIT(TOA + "toa70", "out", 0, 0);
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
