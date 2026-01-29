/*
 *      /d/Gondor/guilds/bnumen/obj/guild_book.c
 *
 *      Copyright (c) 1995, 1997 by Christian Markus
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

int     read_chapter(string str);
string  read_index();

public void
create_object()
{
    set_short("ancient leatherbound book on a pedestal");
    set_name("book");
    add_name("bnumen book");
    set_long("The large book bound in brown leather looks ancient.\n"
      + read_index());
    add_prop(OBJ_I_NO_GET,"@@try_get");
    add_prop(OBJ_I_LIGHT,1);
}

int
try_get()
{
    write("The book is chained to the pedestal, you cannot get it!\n");
    say(QCTNAME(TP)+" tries to take the book from the pedestal, but it "
      + "is chained to the pedestal.\n", TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(read_chapter, "read");
}

string
read_index()
{
    return 
        "You open the book to the index page, and read:\n\n"
      + "\tThe Book of the Houses of the Black Numenoreans in Minas Tirith:\n"
      + "\tAvailable chapters: Rules of the Black Numenoreans.\n"
      + "\t                    History of the Houses of the Black Numenoreans.\n"
      + "\t                    Lords and Ladies of the Black Numenoreans.\n"
      + "\t                    Joining a House of the Black Numenoreans.\n"
      + "\t                    Leaving a House of the Black Numenoreans.\n"
      + "\n";
}

string
read_rules()
{
    return "\n" + break_string(
       "There are twelve Houses of the Black Numenoreans. Every House can have a Lord "
     + "or a Lady if there is a member of the House that proves worthy. The "
     + "Lord or the Lady can adopt new members and admit them thus into the "
     + "House. He or she can also expel members of his or her House that have "
     + "proven not to be worthy, at his or her sole discretion.\n", 60, "\t")
     + "\n" + break_string(
       "The members of the Houses of the Black Numenoreans have to swear an oath of "
     + "fealty to the Lord or the Lady of the House. If the House receives "
     + "a new Lord or Lady, every bnumen of the House will automatically "
     + "become vassal to the new Lord or Lady. If the bnumen is not able "
     + "or willing to fulfill his or her duties to the House and its Lord or "
     + "Lady, he or she has to renounce the House.\n", 60, "\t")
     + "\n" + break_string(
       "Every bnumen may use the Armoury, the Train Hall, the post office, "
    + "and the Library of the Black Numenoreans.\n", 60, "\t") + "\n";
}

string
read_join()
{
    return "\n" + break_string(
        "If the House has a Lord or a Lady, only the Lord or the Lady can "
      + "receive new members into the House. To this purpose the human wishing "
      + "to join the House has to 'apply' for membership in the House in this "
      + "room in the presence of the Lord or the Lady of the House.\n", 60, "\t")
      + "\n" + break_string(
        "The Lord or the Lady can then offer to 'adopt' the applicant, asking "
      + "him or her to swear the oath of fealty. After the applicant has sworn "
      + "the oath and the Lord or the Lady has replied with the correspoding "
      + "oath as liege lord, the Lord or the Lady receives the applicant into "
      + "his or her House.\n", 60, "\t")
      + "\n" + break_string(
        "If a House has neither Lord nor Lady, every human may 'enter' the House "
      + "by declaring his or her wish to do so, provided that a member of the "
      + "House or a Lord or a Lady of the Black Numenoreans has vouched for him or her. "
      + "Everyone entering a House without a Lord and a Lady must be aware that "
      + "once the House receives a Lord or a Lady, the members are required to "
      + "follow the Lord or the Lady as faithful vasall, as if they had sworn "
      + "the oath of fealty. If they are unwilling or unable to do so, they "
      + "will have to renounce the House.\n", 60, "\t")
      + "\n";
}

string
read_leave()
{
    return "\n" + break_string(
        "Any bnumen who is unwilling or unable to fulfill his duties as liege "
      + "man or liege woman of the Lord or the Lady of the House of the Black Numenoreans "
      + "to which he or she belongs has to declare this by renouncing the House. "
      + "This action will remove him or her not only from his or her own House, "
      + "but also from the the ranks of the Black Numenoreans.\n", 60, "\t")
      + "\n" + break_string(
        "A Lord or a Lady of a House may expel at his or her discretion any "
      + "member of his or her House.\n", 60, "\t")
      + "\n" + break_string(
        "A Lord or a Lady of a House of the Black Numenoreans may release "
      + "a bnumen of his or her House from service. This will not "
      + "end membership of the bnumen in the House, but it will "
      + "enable to bnumen to be adopted into another House of "
      + "the Black Numenoreans.\n", 60, "\t")
      + "\n" + break_string(
        "Only humans can belong to the Houses of the Black Numenoreans. If by magic, "
      + "wizardry, or by corruption through the power of the Evil One a bnumen "
      + "is turned into a being that is not human anymore, that being will be "
      + "removed from the Houses of the Black Numenoreans.\n", 60, "\t")
      + "\n";
}

string
read_history()
{
    return "\n" + break_string(
        "The members of the Houses of the Black Numenoreans value lore and "
      + "knowledge above all else. In highest regard they hold "
      + "knowledge of the history of Arda and Middle Earth, as they "
      + "consider it as one of their most noble duties to collect "
      + "and preserve the tales relating the history of their people.\n",
        60, "\t") + "\n" + break_string(
        "Thus the Houses of the Black Numenoreans are the repository of much "
      + "knowledge that cannot be found anywhere else in the realms "
      + "of the world. The members of the Houses are expected to be "
      + "familiar with the history of Arda, from the Ainulindale over "
      + "the Tales of the Elder Days and the War of the Silmarilli to "
      + "the accounts of Numenor and the Third Age.\n", 60, "\t")
      + "\n" + break_string(
        "The status of a bnumen in the Houses is determined by his "
      + "or her experience and knowledge. A bnumen that wishes to "
      + "increase his or her status in the Houses can try to advance "
      + "in the Chamber of Knowledge west of the Chamber of the "
      + "Houses, but he or she has to pass a test to do so! The higher "
      + "the status, the more difficult will be the questions to be "
      + "answered, and only the truly learned will ever gain sufficient "
      + "status to be eligible to become Lord or Lady of their "
      + "House.\n", 60, "\t") + "\n";
}

string
read_lords()
{
    return "\n" + break_string(
        "Any member of a House of the Black Numenoreans can advance to the "
      + "position of Lord or Lady of his or her house, if the bnumen "
      + "has reached sufficient status among the bnumen and if "
      + "there is no other active bnumen already holding the "
      + "position.\n",
          60, "\t") + "\n" + break_string(
        "If a house has a Lord or a Lady, a human can only join that house "
      + "if he or she is adopted into the House by the Lord or "
      + "the Lady.\n",
        60, "\t") + "\n" + break_string(
        "The Lord or the Lady of a House will lose the rank "
      + "if he or she resigns in this room, or if he or she "
      + "dies, or if he or she is absent from these realms for a "
      + "prolonged period of time and another member of "
      + "the House tries to advance to the position of Lord "
      + "or Lady.\n", 60, "\t") + "\n";
}

int
read_chapter(string str)
{
    if (!str)
        return 0;

    str = LOW(str);

    switch (str)
    {
        case "book":
            write(read_index());
            say(QCTNAME(TP)+" reads the index page of the large brown book.\n",TP);
            break;
        case "rules":
        case "rules of the bnumen":
            write(read_rules());
            say(QCTNAME(TP)+" reads the chapter on the rules of the Black Numenoreans.\n",TP);
            break;
        case "join":
        case "joining":
        case "joining the bnumen":
        case "joining a house of the bnumen":
            write(read_join());
            say(QCTNAME(TP)+" reads the chapter on joining a House of the Black Numenoreans.\n",TP);
            break;
        case "leave":
        case "leaving":
        case "leaving the bnumen":
        case "leaving a house of the bnumen":
            write(read_leave());
            say(QCTNAME(TP)+" reads the chapter on leaving a House of the Black Numenoreans.\n",TP);
            break;
        case "history":
        case "history of the bnumen":
        case "history of the houses":
        case "history of the houses of the bnumen":
            write(read_history());
            say(QCTNAME(TP)+" reads the chapter on the History of the Houses "
              + "of the Black Numenoreans.\n",TP);
            break;
        case "lords":
        case "lords of the bnumen":
        case "ladies of the bnumen":
        case "lords and ladies":
        case "ladies":
        case "lords and ladies of the bnumen":
            write(read_lords());
            say(QCTNAME(TP)+" reads the chapter on Lords and Ladies "
              + "of the Black Numenoreans.\n", TP);
            break;
        default:
            NF("There is no such chapter!\n");
            return 0;
            break;
    }

    return 1;
}
