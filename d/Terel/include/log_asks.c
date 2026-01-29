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

# pragma strict_types
# pragma no_clone
inherit "/std/act/asking";

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

public void catch_question(string str)
{
    if (!ask_id(str))

    SCROLLING_LOG("/d/Terel/log/asks",
        capitalize(this_player()->query_real_name())+
        " asked "+ capitalize(this_object()->query_name()) +
        ": "+ str);

    ::catch_question(str);
}

