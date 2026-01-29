// file name       /d/Avenir/common/dead/obj/flames_goddess.c copied from
// Fire Rose Petal Flames   /d/Avenir/common/holm/obj/flames.c       
// creator(s):      Lilith  01/20/97
// purpose:         Enchanted rose for Mascarvin Quest
// last update:     Lilith, Sep 2021: added PVP_ABILITY_DISABLED check.
//                  Lilith, Oct 2021: added 3 second delay for block instead
// note:            These flames result when a petal is dropped.
//                  It can be used to block exits for a short 
//                  period of time (<30 seconds).
//                  Related objects: rose_fire.c and rose_petal.c 
// bug(s):
// to-do:

inherit "/std/object";
#include "/d/Avenir/common/dead/dead.h"
#include <ss_types.h>
#include "/d/Genesis/specials/defs.h"
#define  TOSS_PROP  "_Avenir_Fire_Petal_Tosser"

object tosser;
int    in_effect = 0;             
string blocked = "";  
public void set_exit_blocked(string str) {    blocked = str;     }
public string query_exit_blocked()       {    return blocked;    }
public void set_tosser(object tp)        {    tosser = tp;       }

string short_desc();
string long_desc();

void
create_object()
{
    set_name("_Avenir_Petal_Flames");
    add_name("flames");
    set_adj("leaping");
    add_adj(({"orange", "red", "orange-red", "dancing"}));
    set_short(short_desc);
    set_pshort(short_desc);
    set_long(long_desc);
   
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_S_WIZINFO,  "These flames are the result of "+
        "dropping a petal from an enchanted fire rose. They are "+
        "designed to block an exit when the petal is used properly."+
        "Players with INT<50 and Illusion skills>40-59 should be "+
		"unaffected by the exit block. The flames also cast 2 "+
		"levels of light while in effect. \n");

    add_prop(MAGIC_AM_MAGIC, ({70, "illusion"}));
    add_prop(MAGIC_AM_ID_INFO,
	({"These flames are magical in nature.\n", 15,
      "These flames are an illusion.\n", 30,
      "They will dissipate in a short period of time.\n", 40,
	  "Only fools and those skilled in the art of illusion " +
	  "can pass through them.\n", 45}));

    add_prop(OBJ_I_LIGHT, 2);
}

string
long_desc()
{
    string str;
    str = "These orange-red flames are magical in nature. The "+
          "flames flicker and leap in a mesmerizing dance. "+
          "They are self-contained and do not seem to use any fuel "+
          "other than the air.\n";
    if (in_effect)
    {
        str += "It is blocking the exit leading "+ blocked +".\n";
    }
    return str;
}
  
string 
short_desc()
{
   string str;
   str = "cluster of leaping orange-red flames";
   if (in_effect)
	   str += " blocking the exit "+ blocked;
   return str;   
}	

void
burn_out()
{
    tell_room(environment(TO), "The "+ short() +" burn themselves "+
	    "out, leaving the air tainted with "+
		"the scent of scorched rose petals.\n");		
    remove_object();
}

void remove_toss_prop(object tosser)
{
    tosser->remove_prop(TOSS_PROP);
}

void
set_timer(int i)
{    
    set_alarm(itof(i), 0.0, burn_out);
    set_alarm(itof(i-1), 0.0, &remove_toss_prop(tosser));
}

void enable_flames()
{
	tell_room(environment(TO), "The flames spread to entirely "+
        "block the way "+ blocked +".\n");			
    in_effect = 1;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (!to || living(to)) 
        return;
    
    if (member_array(blocked, to->query_exit_cmds()) >= 0) 
    {
        set_alarm(3.0, 0.0, enable_flames);
    }
}

void
init()
{
    ::init();

    if (environment(TO) == environment(TP) && strlen(blocked)) 
    {
        add_action("test_exit", blocked);
    }
}

int
test_exit()
{
    if (!in_effect)
        return 0;
    if (TP->query_wiz_level())
    {
        write("The flames part for you, allowing you safe passage.\n");
        say(QCTNAME(TP) +" parts the flames and steps through.\n");    
        return 0;
    }
	/* If you tossed the petal you can pass the exit */
    if (TP->query_prop(TOSS_PROP))
    {
        write("You tossed the petal and so you are spared from the "+
            "flames.\n");
        say("The flames part for "+ QCNAME(TP) +".\n");
        return 0;
    }	
	/* If intelligence is low enough just walk through */ 
    if (TP->query_stat(SS_INT) < 50) 
    {
        write("You walk right through the "+ short() +".\n");
        say(QCTNAME(TP) +" walks heedlessly through the flames.\n");
        return 0;
    }
	/* If magic skill is high enough, I ignnore the illusion */
    if (TP->query_skill(SS_FORM_ILLUSION) > 40 + random(20))
    {
        write("You recognize the flames for what they are, an "+
            "illusion, and pass safely through.\n");
        say(QCTNAME(TP) +" parts the flames and steps through.\n");
        return 0;
    }
	// check to see if block is globally disabled
/* This obj does the 3 second delay after notice before block takes effect 
	if (PVP_ABILITY_DISABLED)
	{
		write("You feel somewhat scorched by the flames, but pass through "+
		    "them unimpeded.\n");
		say(QCTNAME(TP) +" walks into the flames.\n");
		return 0;
	}
*/	
    write("The "+ short() +" drive you away with their heat! You "+
        "cannot go "+ blocked +".\n");
    say(QCTNAME(TP) +" tries to go "+ blocked +" but is driven back "+
        "by the flames!\n");
    return 1;
}
