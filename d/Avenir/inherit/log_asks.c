// file name:   /d/Avenir/inherit/log_asks.c
// creator(s):  Lilith Feb 1996
// last update: 
// purpose: 	To log questions asked of npcs.
// note:	Should be a big help in figuring out what add_asks
//              are needed. This should not be used long-term.
//
//              Logged to /d/Avenir/log/asks 
// bug(s):	
// to-do:	

#if 0
#pragma strict_types

/*
 * Disabled for now since it's of limited use and improperly designed.
 */

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

public void
catch_question(string question)
{
    if (!ask_id(question))
    {
	SCROLLING_LOG("/d/Avenir/log/misc/asks",
	    capitalize(this_player()->query_real_name())+
	    " asked "+ capitalize(this_object()->query_name()) +
	    ": "+ question);
    }

    ::catch_question(question);
}
#endif
