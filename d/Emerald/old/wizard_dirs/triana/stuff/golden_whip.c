inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#define PATH "/d/Avenir/goldberry/private/obj/"

#define PERS QCTNAME(this_player())
#define POSS this_player()->query_possessive()
#define PRON this_player()->query_pronoun()

string query_auto_load() {if(environment() -> query_real_name()=="tepisch")
  return MASTER; return 0;}
 
void
create_object()
{
    set_name("bullwhip");
    add_adj("lordly");
    set_short("lordly bullwhip");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);


    set_long(
"This long and nasty looking whip belongs to the Lord of Avenir.\n"+ 
"Should the Lord wish to know more of the whip, the command: help whip\n"+
"would be most helpful.\n");

   add_cmd_item("whip", "help",
"\n Here are the possible commands for the whip:\n"+
"\n"+
"		whip            : need we describe this one?\n"+
"		coil            : properly coil the whip.\n"+     
"		unfurl          : ready the whip for helpful emphasis.\n"+
"               brandish        : give it a try, lots-o'-fun.\n"+ 
"\n");

    add_prop(OBJ_I_VALUE, 864000);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

void
init()
 {
   ::init();
   if(environment() == this_player())
   { 
     add_action("whip_func", "whip");
     add_action("coil", "coil");
     add_action("unfurl", "unfurl");
     add_action("brandish", "brandish");  
   }
 }

int
whip_func(string arg)
 {
    string str;

    if(!arg)
     {
      write(
"You humbly request of those around you to take interest in working.\n");
      say("Whhhiittttt.....\n");
      say("CRRRAAAAAAAAACK!!!\n");
      say(
PERS + " lashes out with " +POSS+ " lordly bullwhip, encouraging you to "+
"get to work.\n");
   return 1; 
     }
   notify_fail("Whipping a target not possible _yet_.\n");
  }

int
coil()
 {
   write(
"You carefully coil up the nice little whip and store it away.\n");
   say(
PERS + " casually coils " + POSS + " lordly bullwhip and stores it away.\n"+
"You feel somewhat more secure now.\n"); 
    return 1;
 }
   
int
unfurl()
 {
   write(
"You take hold of the bullwhip and slowly unfurl it, readying it for use.\n");
   say(
PERS + " slowly unfurls " + POSS + " lordly bullwhip with a wicked gleam "+
"in " + POSS + " eyes.\n"+
"You don't feel quite as safe as you did a moment ago....\n");
     return 1;
 }

int
brandish()
 {
   write(
"With a look of determination, you firmly brandish your bullwhip,\n"+
"suggesting to those around you to get busy or else....\n");
   say(
PERS + " eyes you carefully as "+PRON+" takes a firm hold of "+POSS+
" lordly bullwhip.\n" + "Perhaps you should get to work?\n");
  return 1;
 }
   
   

