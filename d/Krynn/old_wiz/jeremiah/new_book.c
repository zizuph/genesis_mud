/* Note: This code may look like C, but is really -*- LPC -*- */

//
// A blank book
//
 
inherit "/std/scroll";
 
#include <macros.h>
#include "/d/Shire/defs.h"
#include "/d/Shire/noldor/noldor.h"
 
static string gTitle;
static string gFilename;
 
create_scroll()
{
    set_name("book");
    add_name("_book_i_write_");
    set_short("new book");
    set_long("A book without a title.\n");
    
    seteuid(getuid());
}
 
init()
{
    ::init();
    add_action("do_write", "write");
}
 
public int
done_writing(string story)
{
    object scr;
    
    write_file(NOLDOR_BOOK_DIR + "new/"+ gFilename, story);
    write_file(NOLDOR_BOOK_DIR + "new/log", ctime(time()) + 
	       " " + TP->query_real_name() + " wrote " + gFilename + ".\n");
    write("You finish your great book.\n");
    say(QCTNAME(TP) + " finishes a great book.\n");
     
    scr = clone_object("/std/scroll");
    scr->set_name("book");
    scr->add_name(gTitle);
    scr->add_adj("new");
    scr->set_long("This is a new book "+ gTitle + ". " + 
		  "This new book was just written by "+ QCTNAME(TP)+
		  ".\n");
    scr->set_file(NOLDOR_BOOK_DIR + "new/" + gFilename);
    scr->add_prop(OBJ_I_NOLDOR_NEW_BOOK, 1);
    scr->move(TP);
    remove_object();
    return 1;
}

/*
 * Converts a title e.g. "The Story of the Noldor" 
 * into a filename "The_Story_of_the_Noldor"
 */
public string
convert_title_to_filename(string title)
{
    return implode(explode(title, " "), "_");
}
 
/*
 * Converts a filename, e.g. "The_Story_of_the_Noldor"
 * into a title, "The Story of the Noldor".
 */
public string
convert_filename_to_title(string fname)
{
    return implode(explode(fname, "_"), " ");
}

public int
do_write(string title)
{
    notify_fail("What about a title?\n");
    if (!title || !strlen(title))
	return 0;
 
    gTitle = title;
    gFilename = convert_title_to_filename(title);
    
    write("You start writing a book.\n");
    say(QCTNAME(TP) + " starts writing a book.\n");
    
    clone_object("/std/edit")->edit("done_writing", "");
    return 1;
}
 
