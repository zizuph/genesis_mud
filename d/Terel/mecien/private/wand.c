inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

init(){
add_action("slay", "slay");
::init();
}

create_object(){

set_name("wand");
set_adj("arcane");
add_adj("ivory");

set_long(
"It is a thin elegant ivory wand, covered with arcane runes.\n"
);

}

slay(string str){

object who;

if(!str) return 0;
who=find_living(str);
if(who){
write("You raise the ivory wand against " + QNAME(who) + "\n");
say(QCTNAME(this_player()) + " raises an arcane ivory wand!\n");
tell_room(environment(who), QCTNAME(who) + " is surrounded by " +
 "a mysterious power and bursts into white flames!\n", who);
who->catch_msg("You have been destroyed!\n");
who->remove_object();
return 1;
}
write("Slay who?");
}

