// Book_wom      (/d/Avenir/common/bazaar/NPC/book_wom.c)
// creator(s):    Glinda
// purpose:       A possible holder of the book the librarian wants
// note:          Made from the man1 which crowds the bazaar.
/*
 * Revisions:
 * 	Lucius, Aug 2017: Cleanups and fixes for "return book" quest.
 */
inherit "/d/Avenir/common/bazaar/NPCS/wom1";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"

#define BOOK "/d/Avenir/common/bazaar/Obj/books/book1"
#define LOC  "/d/Avenir/common/bazaar/extr/"
#define VOID "/d/Avenir/common/void"

public int has_been_asked;
public object book;

public void
create_monster()
{
    ::create_monster();
    add_ask(({"book","books"}), "@@react_book@@", 1);
}

public void
place_me(void)
{
    string loc;

    switch(random(8))
    {
    case 0:
	loc=(LOC + "str22");
	break;
    case 1:
	loc=(LOC + "str23");
	break;
    case 2:
	loc=(LOC + "str24");
	break;
    case 3:
	loc=(LOC + "str7");
	break;
    case 4:
	loc=(LOC + "str10");
	break;
    case 5:
	loc=(LOC + "str12");
	break;
    case 6:
	loc=(LOC + "str15");
	break;
    case 7:
	loc=(LOC + "str19");
	break;
    }
    TO->move(loc);
}

public string
react_book(void)
{
    if (IS_INFIDEL(TP))
    {
	command("emote looks frightened.");
	command("shout Guards! I've found an infidel!");
	return "";
    }

    if (!TP->query_prop("_has_talked_to_librarian"))
    {
	command("shrug");
	return "";
    }

    if (!TP->test_bit("Avenir",0,5) && !has_been_asked)
    {
	command("say Oh....yeah the book...");
	command("say Hang on, let me go get it.");
	command("say Catch me later and I'll have it for you.");
	command("emote runs off to get the book.");
	TO->move(VOID);
	set_alarm(100.0, 0.0, place_me);
	has_been_asked=1;
	return "";
    }

    if (has_been_asked)
    {
	book=clone_object(BOOK);
	book->move(TO);
	command("say Sure, here it is....");
	command("give book to " + TP->query_real_name());
	command("emote vanishes in the crowd.");
	TO->remove_object();
    }
    command("shrug");
    return "";
}
