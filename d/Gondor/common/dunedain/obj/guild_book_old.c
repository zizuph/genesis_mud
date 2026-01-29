/*
 *      /d/Gondor/common/dunedain/obj/guild_book.c
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
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

int     read_chapter(string str);
string  read_index();

public void
create_object()
{
    set_short("ancient leatherbound book on a pedestal");
    set_name("book");
    add_name("dunedain book");
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
      + "\tThe Book of the Houses of the Dunedain in Minas Tirith:\n"
      + "\tAvailable chapters: Rules of the Dunedain.\n"
      + "\t                    History of the Houses of the Dunedain.\n"
      + "\t                    Lords and Ladies of the Dunedain.\n"
      + "\t                    Joining a House of the Dunedain.\n"
      + "\t                    Leaving a House of the Dunedain.\n"
      + "\n";
}

string
read_rules()
{
    return "\n" + break_string(
       "There are twelve Houses of the Dunedain. Every House can have a Lord "
     + "or a Lady if there is a member of the House that proves worthy. The "
     + "Lord or the Lady can adopt new members and admit them thus into the "
     + "House. He or she can also expel members of his or her House that have "
     + "proven not to be worthy, at his or her sole discretion.\n", 60, "\t")
     + "\n" + break_string(
       "The members of the Houses of the Dunedain have to swear an oath of "
     + "fealty to the Lord or the Lady of the House. If the House receives "
     + "a new Lord or Lady, every dunadan of the House will automatically "
     + "become vassal to the new Lord or Lady. If the dunadan is not able "
     + "or willing to fulfill his or her duties to the House and its Lord or "
     + "Lady, he or she has to renounce the House.\n", 60, "\t")
     + "\n" + break_string(
       "Every dunadan may use the Armoury, the Train Hall, the post office, "
    + "and the Library of the Dunedain.\n", 60, "\t") + "\n";
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
      + "House or a Lord or a Lady of the Dunedain has vouched for him or her. "
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
        "Any dunadan who is unwilling or unable to fulfill his duties as liege "
      + "man or liege woman of the Lord or the Lady of the House of the Dunedain "
      + "to which he or she belongs has to declare this by renouncing the House. "
      + "This action will remove him or her not only from his or her own House, "
      + "but also from the the ranks of the Dunedain.\n", 60, "\t")
      + "\n" + break_string(
        "A Lord or a Lady of a House may expel at his or her discretion any "
      + "member of his or her House.\n", 60, "\t")
      + "\n" + break_string(
        "A Lord or a Lady of a House of the Dunedain may release "
      + "a dunadan of his or her House from service. This will not "
      + "end membership of the dunadan in the House, but it will "
      + "enable to dunadan to be adopted into another House of "
      + "the Dunedain.\n", 60, "\t")
      + "\n" + break_string(
        "Only humans can belong to the Houses of the Dunedain. If by magic, "
      + "wizardry, or by corruption through the power of the Evil One a dunadan "
      + "is turned into a being that is not human anymore, that being will be "
      + "removed from the Houses of the Dunedain.\n", 60, "\t")
      + "\n";
}

string
read_history()
{
    return "\n" + break_string(
        "The members of the Houses of the Dunedain value lore and "
      + "knowledge above all else. In highest regard they hold "
      + "knowledge of the history of Arda and Middle Earth, as they "
      + "consider it as one of their most noble duties to collect "
      + "and preserve the tales relating the history of their people.\n",
        60, "\t") + "\n" + break_string(
        "Thus the Houses of the Dunedain are the repository of much "
      + "knowledge that cannot be found anywhere else in the realms "
      + "of the world. The members of the Houses are expected to be "
      + "familiar with the history of Arda, from the Ainulindale over "
      + "the Tales of the Elder Days and the War of the Silmarilli to "
      + "the accounts of Numenor and the Third Age.\n", 60, "\t")
      + "\n" + break_string(
        "The status of a dunadan in the Houses is determined by his "
      + "or her experience and knowledge. A dunadan that wishes to "
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
        "Any member of a House of the Dunedain can advance to the "
      + "position of Lord or Lady of his or her house, if the dunadan "
      + "has reached sufficient status among the dunedain and if "
      + "there is no other active dunadan already holding the "
      + "position.\n",
          60, "\t") + "\n" + break_string(
        "If a house has a Lord or a Lady, a human can only join that house "
      + "if he or she is adopted into the House by the Lord or "
      + "the Lady.\n",
        60, "\t") + "\n" + break_string(
        "The Lord or the Lady of a House will lose the rank "
      + "if he or she resigns in this room, or if he or she "
    + "is absent from these realms for a "
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
        case "rules of the dunedain":
            write(read_rules());
            say(QCTNAME(TP)+" reads the chapter on the rules of the Dunedain.\n",TP);
            break;
        case "join":
        case "joining":
        case "joining the dunedain":
        case "joining a house of the dunedain":
            write(read_join());
            say(QCTNAME(TP)+" reads the chapter on joining a House of the Dunedain.\n",TP);
            break;
        case "leave":
        case "leaving":
        case "leaving the dunedain":
        case "leaving a house of the dunedain":
            write(read_leave());
            say(QCTNAME(TP)+" reads the chapter on leaving a House of the Dunedain.\n",TP);
            break;
        case "history":
        case "history of the dunedain":
        case "history of the houses":
        case "history of the houses of the dunedain":
            write(read_history());
            say(QCTNAME(TP)+" reads the chapter on the History of the Houses "
              + "of the Dunedain.\n",TP);
            break;
        case "lords":
        case "lords of the dunedain":
        case "ladies of the dunedain":
        case "lords and ladies":
        case "ladies":
        case "lords and ladies of the dunedain":
            write(read_lords());
            say(QCTNAME(TP)+" reads the chapter on Lords and Ladies "
              + "of the Dunedain.\n", TP);
            break;
        default:
            NF("There is no such chapter!\n");
            return 0;
            break;
    }

    return 1;
}
