/*
 *  The Rangers post-office, a modification of the Hobbiton post-office
 *  Updated to use /d/Gondor/common/lib/post.c
 *  - Olorin, January 1995
 *
 *  Modification log:
 *  Alto to fit CH theme, added ferrets, removed council mail aliases.
 *  Gwyneth, 3 May 2004, neatened
 *  Tigerlily, Nov. 3, 2004--Allow rangers teamed for task 8
 *      to enter taskroom
 */
inherit "/d/Gondor/common/lib/post";

#include "../rangers.h"

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define PIGEON_VALUE 24
#define FERRET_VALUE 36
#define I_PENNED_RANGER_COUNCIL   ("_i_penned_ranger_council")


string             exa_note();
static int         Fee = FERRET_VALUE;
object             actor;

public int
check_app()
{
    object tp = this_player();
    object *teammate = tp->query_team_others();
    
    //ok for full ranger if teamed with apprentice on
    //task 8
    if (sizeof(teammate) == 1)
    {
        if ((teammate[0]->query_prop(RANGER_I_TASK) == WARRIORS_TASK) &&
        RANGERS_FULL_MEMBER(tp))
            return 0;
    }

    /* Else only let apprentices and wizards by. We don't
     * want full Rangers walking them through it. */
    if (APPRENTICE_MEMBER(tp) || tp->query_wiz_level())
        return 0;
    //else
    write("You are not allowed to go there.\n");
    return 1;

}

void
create_room()
{
   set_short("the communications office of Ranger Central Headquarters");
   set_long("The smell of captive animals is very powerful here! Looking "
       + "around, you see a small hutch containing carrier pigeons, and "
       + "several wire cages containing ferrets. In addition to courier "
       + "animal services, this room also functions as the Post Office for "
       + "the rangers stationed here at Central Headquarters. On one wall "
       + "hangs a note, and a poster on the other "
       + "contains instructions. A doorway leads east to the corridor "
       + "and another leads west to the outside.\n");

   add_item(({"note",}), exa_note());
   add_cmd_item(({"note",}), "read", exa_note());

   add_item(({"pigeons", "pigeon", "carrier-pigeons"}), "The pigeons are "
       + "useful for quickly delivering messages anywhere in the world. "
       + "Keep in mind that they can only give messages to recipients "
       + "standing under open sky.\n");
   add_item(({"ferrets", "ferret"}), "Cheerful ferrets roll and play in "
       + "the wire cages. These animals may be used to deliver messages "
       + "anywhere within the bounds of the great Oceans.\n");
   add_item(({"animal", "animals"}), "There are two kinds of courier animal "
       + "housed here: pigeons and ferrets.\n");
   add_item(({"hutch", "small hutch"}), "A small wooden hutch in which "
       + "carrier-pigeons are kept when they are not out delivering "
       + "messages.\n");
   add_item(({"cages", "cage", "wire cages", "wire cage"}), "The small "
       + "wire cages contain a number of bustling ferrets.\n");

   set_poster_name("big poster");

   add_exit(RANGERS_HQ_DIR + "dcorridor2", "east", 0);
   add_exit(RANGERS_DIR + "tasks/task_room", "west", &check_app());

   create_post();
}

void
mail_message(string new)
{
   write("\nThere is" + new + " mail for you in the post office in "
       + "the Rangers Guild.\n(Somewhere in central Gondor)\n\n");
}

string
exa_poster()
{
    return "Use the brand new service of this post-office: if you need to "
        + "get an urgent message through to a friend elsewhere in the world, "
        + "hire a carrier pigeon to bring it to him. This service may be "
        + "bought for the very low price of " + PIGEON_VALUE + " copper "
        + "coins. For messages within the lands of Middle Earth, a ferret "
        + "may be rented to deliver messages to places pigeons cannot "
        + "travel.\n";
}

string
exa_note()
{
    return "Here you may read and write your mail as in any other post "
        + "office. Check the mailreader for instructions.\n\n"
        + HANGING_INDENT("To contact the Ranger Council:\n"
        + "If any counsellors desire to be contacted directly, they will "
        + "have posted their names and titles on the board to the east. "
        + "If their identities are not known to you, you may <pen> a message "
        + "here that will be made available to the counsellors.", 4, 0);
}

public int
pen_council(string str)
{
    string message;

    if (TP->query_prop(I_PENNED_RANGER_COUNCIL))
    {
        NF("You have already penned the Ranger Council today. "
            + "As they are quite busy with their duties, it would be "
            + "unkind to overtax their time and patience.\n");
        return 0;
    }

    if (!strlen(str))
    {
        NF("Please <pen> a brief (single return) message to the members "
            + "of the Ranger Council.\n");
        return 0;
    }

    message = str;
    write("Your message will be made available to the Council of "
        + "Rangers. Thank you.\n");
    MANAGER->rlog("messages", "The following message was left by " 
        + capitalize(TP->query_real_name()) + ":\n\n"
        + message + "\n"
        + "     ---------------------------------------------     \n");
    TP->add_prop(I_PENNED_RANGER_COUNCIL, 1);
    return 1;
}


public int
rent_ferret(string str)
{
    int     n;
    mixed   res;
    string  give, change;
    object  ferret;

    actor = TP;

    if (!strlen(str) || (str != "ferret" && str != "a ferret"))
    {
       NF0("What exactly do you wish to rent?\n");
       return 0;
    }

    if (pointerp(res = pay(Fee, TP)) && (sizeof(res) > 1))
    {
        give = text(res);
        change = text(res[sizeof(MONEY_TYPES)..]);
        write("You pay " + text(res) +
            (strlen(change) ? " and get " + change + " back as change" : "") +
            ".\nOne of the ferrets bounds from a cage and into your arms.\n");
        tell_room(environment(actor), QCTNAME(actor) + " rents a ferret.\n",
            actor);

        ferret = clone_object(RANGERS_OBJ + "ferret.c");
        ferret->move(TP);

        return 1;
    }

    write("It seems you do not have enough money to afford a ferret.\n");
    return 1;
}

void
add_aliases(object rdr)
{

    string *wizards = ({ });
    wizards = GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME);
    if (sizeof(wizards))
        rdr->set_alias("guildmaster", wizards);

}

public void
init() 
{
    ::init();

    add_action(rent_ferret,  "rent");
    add_action(pen_council, "pen");
}
