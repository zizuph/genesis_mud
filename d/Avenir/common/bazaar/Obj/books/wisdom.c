// wisdom         (/d/Avenir/common/bazaar/Obj/books/wisdom.c)
// creator(s):   Lilith, March 1997
// revisions:                                                            
// purpose:      The Book of Small Wisdoms
// note:                                                                   
// bug(s):                                                                 
// to-do:                                                                  
#pragma strict_types

inherit "/std/object";            

#include <macros.h> 
#include <stdproperties.h>

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/relation.h"

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/WISDOM/"

/* NUM_PAGES needs to updated everytime a new page is added */
#define NUM_PAGES 57

private static int page = random(NUM_PAGES);
private static string *earmarks =
	explode("000000000000000000000000000000000000", "");
private static string *alnum =
	explode("abcdefghijklmnopqrstuvwxyz0123456789", "");

public int
query_page(void)	{ return page; }

public int
set_page(int a)		{ page = a; }

public void
create_object(void)
{                                                                           
    setuid();
    seteuid(getuid());

    set_name("_wisdom_book");
    add_name(({"enchiridion", "enchridon", "book", "wisdoms"}));
    add_adj(({"small", "tiny", "palm-sized", "soft-bound"}));
    set_pname("enchiridia");
    set_short("palm-sized enchiridion");
    set_pshort("palm-sized enchiridia");
    set_long("A small, palm-sized book with a soft, flexible "+
      "cover and rounded edges. On the spine and front cover "+
      "have been printed the words: 'The Book of Small Wisdoms'"+
      ".\nThere is a small caption beneath the title, most "+
      "likely instructions for using this book.\n");

    add_item(({"spine", "cover"}), "It has the words: 'The Book "+
      "of Small Wisdoms' written on it.\n");
    add_item(({"caption", "help", "instructions"}),
      "\n   You can <open> or <read> this book.\n"+
      "   You can <quote book> to quote from a page.\n"+
      "   You can <thumb book> to thumb forward a few pages.\n"+
      "   You can <mark this page as tab [a-z/0-9]> and then\n"+
      "   You can <tab [a-z/0-9]> to read that page.\n"+
      "   In case of conflict you may prefix commands with \"wis\"\n"+
      "        <wisread>, <wisquote>, etc.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_M_NO_BUY,   1);
    add_prop(OBJ_M_NO_SELL,  1);
    add_prop(OBJ_I_NO_STEAL, 1);
}

public int
do_read(string str) 
{
    if (str == "enchiridion" || str == "palm-sized book" ||
	str == "book" || str == "wisdoms") 
    {
	string text, what;

	switch(query_verb())
	{
	case "thumb":
	case "wisthumb":
	    page += 5; /* Turn a few pages. */
	    break;
	default:
	    page += 1; /* Turn one page. */
	    break;
	}

	if (page > NUM_PAGES)
	    page = 0;

	if (TP->query_wiz_level())
	    what = "page "+ page;
	else 
	    what = "a random page";

	text = read_file(BOOKPATH + "p" + page);
	write("The "+ short() +" flutters open to "+ what +":\n\n");
	TP->more(text);        
	return 1;
    }

    return NF(CAP(query_verb()) +" what?\n");
}

public int
do_quote(string str)
{
    if (str == "book" || str == "from book" ||
	str == "enchiridion" || str == "from enchiridion")
    {
	string text = read_file(BOOKPATH +"p"+ page);

	write("You quote from the "+ short() +":\n\n"+ text);
	say(QCTNAME(TP) +" solemnly intones:\n\n"+ text);

	return 1;                
    }

    return NF(CAP(query_verb()) +" what?\n");
}

public int
do_mark(string str)
{
    if (!strlen(str))
	return NF(CAP(query_verb()) +" what?\n");

    if (!parse_command(str, ({ }),
	"[a] / [the] / [this] 'page' [as] 'tab' %s", str))
	return NF(CAP(query_verb()) +" what?\n");

    int ix = member_array(str, alnum);

    if (ix == -1)
    {
	write("That would make for an invalid tab.\n");
    }
    else
    {
	earmarks[ix] = sprintf("%d", page);
	write("You have marked this page as tab "+ str +".\n");
    }

    return 1;
}

public int 
do_tab(string str)
{
    if (!strlen(str) || !parse_command(str, ({ }), "[to] [page] %s", str))
	return NF(CAP(query_verb()) +" what?\n");

    string text;
    int ix = member_array(str, alnum);

    if (ix == -1)
    {
	write("That is an invalid tab.\n");
	return 1;
    }

    sscanf(earmarks[ix], "%d", page);
    text = read_file(BOOKPATH +"p"+ page);

    write("You turn the "+ short() +" open to tab "+ str +":\n\n");
    TP->more(text);        
    return 1;
}

public void
init(void)
{
    ::init();

    if (TP != environment())
	return;

    add_action(  do_read, "read"     );
    add_action(  do_read, "wisread"  );
    add_action(  do_read, "open"     );
    add_action(  do_read, "wisopen"  );
    add_action(  do_read, "thumb"    );
    add_action(  do_read, "wisthumb" );
    add_action( do_quote, "quote"    );
    add_action( do_quote, "wisquote" );
    add_action(   do_tab, "tab"      );
    add_action(   do_tab, "wistab"   );
    add_action(  do_mark, "mark"     );
    add_action(  do_mark, "wismark"  );
    add_action(  do_mark, "earmark"  );
}

public void
init_arg(string arg)
{
    if (strlen(arg) < 30)
	return;

    earmarks = explode(arg, ";");
}

public string
query_auto_load(void)
{
    if (IS_SYBARITE(ENV(TO)))
	return MASTER + ":" + implode(earmarks, ";");
}                 

public string
query_recover(void)
{
    return (string)0;
}
