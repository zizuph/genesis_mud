/*
 * Mortis 03.2006 
 *
 * The master suite of merchant house Trusq.
 *
 * How much general xp can be rewarded for disarming/picking?
 *
 * EDITED:  The difficulty of Find and Remove Traps checks was based
 * on the assumption that krynn thieves had a skill level of 50. It is
 * actually 40 which meant a master thief got slashed by the trap more
 * often than disarming it. Difficulty has been lowered in accordance
 * with my original intention.
 *
 * Mortis 01.2008
 *
 * Increased the rewards in the chest and pouch to make it worth the risk
 * of dealing with the traps. Updated syntax (e.g. if curlies), also.
 *
 * Mortis 09.2014
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <poison_types.h>

#define VIEWSTREET               (SHIP + "alley201")
#define VIEWLEDGE                (SHIP + "trusq_ledge")
#define DUMBWAITER_LOC           (SHIP + "trusq_dumb")
#define HIGH_GUARDROOM           (SHIP + "trusq_priv_guardroom")
#define VIEWENT                  (SHIP + "s03")
#define VIEWREAR                 (SHIP + "alley202")
#define VIEWESTATE               (SHIP + "neighbor_estate")
#define FOUND_TRUSQ_CHEST        "_i_found_trusq_chest"
#define FOUND_TRUSQ_CHEST_TRAP   "_i_found_trusq_chest_trap"
#define FOUND_FIREPLACE_HOLE     "_i_found_trusq_fireplace_hole"
#define CHIMNEY_INVADER          "_i_invaded_trusq_through_the_chimney"

inherit SHIP_ROOMBASE;

int pouchhere = 0, chesthere = 0, chesttrap = 0, trappoisons = 2, alrm = 0,
    winopen, winlock;
object trusq, bodyguard, indumb, *inv, *ppl, ledge = find_object(VIEWLEDGE);

/* Prototypes */
int enter_dumb(string str);
int crawl_vent(string str);
int pull_rope(string str);
int disarm_chest(string str);
int spring_trap(object victim);
int chest_open();
string is_dumb_here();
string desk_search();
string bed_search();
string chest_search();
string brass_panel();
string exa_fire();
string exa_vent(string str);
string window_status();

void
reset_palan_room()
{
    if (!trusq)
    {
        trusq = clone_object(SHIP + "living/trusq_lord");
        trusq->move(TO);
    }

    if (!bodyguard)
    {
        bodyguard = clone_object(SHIP + "living/trusq_guard3");
        bodyguard->move(TO);
    }

    if (random(5) == 1)
        pouchhere = 0;

    if (random(6) == 1)
    {
        chesthere = 0;
        chesttrap = 0;
        trappoisons = 2;
    }
}

void
create_palan_room()
{
    object mdoor;

    SHORT("An enormous bedroom suite in a merchant estate");
    LONG("Dark, oak paneling lines the walls of this enormous suite from "
    + "the ground up to three feet with polished, translucent white marble "
    + "taking over from there. The entire fourth floor is taken up by "
    + "this one suite which contains a king sized bed with thick, ten foot "
    + "tall oak bedposts, a twelve foot tall wardrobe, a large couch, a "
    + "loveseat, several plush leather chairs, a great oaken desk, and rows "
    + "of bookcases against the wall. There is a dumbwaiter in the "
    + "southeast of the room, a fireplace in the south, and windows looking "
    + "out in all directions.\n");

    ITEM(({"suite", "bedroom", "office"}), "You are in the suite. Have a "
    + "<look> around? Or a <view> out the window?\n");
    ITEM(({"wall", "walls", "panelling"}), "The bottom three feet of the "
    + "walls in this room have been paneled in wide strips of dark stained "
    + "oak. From there up is polished, translucent white marble. The "
    + "paneling and marble are separated by a wide strip of oak trim. "
    + "Several large paintings line the walls.\n");
    ITEM("marble", "The marble in the room is translucent white and "
    + "polished to a gleaming shine.\n");
    ITEM("floor", "The floor is made of large sheets of translucent white "
    + "marble and polished to a shine.\n");
    ITEM("ceiling", "The ceiling has been finished with translucent white "
    + "marble.\n");
    ITEM("trim", "A wide strim of oak trim separates the paneling from the "
    + "marble. Keepsakes, vases, and flowers are arranged atop it.\n");
    ITEM(({"keepsake", "keepsakes", "vase", "vases", "flower", "flowers"}),
      "Keepsake cameos, music boxes, vases, and flowers line are arranged "
    + "about the room atop the oak trim separating the paneling from the "
    + "marble.\n");
    ITEM(({"bed"}), "A gigantic, king sized bed sits against the north "
    + "wall. Thick, ten foot tall oak bedposts carved to appear to "
    + "twist rise from its corners topped with studded wooden balls. "
    + "@@bed_search@@" + "\n");
    ITEM(({"couch", "loveseat", "seat", "seats", "chair", "chairs"}),
      "A soft blue couch and loveseat are arranged before the fireplace "
    + "along the south wall alongside plush leather chairs.\n");
    ITEM(({"book", "books", "case", "cases", "bookcase", "bookcases"}),
      "Rows of bookcases line the walls in the northwest corner of the "
    + "suite around a great oaken desk.\n");
    ITEM(({"painting", "paintings"}), "Several large, skillfully done "
    + "paintings line the walls. One is a portrait of a middle-aged "
    + "man in noble clothing with a young, stern faced lady on his arm. "
    + "Another is of several sailing ships in the Bay of Belfalas all "
    + "flying a yellow and blue banner.\n");
    ITEM("desk", "@@desk_search");
    ITEM("chest", "@@chest_search");
    ITEM("brass panel", "@@brass_panel");
    ITEM("trap", "@@exa_trap");
    ITEM("wardrobe", "The wardrobe sits against the east wall and rises to a "
    + "gigantic height of twelve feet. Its wood is dark stained and "
    + "carved with incredibly detailed ornate patterns.\n");
    ITEM(({"window", "windows"}), "The north window looks out over Bulwark "
    + "Round where the main estate entrance is <view entrance>. The east "
    + "window looks out over a ledge <view ledge> to a side street below "
    + "<view street>. The south window looks out over a side street in the "
    + "rear of the estate <view rear>. The west window looks across at "
    + "the merchant house estate next door <view estate>.\n");
    ITEM("east window", "An iron-rimmed window looking east onto the side "
    + "street below. " + "@@window_status@@" + "\n");
    ITEM(({"north window", "west window", "south window"}), "A simple "
    + "window through which you may view what is going on outside.\n");
    ITEM(({"dumbwaiter", "panel"}), "Above the desk in the southwest "
    + "corner covered by a sliding steel panel with a tiny keyhole is a "
    + "small dumbwaiter used to send meals up to the higher floors by means "
    + "of a rope and pulley system. " + "@@is_dumb_here@@" + "\n");
    ITEM(({"rope", "pulley"}), "A rope within the dumbwaiter shaft hangs "
    + "out of an opening beside the dumbwaiter allowing the dumbwaiter to "
    + "be hoisted to the upper floors via a pulley attached high above. "
    + "You can pull the left rope or the right to work the dumbwaiter.\n");
    ITEM("opening", "In a small opening in the wall beside the dumbwaiter "
    + "hangs a rope used to hoist the dumbwaiter up to the upper floors. "
    + "You can pull the left rope or the right to work the dumbwaiter.\n");
    ITEM(({"fire", "fireplace"}), "A brick fireplace is set into the south "
    + "wall of the room providing warmth on cold nights. A couch, loveseat, "
    + "and leather chairs are arranged around it." + "@@exa_fire@@" + "\n");
    ITEM(({"ash", "ashes"}), "Ashes from spent fires lay scattered in the "
    + "fireplace.\n");
    ITEM("vent", "@@exa_vent");

    add_smell("vampire", "The air is clean, but you smell expensive perfumes "
    + "here. Your fangs throb with anticipation as you sense hot "
    + "blood pumping through a great many hearts closeby.");
    add_smell("morgul", "The air is clean, but you smell expensive perfumes "
    + "here.");
    add_smell("human", "The air is clean, but you smell expensive perfumes "
    + "here.");
    add_smell("elf", "The air is clean, but you smell human perfumes "
    + "here.");
    add_smell("goblin", "The air is clean, but you smell perfumie things "
    + "here.");
    add_smell("dwarf", "The air is clean, but you human perfumes "
    + "here.");
    add_smell("hobbit", "The air is clean, but you smell expensive perfumes "
    + "here.");
    add_smell("gnome", "The air is clean, but you detect expensive perfumes "
    + "here.");
    add_smell("minotaur", "The air is clean, but you smell expensive perfumes "
    + "here. The smell of man is thick here.");
    add_smell("halfhuman", "The air is clean, but you smell expensive "
    + "perfumes here.");
    add_smell("halfelf", "The air is clean, but you smell expensive perfumes "
    + "here.");
    add_smell("orc", "The smell of human perfumes in the sterile air "
    + "cannot mask the scent of so much manflesh in this place.");
    add_smell("hobgoblin", "The clean air would indicate humans keep this "
    + "place well tended. You smell human perfumes here.");
    add_smell("kender", "The air is clean, but you smell pretty perfumes "
    + "here.");
    add_smell("drow", "The sterile air here would indicate the place is "
    + "clean by human standards. You detect the smells of human perfumes "
    + "here.");
    add_smell("noldor", "The air is clean, but you smell human perfumes "
    + "here.");
    add_smell("uruk", "The smell of human perfumes in the sterile air "
    + "cannot mask the scent of so much manflesh in this place.");
    add_smell("presence", "You don't pick up much in your current state.");
    add_smell("unknown", "The air is clean and smells of expensive perfumes, "
    + "but what the heck race are you?!?  Why not <mail krynn> for fun?");

    CMD(({"dumbwaiter"}), "view", "@@view_dumb");
    CMD(({"street"}), "view", "@@view_street");
    CMD(({"ledge"}), "view", "@@view_ledge");
    CMD(({"window", "east window"}), "open", "@@open_ewindow");
    CMD(({"window", "east window"}), "close", "@@close_ewindow");
    CMD(({"window", "east window"}), "unlock", "@@unlock_ewindow");
    CMD(({"window", "east window"}), "lock", "@@lock_ewindow");
    CMD("chest", "open", "@@chest_open");

    mdoor = clone_object(SHIP + "doors/trusq_master_door2");
    mdoor->move(TO);

    reset_palan_room();
    DUMBWAITER_LOC->teleledningsanka();
    HIGH_GUARDROOM->teleledningsanka();
}

string
window_status()
{
    winopen = ledge->query_open();
    winlock = ledge->query_lock();

    if (winopen == 1 && winlock == 1)
    { return "The window is closed and locked from the inside."; }

    if (winopen == 1)
    { return "The window is closed but unlocked."; }

    return "The window is open.";
}

int
open_ewindow()
{
    winopen = ledge->query_open();
    winlock = ledge->query_lock();

    NF("You must unlock the window first.\n");
    if (winlock == 1)
    { return 0; }

    write("You open the east window.\n");
    say(QCTNAME(TP) + " opens the east window.\n");
    ledge->win_open();
    return 1;
}

int
close_ewindow()
{
    winopen = ledge->query_open();
    winlock = ledge->query_lock();

    NF("The window is already closed.\n");
    if (ledge->query_open() == 1)
    { return 0; }

    write("You close the east window.\n");
    say(QCTNAME(TP) + " closes the east window.\n");
    ledge->win_close();
    return 1;
}

int
unlock_ewindow()
{
    winopen = ledge->query_open();
    winlock = ledge->query_lock();

    NF("The window is already unlocked.\n");
    if (winlock == 0)
    { return 0; }

    write("You unlock the east window.\n");
    say(QCTNAME(TP) + " unlocks the east window.\n");
    ledge->win_unlock();
    return 1;
}

int
lock_ewindow()
{
    winopen = ledge->query_open();
    winlock = ledge->query_lock();

    NF("The window is already locked.\n");
    if (winlock == 1)
    { return 0; }

    NF("You must close the window first.\n");
    if (winopen == 0)
    { return 0; }

    write("You lock the east window.\n");
    say(QCTNAME(TP) + " locks the east window.\n");
    ledge->win_lock();
    return 1;
}

string
exa_fire()
{
    if (TP->query_prop(FOUND_FIREPLACE_HOLE) == 1)
    {
        return "  Behind the ash in the back of the fireplace is a vent "
        + "where smoke from fireplaces below rises through here and up "
        + "the chimney.";
    }

    if (TP->query_skill(SS_AWARENESS) > 20 + random(20))
    {
        TP->add_prop(FOUND_FIREPLACE_HOLE, 1);
        return "  You discover a large vent behind the ash in the back of "
        + "the fireplace where smoke from fireplaces below rises through "
        + "here and up the chimney.";
    }
    return "";
}

string
exa_vent(string str)
{
    if (TP->query_prop(FOUND_FIREPLACE_HOLE) != 1)
    { return "You find no vent.\n"; }

    return "If you were small enough, or able to contort your body into "
    + "acrobatic positions, you might be able to crawl into the vent in the "
    + "back of the fireplace. It's pretty filthy though.\n";
}

string
desk_search()
{
    string pouchcol = one_of_list(({"white", "grey", "black"}));
    object pouchh;

    if (pouchhere == 0 && TP->query_skill(SS_AWARENESS) > 30 + random(21))
    {
        pouchh = clone_object(MERCH + "obj/lgeneral");
        pouchh->set_general_data("plain" + "&&" + pouchcol + "&&"
                                + "suede" + "&&" + "belt-pouch");

        MONEY_MAKE_PC(7)->move(pouchh);
        MONEY_MAKE_GC(72 + random(5))->move(pouchh);
        pouchh->move(TP);
        pouchhere = 1;

        return "The great, oaken desk is ornately carved with intricate detail "
        + "and has several drawers beneath. In one of them, you find a "
        + pouchh->short() + " and pick it up!\n";
    }

        return "The great, oaken desk is ornately carved with intricate detail "
        + "and has several drawers beneath.\n";
}

string
bed_search()
{
    if (TP->query_prop(FOUND_TRUSQ_CHEST) == 1)
    { return "There is a chest bolted securely beneath the bed."; }

    if (chesthere == 0 && TP->query_skill(SS_AWARENESS) > 40 + random(21))
    {
        TP->add_prop(FOUND_TRUSQ_CHEST, 1);
        return "There is a chest bolted securely beneath the bed.";
    }

    return "It is covered with a rich, pale blue comforter.";
}

string
chest_search()
{
    string chestdesc = "The chest is thick mahogany bound with thick, square steel "
        + "bands, and is bolted securely beneath the bed. ";

    if (TP->query_prop(FOUND_TRUSQ_CHEST) != 1)
    { return "You find no chest.\n"; }

    if (chesthere == 1)
    { return chestdesc + "It has been unlocked and is empty.\n"; }

    if (chesttrap == 0 && TP->query_prop(FOUND_TRUSQ_CHEST_TRAP) == 1)
    {
        return chestdesc + "It is latched shut and locked. You notice a "
        + "brass panel above it on the bottom of the bed with numerous "
        + "holes.\nThe chest is trapped!\n";
    }
    
    if (chesttrap == 0 && TP->query_skill(SS_FR_TRAP) >= 25 + random(21))
    {
        TP->add_prop(FOUND_TRUSQ_CHEST_TRAP, 1);
        return chestdesc + "It is latched shut and locked. You notice a "
        + "steel panel above it on the bottom of the bed with numerous "
        + "holes.\nThe chest is trapped!\n";
    }

    return chestdesc + "It is latched shut and locked.\n";
}

int
disarm_chest(string str)
{
    int dmg = 250 + random(400);

    NF("What?\n");
    if (!str)
    { return 0; }

    if (TP->query_prop(FOUND_TRUSQ_CHEST_TRAP) != 1)
    { return 0; }

    NF("Disarm what?\n");
    if (!parse_command(str, ({}), "[the] 'trap' / 'chest'"))
    { return 0; }
    
//    NF("The trap on the chest has already been disarmed.\n");
    if (chesttrap == 1)
    {
        write("The trap on the chest has already been disarmed.\n");
        return 1;
    }

    if (chesttrap == 0 && TP->query_skill(SS_FR_TRAP) > 21 + random(21))
    {
        chesttrap = 1;
        write("Jamming one of the holes in the steel panel above the chest, "
        + "you are confident you've disabled the trap... for a while.\n");
        return 1;
    }

    spring_trap(TP);
    return 1;
}

int
spring_trap(object victim)
{
    int dmg = -200 - 125;

    write("You hear a \"Klitch\"... \"Chi-KOONG!\"  ...as an array of spear "
    + "tips plunges down from the steel panel above the chest impaling "
    + "you.\n");
    say("You hear a sick clunking noise from under the bed as " + QTNAME(TP)
    + " fiddles with something.\n");

    if (trappoisons > 0)
    {
        trappoisons--;

        object poison = clone_object("/std/poison_effect");
        poison->set_time(630);
        poison->set_interval(23);
        poison->set_strength(45);
        poison->set_damage(({POISON_HP, 105, POISON_STAT, SS_DEX}));
        poison->set_poison_type("isil juice");
        poison->move(victim);
        poison->start_poison();
    }

    victim->heal_hp(dmg);

    if (victim->query_hp() <= 0)
    { victim->do_die(E(victim)); }
}

int
pick_chest(string str)
{
    if (!str)
    { return 0; }

    if (TP->query_prop(FOUND_TRUSQ_CHEST) != 1)
    { return 0; }

    if (!parse_command(str, ({}), "[the] 'lock' / 'chest' [on] [the] [chest]"))
    { return 0; }

    NF("The chest has already been unlocked and looted.\n");
    if (chesthere == 1)
    { return 0; }

    NF("But the chest is trapped!  Just trying to pick it looks like it will "
    + "spring the trap and impale your hands to the floor, and you don't "
    + "want that, do you?\n");
    if (chesttrap == 0 && TP->query_prop(FOUND_TRUSQ_CHEST_TRAP) == 1)
    { return 0; }

    if (chesttrap == 0)
    {
        spring_trap(TP);
        return 1;
    }

    if (TP->query_skill(SS_OPEN_LOCK) > 50 + random(26))
    {
        clone_object("/d/Genesis/gems/obj/diamond")->move(TP);
        if (random(2) == 1)
        { clone_object("/d/Genesis/gems/obj/diamond")->move(TP); }
        if (random(3) == 1)
        { clone_object("/d/Genesis/gems/obj/diamond")->move(TP); }

        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        clone_object("/d/Genesis/gems/obj/emerald")->move(TP);
        if (random(2) == 1)
        { clone_object("/d/Genesis/gems/obj/emerald")->move(TP); }
        if (random(3) == 1)
        { clone_object("/d/Genesis/gems/obj/emerald")->move(TP); }

        MONEY_MAKE_PC(5 + random(11))->move(TP);
        MONEY_MAKE_GC(50 + random(61))->move(TP);
        MONEY_MAKE_SC(200 + random(151))->move(TP);
        chesthere = 1;
        write("You unlock the chest with a satisfying \"chi-koonk\" noise "
        + "from within as you open the lid quietly before looting a pile "
        + "of gold, silver, and jewels inside the chest.\n");
        return 1;
    }

    write("You fumble with the lock on the chest but instead of a satisfying "
    + "\"chi-koonk\" noise from within, you hear the ominous clank of a gear "
    + "above the steel trap panel.\nNothing happens.\n");
    chesttrap = 0;
    return 1;
}

int
chest_open()
{
    if (chesthere != 0 && TP->query_prop(FOUND_TRUSQ_CHEST) == 1)
    {
        write("The chest is empty inside.\n");
        return 1;
    }

    if (chesthere == 0 && TP->query_prop(FOUND_TRUSQ_CHEST) == 1)
    {
        write("The chest is locked. You can't figure this thing out.\n");
        return 1;
    }
    return 0;
}

string
brass_panel()
{
    if (TP->query_prop(FOUND_TRUSQ_CHEST_TRAP) == 1)
    {
        return "There is a brass panel above the chest under the bed that "
        + "is riddled with circular holes. You believe it is a trap "
        + "triggered by meddling with the chest.\n";
    }

    return "You find no brass panel\n";
}

string
exa_trap()
{
    if (TP->query_prop(FOUND_TRUSQ_CHEST_TRAP) == 1)
    {
        return "There is a brass panel above the chest under the bed that "
        + "is riddled with circular holes. You believe it is a trap "
        + "triggered by meddling with the chest.\n";
    }

    return "You find no trap\n";
}

string
is_dumb_here()
{
    if (indumb->what_floor() == 4)
    {
        return "The dumbwaiter is presently here. You may look inside it "
        + "with <view dumbwaiter>.";
    }
    else
    {
        return "The dumbwaiter is at present not on this floor.";
    }
}

int
view_dumb()
{
    /* This function returns an equivalent of 'look' from trusq_dumb
     * most importantly without any supporting code from the
     * target room.
     */

    object *obs;
    string desc;

    NF("The dumbwaiter is not here so you cannot look inside it.\n");
    if (indumb->what_floor() != 4)
    { return 0; }

    write(DUMBWAITER_LOC->long());
    indumb = find_object(DUMBWAITER_LOC);
    inv = all_inventory(indumb);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write(one_of_list(({"You see "}))
                        + desc + " laying there.\n");
    }

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write(one_of_list(({"You can make out "}))
                        + desc + " in the dumbwaiter.\n");
    }
 
    return 1;
}

void 
init()
{
    ::init();
    ADD("enter_dumb", "enter");
    ADD("crawl_vent", "crawl");
    ADD("pull_rope", "pull");
    ADD("disarm_chest", "disarm");
    ADD("pick_chest", "pick");
}

int
enter_dumb(string str)
{
    string dumbrace = QRACE(TP);
    
    indumb = find_object(DUMBWAITER_LOC);
    inv = all_inventory(indumb);
    ppl = FILTER_LIVE(inv);

    NF("What?\n");
    if (!str)
    { return 0; }

    if (parse_command(str, ({}), "[the] [east] 'window' / 'ledge'"))
    {

        NF("You must first open the window before you attempt to enter it.\n");
        if (ledge->query_open() == 1)
            return 0;

        write("You slip out the east window.\n");
        say(QCTNAME(TP) + " slips out the east window.\n");
        TP->move_living("entering the east window", SHIP + "trusq_ledge",
            0, 0);
        return 1;
    }

    NF("Enter what?  The future?  Have patience.\n");
    if (!parse_command(str, ({}), "[the] [dumb] 'waiter' / 'dumbwaiter'"))
    { return 0; }

    NF("The dumbwaiter is not on this floor.\n");
    if (indumb->what_floor() != 4)
    { return 0; }

    NF("There is already someone inside the dumbwaiter!  This must be a "
    + "popular hangout.\n");
    if (sizeof(ppl) > 0)
    { return 0; }

    if (TP->query_skill(SS_ACROBAT) >= 15 + random(16) ||
        dumbrace == "hobbit" || dumbrace == "kender" || dumbrace == "gnome")
    {
        write("You unlatch the cupboard doors, open them, and contort "
        + "yourself inside the dumbwaiter.\n");
        TP->move_living("unlatches the cupboard doors and squeezes inside "
        + "the dumbwaiter in the southwest corner", SHIP + "trusq_dumb", 1, 0);
        return 1;
    }

    write("You can't quite contort yourself to fit inside the dumbwaiter, "
    + "strain as you might. You'd need an acrobat or a midget to fit inside "
    + "that thing!\n");
    say(QCTNAME(TP) + " strains to fit inside the dumbwaiter in the "
    + "southwest corner but can't quite make it.\n");
    return 1;
}

int
pull_rope(string str)
{
    indumb = find_object(DUMBWAITER_LOC);
    inv = all_inventory(indumb);
    ppl = FILTER_LIVE(inv);

    NF("What?\n");
    if (!str)
    { return 0; }

    NF("Pull " + str + "?  Right here?  Are you mad?!?\n");
    if (!parse_command(str, ({}), "[the] [left] [right] 'rope'"))
    { return 0; }

    if (parse_command(str, ({}), "[the] [right] 'rope'"))
    {
        NF("The dumbwaiter is too heavy!  Pulling the right rope has no "
        + "effect.\n");
        if (sizeof(ppl) > 1)
        { return 0; }

        NF("The dumbwaiter has reached the top and can go no further. "
        + "Pulling the right rope has no effect.\n");
        if (indumb->what_floor() == 4)
        { return 0; }
        
        write("You pull the right rope, and the dumbwaiter rises to the "
        + "next floor.\n");
        say(QCTNAME(TP) + " pulls the right rope in the southwest corner "
        + "and hoists the dumbwaiter to the next floor.\n");
        tell_room(E(TP), "The dumbwaiter arrives at this floor.\n");
        indumb->add_floor();

        return 1;
    }

    if (parse_command(str, ({}), "[the] [left] 'rope'"))
    {
        NF("The dumbwaiter has reached the bottom and can go no further. "
        + "Pulling the left rope has no effect.\n");
        if (indumb->what_floor() == 1)
        { return 0; }
        
        write("You pull the left rope, and the dumbwaiter lowers to the "
        + "next floor.\n");
        say(QCTNAME(TP) + " pulls the left rope in the southwest corner "
        + "and lowers the dumbwaiter to the next floor.\n");
        indumb->subtract_floor();

        return 1;
    }

    write("Which rope did you want to pull?  The left or right one?\n");
    return 1;
}

int
crawl_vent(string str)
{
    string ventrace = QRACE(TP);

    NF("What?\n");
    if (TP->query_prop(FOUND_FIREPLACE_HOLE) != 1)
    { return 0; }

    NF("Crawl into what?\n");
    if (!str)
    { return 0; }

    if (!parse_command(str, ({}), "[in] [into] [the] 'vent' [in] [the] [back] [of] [the] [fireplace]"))
    { return 0; }

    if (TP->query_skill(SS_ACROBAT) >= 15 + random(6) ||
        ventrace == "hobbit" || ventrace == "kender" || ventrace == "gnome")
    {
        write("You crawl through the ash to the vent in the back of the "
        + "fireplace and squeeze your way inside.\n");
        TP->move_living("crawls through the ash in the fireplace and "
        + "disappears into a vent", SHIP + "trusq_chimney_roof", 1, 0);
        return 1;
    }

    write("You can't quite contort yourself to fit inside the vent, strain "
    + "as you might. You'd need an acrobat or a midget to fit inside that "
    + "thing!\n");
    say(QCTNAME(TP) + " crawls through the ash in the fireplace and tries "
    + "to squeeze " + HIS(TP) + " way in deeper.\n");
    return 1;
}

void
enter_inv2()
{
    if (trusq && bodyguard)
        trusq->command("say to guard Do make efforts to be more careful with "
        + "the vases.");
    alrm = 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (alrm != 0)
    { return 0; }

    if (ob->query_prop(CHIMNEY_INVADER) == 1)
    {
        alrm = 1;

        if (trusq)
        {
            trusq->command("say The gall of some criminals these days. "
            + "Breaking and entering is low class and unprofitable.");
        }
        
        if (bodyguard)
        {
            int dmg = -175 - random(50);
            string invader = ob->query_real_name();

            bodyguard->command("say Invaders!  Protect!");
            bodyguard->command("kill " + invader);
            ob->catch_msg("The guard smashes a vase over your skull!\n");
            say("The guard smashes a vase over " + QTNAME(ob) + "'s "
            + "skull!\n", ob);
            ob->heal_hp(dmg);

            if (ob->query_hp() <= 0)
                ob->do_die(E(ob));
        }
        
        set_alarm(1.5, 0.0, "enter_inv2");
    }
}

int
view_street()
{
    /* This function returns an equivalent of 'look' from alley201
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWSTREET->long());
    target = find_object(VIEWSTREET);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write(one_of_list(({"From above you can make out ",
                            "You believe you spot ",
                            "Your eyes come across "}))
                            + desc + " on the ground.\n");
    }

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write(one_of_list(({"Down below you see ",
                            "You notice below ",
                            "Down below you spy "}))
                            + desc + " in the side street.\n");
    }
 
    return 1;
}

int
view_ledge()
{
    /* This function returns an equivalent of 'look' from trusq_ledge
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWLEDGE->long());
    target = find_object(VIEWLEDGE);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write(one_of_list(({"From the window you can make out ",
                            "You believe you spot ",
                            "Your eyes come across "}))
                            + desc + " on the ledge.\n");
    }

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write(one_of_list(({"Out the window you see ",
                            "You notice below ",
                            "Out the window you spy "}))
                            + desc + " perched on the ledge.\n");
    }
 
    return 1;
}

int
view_ent()
{
    /* This function returns an equivalent of 'look' from s03
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWENT->long());
    target = find_object(VIEWENT);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write(one_of_list(({"From above you can make out ",
                            "You believe you spot ",
                            "Your eyes come across "}))
                            + desc + " on the ground.\n");
    }

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write(one_of_list(({"Down below you see ",
                            "You notice below ",
                            "Down below you spy "}))
                            + desc + " in front of the estate.\n");
    }
 
    return 1;
}

int
view_rear()
{
    /* This function returns an equivalent of 'look' from alley202
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWREAR->long());
    target = find_object(VIEWREAR);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write(one_of_list(({"From above you can make out ",
                            "You believe you spot ",
                            "Your eyes come across "}))
                            + desc + " on the ground.\n");
    }

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write(one_of_list(({"Down below you see ",
                            "You notice below ",
                            "Down below you spy "}))
                            + desc + " in the side street.\n");
    }
 
    return 1;
}

int
view_estate()
{
    /* This function returns an equivalent of 'look' from estate west
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWESTATE->long());
    target = find_object(VIEWESTATE);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write(one_of_list(({"From above you can make out ",
                            "You believe you spot ",
                            "Your eyes come across "}))
                            + desc + " on the ground.\n");
    }

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write(one_of_list(({"Down below you see ",
                            "You notice below ",
                            "Down below you spy "}))
                            + desc + " in the side street.\n");
    }
 
    return 1;
}

void
rescue_lord_room(object ob)
{
    if (!bodyguard)
    { return; }

    bodyguard->rescue_lord(ob);
    return;
}