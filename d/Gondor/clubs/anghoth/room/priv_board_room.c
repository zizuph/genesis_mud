/*
 *  priv_board_room.c
 *
 *  Private bulletin board room of the Anghoth Barracks
 *
 *  Alto, 13 June 2002
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../anghoth_defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <std.h>
#include "/d/Gondor/defs.h"

inherit ANGHOTH_ROOM + "room_funcs.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define BENCH_NAME     "stone bench"
#define BENCH_CAPACITY 12

static object      *Janitor = allocate(1);

public string  long_func();
public string  read_plaque();
public int     check_anghoth();
public void    leave_inv(object ob, object to);
public string  look_at(string arg);     /* VBFC for chairs */
public string  long_func();

public string
print_member_list()
{
    string text, sponsor;
    string *kriechek_list, *korrak_list, *dath_list, *durub_list;
    int    i, j, k, l, ashuk;

    text = "These are the Anghoth, Shields of Minas Morgul:\n\n";

    kriechek_list = MANAGER->query_rank_members(1);
    korrak_list   = MANAGER->query_rank_members(2);
    dath_list     = MANAGER->query_rank_members(3);
    durub_list    = MANAGER->query_rank_members(4);

    seteuid(getuid());
    
    i = -1;
    while (++i < sizeof(kriechek_list))
    {
        /* Don't want a jr's name on the club list */
        if ((extract(kriechek_list[i], -2) == "jr") &&
            !(TP->query_wiz_level()))
        {
            continue;
        }

        ashuk = MANAGER->query_ashuk(kriechek_list[i]);
        sponsor = MANAGER->query_anghoth_sponsor(kriechek_list[i]);

        switch (ashuk)
        {
            case 0:
		              text += "- " + CAP(kriechek_list[i]) + ", Kriechek for " 
                    + CAP(sponsor) + "\n";
                break;
            case 1:
                text += "- " + CAP(kriechek_list[i]) + ", Ashuk Kriechek\n";
                break;
            default:
               break;
        }
    }

    j = -1;
    while (++j < sizeof(korrak_list))
    {
        /* Don't want a jr's name on the club list */
        if ((extract(korrak_list[j], -2) == "jr") &&
            !(TP->query_wiz_level()))
        {
            continue;
        }

        ashuk = MANAGER->query_ashuk(korrak_list[j]);
        sponsor = MANAGER->query_anghoth_sponsor(korrak_list[j]);

        switch (ashuk)
        {
            case 0:
		              text += "- " + CAP(korrak_list[j]) + ", Korrak for " 
                    + CAP(sponsor) + "\n";
                break;
            case 1:
                text += "- " + CAP(korrak_list[j]) + ", Ashuk Korrak\n";
                break;
            default:
               break;
        }
    }

    k = -1;
    while (++k < sizeof(dath_list))
    {
        /* Don't want a jr's name on the guildlist */
        if ((extract(dath_list[k], -2) == "jr") &&
            !(TP->query_wiz_level()))
        {
            continue;
        }

        ashuk = MANAGER->query_ashuk(dath_list[k]);
        sponsor = MANAGER->query_anghoth_sponsor(dath_list[k]);

        switch (ashuk)
        {
            case 0:
		              text += "- " + CAP(dath_list[k]) + ", Dath for " 
                    + CAP(sponsor) + "\n";
                break;
            case 1:
                text += "- " + CAP(dath_list[k]) + ", Ashuk Dath\n";
                break;
            default:
               break;
        }
    }

    l = -1;
    while (++l < sizeof(durub_list))
    {
        /* Don't want a jr's name on the guildlist */
        if ((extract(durub_list[l], -2) == "jr") &&
            !(TP->query_wiz_level()))
        {
            continue;
        }

        ashuk = MANAGER->query_ashuk(durub_list[l]);
        sponsor = MANAGER->query_anghoth_sponsor(durub_list[l]);

        switch (ashuk)
        {
            case 0:
		              text += "- " + CAP(durub_list[l]) + ", Durub for " 
                    + CAP(sponsor) + "\n";
                break;
            case 1:
                text += "- " + CAP(durub_list[l]) + ", Ashuk Durub\n";
                break;
            default:
               break;
        }
    }

    return text + "\n";
}


static string 
exa_poster()
{
    write("On the poster you read:\n\n");
    write(TO->print_member_list());
    return "";
}

public void
create_gondor()
{
    object  board, admin_obj, rack;

    set_short(" the private quarters of the Anghoth of Morgul");
    set_long(long_func);

    add_chair(BENCH_NAME,
        "[down] [on] [one] [of] [the] [stone] 'benches' / 'bench'",
        BENCH_CAPACITY, "on");
    add_item(({ "stone bench", "stone benches", "bench", "benches",}), 
        &look_at(BENCH_NAME) );

    anghoth_add_items();

    add_prop(ROOM_I_INSIDE,1);

    add_exit(ANGHOTH_ROOM + "pub_board_room",      "down", check_anghoth, 0);

    add_item("plaque", read_plaque);
    add_cmd_item("plaque", "read", read_plaque);

    add_item(({"room", "building"}), &long_func());
    add_item(({"north wall"}), "On the north wall a window stands open.\n");
    add_item(({"window"}), "The air coming in through the window is stuffy "
        + "and oppressive. The Anghoth, however, do not wilt but rather "
        + "thrive under such conditions.\n");
    add_item(({"south wall"}), "Upon the south wall has been bolted a "
        + "plaque. It looks important.\n");
    add_item(({"east wall"}), "Against the east wall rests a large stone "
        + "table. Now and then the Angoth of Morgul rest upon its benches, "
        + "discussing the strategies by which they ensure the safety of "
        + "their Lords.\n");
    add_item(({"west wall"}), "There is a large poster on the west wall "
        + "which appears to present a list of the Anghoth ranks.\n");
    add_item(({"stairwell", "stairs", "stair", "stone stairs"}), 
        "The stairs curve down into the darkness. They are the only "
        + "obvious way to leave this room.\n");
    add_item(({"table", "stone table", "large table", "large stone table"}),
        "The large table is made entirely of stone. On it are various "
        + "maps and other documents used by the Anghoth in plotting the "
        + "five great works.\n");
    add_item(({"map", "maps"}), "The maps are of various regions in the "
        + "vicinity of Minas Morgul. Routes both open and hidden are marked "
        + "in red.\n");
    add_item(({"documents", "document"}), "The documents on the table "
        + "all seem to be important in the great works of the Anghoth.\n");
    add_item(({"route", "routes"}), "There are various routes delineated "
        + "on the maps in bright red ink.\n");

    add_item(({"anghoth","members","poster"}), exa_poster);
    add_cmd_item(({"anghoth","members","poster"}), "read", exa_poster);

    FIX_EUID;
    board = clone_object("/std/board");
    board->set_board_name(ANGHOTH_BOARD_DIR + "ang_priv_board");
    board->set_num_notes(50);
    board->set_silent(0);
    board->set_show_lvl(0);
    board->set_remove_lvl(WIZ_NORMAL);
    board->set_remove_str("The note is firmly affixed to the board.");
    board->move(TO);

    admin_obj = clone_object(ANGHOTH_OBJ + "anghoth_admin");
    admin_obj->move(TO);

    rack = clone_object(ANGHOTH_OBJ + "equipment_rack");
    rack->move(TO);
    
    // reset_room();
}

public string
read_plaque()
{
    return "\n --------------------------------------------------------- \n"
         + "|o _____________                                       _ o|\n"
         + "| |                                                     | |\n"
         + "|      Hail in the name of the Lidless Eye!             | |\n"
         + "|                                                       | |\n"
         + "|      Remember at all times the five great works of      |\n"
         + "|      the Anghoth, Shields of Morgul! Our honour         |\n"
         + "|      stems only from the satisfaction of our Lords.     |\n"
         + "|      Any who forget this fact will face first the       |\n"
         + "|      wrath of the Anghoth, which is as nothing          |\n"
         + "|      beside the certain displeasure of the Lords        |\n"
         + "|      of Minas Morgul.                                   |\n"
         + "|                                                         |\n"
         + "|      These quarters are our home. Keep them clean!      |\n"
         + "|      To us has been given the honour to <start here>    |\n"
         + "|      Do not leave your trinkets about the floor for     |\n"
         + "|      the slaves to make off with.                       |\n"
         + "|                                                         |\n"
         + "|      Should you make the terribly unwise decision       |\n"
         + "|      to voluntarily leave our ranks, you may <renounce> |\n"
         + "|      your vow of service here. Should you do so, run    |\n"
         + "|      as far and as fast as your cowardly legs will      |\n"
         + "|      carry you, lest the pain of our scorn be dealt     |\n"
         + "|      swiftly upon your worthless person.                |\n"
         + "|                                                         |\n"
         + "| |                                Arganthal, Durub       |\n"
         + "| |                          Captain of the Anghoth       |\n"
         + "| |_                                     _______________| |\n"
         + "|o                                                       o|\n"
         + " --------------------------------------------------------- \n\n";

}

public string
long_func()
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            longtxt = 
        "You are in a dark building in the northern parts of Minas Morgul. "
        + "There is a large bulletin board in the center of the room, and "
        + "a stairwell of stone leading down. A great stone table rests "
        + "along the east wall, with great stone benches encircling it. "
        + "Here the Anghoth, the living Shields of Minas Morgul, meet to "
        + "organize and ensure the defence of their Lords. On the west "
        + "wall you see a large poster, and on the south wall is bolted "
        + "a plaque."; 

    switch (time)
    {
    case "night":
        longtxt += " A window on the north wall opens onto silky darkness.";
        break;
    case "early morning":
        longtxt += " A window on the north wall admits a few weak rays "
            + "of the early morning light.";
        break;
    case "morning":
    case "noon":
    case "afternoon":
        longtxt += " Through a window on the north wall dim light enters.";
        break;
    case "evening":
        longtxt += " Dull evening sunlight can be seen through a window "
            + "on the north wall.";
        break;
    }
    return (longtxt + "\n");
}

public int
check_anghoth()
{
    if (ANGHOTH_MEMBER(TP))
        {
        write("May you serve well today, Anghoth of Minas Morgul!\n");
        return 0;
        }

    if (IS_MORGUL_MAGE(TP))
        {
        write("May you be well-served today, Mage of the Society!\n");
        return 0;
        }

    if (TP->query_wiz_level())
        {
        write("Farewell, Wizard!\n");
        return 0;
        }

    else
        {
        write("Craven! Run snaga. The hounds of Mordor will assail "
            + "you at every turn.\n");
        return 0;
        }
}

int
start(string str)
{
    if (!strlen(str) || lower_case(str) != "here")
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!ANGHOTH_MEMBER(this_player()))
    {
        notify_fail("Only the Anghoth of Minas Morgul may sleep here!\n");
        return 0;
    }
    else if (this_player()->set_default_start_location(ANGHOTH_START))
    {
        write("You will now begin your service to Minas Morgul here "
            + "each day.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n" +
            "Please make a bug report.\n");
        return 0;
    }
}

void
init()
{
    ::init();

    add_action(start, "start");
    init_room_chairs(); /* add chair verbs */
}

/*
public void
reset_room()
{
    clone_npcs(Janitor, ANGHOTH_NPC + "janitor", -1.0);
}
*/

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    leave_inv_room_chairs(ob, to);
}

public string
look_at(string arg)
{
     if (arg == BENCH_NAME)
    {
     return "The stone benches look solid and unyielding, yet will provide "
        + "some measure of comfort to a weary body. They encircle the large "
        + "stone table.\n" 
        + sitting_on_chair(BENCH_NAME, this_player(), 0);
    }
} /* look_at */

