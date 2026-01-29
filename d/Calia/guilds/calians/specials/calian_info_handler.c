
/* 
   Calian info handler object, handles all the functionality relating
   to Calians writing and storing info about themselves, or reading info 
   about other Calians.

   Coded by Maniac

   History: 
           27/1/2001     updated for new dir            Maniac
           26/8/98       display method changed         Maniac
           28/11/96      moved to Glykron's directory   Maniac
           10/6/96       regular <more> used            Maniac
           12/5/95       Delay between edits            Maniac
           11/5/95       Created                        Maniac
*/

#pragma save_binary
#pragma no_clone

inherit "/std/object";

#include <std.h>
#include "defs.h"
#define CALIAN_FILE_DIR (CRPALACE_TEXTS+"calian_player_info/")
#define EDIT "/obj/edit"
#define MESSAGE_MAX_CHARS 1000
#define MIN_TIME_BETWEEN_EDITS 900

static mapping recently_edited = ([ ]);

void
done_editing(string message)
{
    object tp = this_player();
    string nm, s;

    if (message == "")
        return;

    if (strlen(message) > MESSAGE_MAX_CHARS) {
        tell_object(tp, "That info was too long! It has not been added. " +
                        "Please try again and enter shorter info about " +
                        "yourself.\n");
        return;
    }

    recently_edited += ([capitalize(tp->query_real_name()) : time()]); 

    nm = CALIAN_FILE_DIR + capitalize(tp->query_real_name());
    seteuid(getuid()); 
    if (file_size(nm) > -1)
        rm(nm); 
    write_file(nm, message);

    tell_object(tp, "Your info has now been added.\n");
}


/* A player attempts to add Calian info about himself */
void
add_info(object tp)
{
    int last_edit_time, t;
    string nm;

    if (!tp->query_wiz_level()) {
        nm = capitalize(tp->query_real_name());
        t = time();
        if (last_edit_time = recently_edited[nm]) {
            if ((t - last_edit_time) < MIN_TIME_BETWEEN_EDITS) {
                tell_object(tp, "You've edited your info within the "+
                   "last 15 minutes, and may not do a re-edit until "+
                   "that time has elapsed. This is to prevent usage of "+
                   "cinfo as a kind of tell line.\n");
                return;
            }
            else 
                recently_edited = m_delete(recently_edited, nm);
        }
    }

    set_this_player(tp);
    tell_object(tp, "You may now enter your Calian player info. Please " +
                    "do not exceed " + MESSAGE_MAX_CHARS/80 + " lines " +
                    "(" + MESSAGE_MAX_CHARS + " characters).\n");
    seteuid(getuid());
    clone_object(EDIT)->edit("done_editing");
}


/* Remove Calian info about a player */
void
remove_info(mixed tp)
{
    string nm;

    if (objectp(tp))
    {
        nm = CALIAN_FILE_DIR + capitalize(tp->query_real_name());
    
        if (file_size(nm) == -1)  {
            tell_object(tp, "There is no Calian player info about you to " +
                            "remove!\n");  
            return;
        }
        seteuid(getuid());
        rm(nm);
        tell_object(tp, "Ok, your Calian player info has been removed.\n");
    }
    else if (stringp(tp))
    {
        nm = CALIAN_FILE_DIR + capitalize(tp);
        if (file_size(nm) == -1)  {
            return;
        }
        seteuid(getuid());
        rm(nm);
    }        
}

void
create_object()
{
    int i;
    string *calians;

    seteuid(getuid(this_object()));

    calians = get_dir(CALIAN_FILE_DIR); 
    for (i = 0; i < sizeof(calians); i++)  
        if (!SECURITY->exist_player(calians[i]))  
             rm(CALIAN_FILE_DIR + calians[i]);
}

