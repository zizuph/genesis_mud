/*
*	coded by Amelia
*	with code generously donated from Maniac's stutter_object.c
*	This object is used along with the frog_shadow
*	to turn player's "voice" into a croak
*/

inherit "/std/object";
/*
#include "pond.h"
*/
#include <macros.h>
#include <stdproperties.h>


object tp = this_player();
object TO = this_object();

void
create_object()
{
	set_short("frog_croaker");
	set_long("frog_croaker");
	set_name("frog_croaker");
	set_no_show();
	add_prop(OBJ_I_NO_DROP, 1);
	add_prop(OBJ_I_WEIGHT, 0);
	add_prop(OBJ_I_VOLUME, 0);
	add_prop(OBJ_M_NO_GIVE, 1);
	

}

void
init()
{
    add_action("do_croak","",1);
    ::init();
}


int
do_croak(string str = "")
{
   string verb;
   string *say_cmds; /* list of commands resulting in a 'say' */

   say_cmds = ({"say","rsay"});
   verb = query_verb();

   if (verb[0] == ''') 
   {
      verb = "say";         /* Hep! .. a say cmd in disguise! */
      str = extract(query_verb(),1)+" "+ str;
   }

   while(str[0] == ' ')     /* remove all spaces at start of say line */
      str = extract(str,1);

   if(member_array(verb, say_cmds) == -1)
      return 0;

   if (tp->query_get_echo())
      write("You croak: "+ str + "\n");
   else
   {
      write ("Ok.\n");
      return 1;
   }
   
   tell_room(environment(tp), QCTNAME(tp)+" croaks: "+
      str+"\n", ({tp}));

   return 1;
}


destruct_frog_croaker()
{

	seteuid(getuid(TO));
	TO->remove_object();

}
