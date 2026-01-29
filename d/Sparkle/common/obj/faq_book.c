/*
 * faq_book.c            Sat Jan 30  1993
 *
 * A book with Frequently Asked Questions.
 * Hopefully this book will help newbies to stay alive a litle longer.
 *
 *   -- Styles
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

inherit S_STD_OBJ_DIR + "book";

void
create_book()
{
    set_name("book");
    add_name("faq_book"); /* Name used as a identifyer. */
    set_adj("red");
    set_title("Frequently Asked Questions");
    set_text_file(S_COMMON_HELP_DIR + "faq_book");

    set_short("book on a chain");
    set_long("A red book is chained to the wall. Its title says:"+
             "\n\n       -= "+ query_title() +" =-\n\n"+
             "                                    First edition.\n\n");

    add_prop(OBJ_M_NO_INS, "You can't do that. The chain is too short.\n");
    add_prop(OBJ_M_NO_GET, "You can't do that. The chain is too short.\n");
}

void
leave_env(object to, object from)
{
    ::leave_env(to, from);

    if (open)
    {
        write("You close the book.\n");
        say(QCTNAME(this_player()) + " closes the "+ short() +".\n");
    }
    open = 0;
}

int
read_book(string what)
{
  return ::read_book(what);
}

