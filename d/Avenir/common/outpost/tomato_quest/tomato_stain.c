// Tomato stain for the tomato-drop quest.  
// creator(s):  Kazz
// last update: April 1995
// purpose:     placed in player's inventory when a tomato is dropped on them.
// note: 	original framework for this provided by Aridor in
//		Krynn/Aridor/open/it.c
// to-do:	remove_stain() could count stains and give different msgs.
//		(at least 'some stain is gone' and 'all stains are gone')
// bugs:	

inherit "/std/object";

#include <macros.h>

#define DEBUG

#ifdef DEBUG
#define D(x) find_player("kazz")->catch_msg("tomato_stain debug: " + (x))
#else
#define D(x) ;
#endif

#define STAIN_SUBLOC  	"_avenir_tomato_stain_subloc"

void
create_object()
{
    set_name("tomato_stain");
    set_long("Tomato stains cover everything.\n");
    set_no_show();		// hide this item from inventory.
}

void
enter_env(object dest, object old)
{
// turned off test for interactive() since this will only be
// going into Kazz (testing) or Pompour (npc) and in both cases
// I want the description added!

//    if (interactive(dest))
	dest->add_subloc( STAIN_SUBLOC,this_object());
    ::enter_env(dest, old);
}

void
leave_env(object from, object to)
{
// removed for same reason as in enter_env()    
//   if (interactive(from))
      from->remove_subloc( STAIN_SUBLOC );
    ::leave_env(from, to); 
}

string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
    
    if (subloc != STAIN_SUBLOC)
      return me->show_subloc(subloc, me, for_obj);
    
    if (me->query_prop("_temp_subloc_show_only_things"))
      return "";
    
    if (for_obj == me)
      str = "You are ";
    else
      str = capitalize(me->query_pronoun()) + " is ";
    
    return str + "covered with rotten tomato mush.\n";
}


void
init_arg(string str) { }



void
remove_stain()
{
    environment(this_object())->catch_msg(
	     "The tomato stain finally fades from your clothing.\n" );
    remove_object();
} // remove_stain()


// call this to cause the stain to be removed eventually
void
set_remove_timer()
{
    // 600 seconds = 10 minutes.
    set_alarm( 600.0, 0.0, "remove_stain" );
} // set_remove_timer()


