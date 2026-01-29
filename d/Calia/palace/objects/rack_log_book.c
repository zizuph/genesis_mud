/*  A log book that records special items taken from or
    donated to the rack.

    coder(s):   Maniac 
    history:    
               22/11/02   possible to hide recoverability      Maniac 
                8/7/02             Created                     Maniac 

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define HIDE_RECOVERABLE

#ifdef HIDE_RECOVERABLE
#include <std.h>
#include COUNCIL_HEADER
#include RECRUITER_HEADER
#include CALIAN_HEADER
#endif

#pragma save_binary

inherit CRPALACE_OBJECTS + "log_book";


#define BOOK_MAX_SIZE 3200



#ifdef HIDE_RECOVERABLE

#define EXTRA_SCROLL_TEXT2 \
        ("As you are councillor or recruiter, or someone who " + \
         "has made an outstanding rack contribution, " + \
         "the donation or borrowing of a recoverable item is " + \
         "indicated in the log by an exclamation mark at the end of " + \
         "a sentence. Currently others do not see these indications.\n")

#define EXTRA_SCROLL_TEXT \
        ("The donation or borrowing of a recoverable item is " + \
         "indicated in the log by an exclamation mark at the end of " + \
         "a sentence.\n")

/* 
 * Function:      query_sees_recoverable 
 * Description:   Gives back whether the specified living can 
 *                see recoverability of borrowed / donated 
 *                items. 
 * Returns:       int  - 1 if can see, 0 if not. 
 */ 
public int 
query_sees_recoverable(object pl) 
{ 
    seteuid(getuid()); 

    return (interactive(pl) && 
            (SECURITY->valid_write(file_name(this_object()), pl, 
                                   write_file) || 
             (pl->query_skill(CALIAN_RACK_POINTS) > 2500000) || 
              COUNCIL_CODE->is_council_member(pl->query_real_name()) || 
              RECRUITER_CODE->is_recruiter(pl->query_real_name()))); 
} 
#endif


/*
 * Function:     read_it 
 * Description:  Called when someone reads this scroll. 
 */ 
void
read_it(string str)
{
    string txt; 

    seteuid(getuid(this_object()));
    say(QCTNAME(this_player()) + " reads the " +
        QSHORT(this_object()) + ".\n");

    if (!scroll_file)
    {
        write("There was nothing to read in the " + QSHORT(this_object()) +
        ".\n");
        return;
    }

    if (file_size(scroll_file) >= 50000)
    {
        write("The scroll is too large to be read.\n");
        return;
    }

    txt = read_file(scroll_file); 

#ifdef HIDE_RECOVERABLE
    if (query_sees_recoverable(this_player())) 
    { 
        txt = EXTRA_SCROLL_TEXT2 + "\n" + txt + "\n" + 
              EXTRA_SCROLL_TEXT2; 
    } 
    else 
    { 
        txt = implode(explode(txt, "!"), "."); 
    } 
#else
    txt = EXTRA_SCROLL_TEXT + "\n" + txt + "\n" + 
          EXTRA_SCROLL_TEXT; 
#endif
    this_player()->more(txt); 
}



void
create_log_book()
{
    seteuid(getuid()); 
    set_name("book"); 
    set_adj("blue"); 
    set_short("blue book"); 
    set_long("A book with a blue cover. " + 
        "The title of the book is: \"Special Rack Items Log\".\n"); 
    set_file(CRPALACE_LOGS + "rack"); 
    set_max_size(BOOK_MAX_SIZE); 
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VOLUME, 1000); 
    add_prop(OBJ_M_NO_GET, 
	"The rack log book is fixed here by the magic of Caliana.\n"); 
}

/*
void
update_log_book(string new_line)
{
    ::update_log_book(new_line);
}
*/ 
