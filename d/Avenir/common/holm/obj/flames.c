// -*-C++-*- 
// Fire Rose Petal Flames   /d/Avenir/common/holm/obj/flames.c       
// creator(s):      Lilith  01/20/97
// purpose:         Enchanted rose for Beast Treasure
// last update:     
// note:            These flaems result when a petal is dropped.
//                  It can be used to block exits for a short 
//                  period of time.
//                  Related objects: rose.c and petal.c 
// bug(s):
// to-do:

inherit "/std/object";
#include "/d/Avenir/common/holm/holm.h"
#include <ss_types.h>
#define  ROSE_PROP  "_Magic_Rose_Owner"

int    in_effect = 0;
int    set_timer(int i);             
string blocked = "";
string set_exit_blocked(string str) {    return blocked = str;     }
string query_exit_blocked()         {    return blocked;           }

void
create_object()
{
    set_name("Petal_Flames");
    add_name("flames");
    set_adj("leaping");
    add_adj(({"orange", "red", "orange-red", "dancing"}));
    set_short("leaping orange-red flames");
    set_pshort("leaping orange-red flames");
    set_long("@@long_desc");
   
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_S_WIZINFO,  "These flames are the result of "+
        "dropping a petal from an enchanted fire rose. They are "+
        "designed to block an exit when the petal is used properly."+
        "\n");

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
   
void
burn_out()
{
    tell_room(environment(TO), "The "+ short()+ " burn themselves "+
        "out, leaving the air tainted with the scent of scorched "+
        "rose petals.\n");
    remove_object();
}


void
set_timer(int i)
{
    set_alarm(itof(i), 0.0, burn_out);
}



void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (!to || living(to)) 
        return;
    
    if (member_array(blocked, to->query_exit_cmds()) >= 0) 
    {
        in_effect = 1;
    }
}


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
    if (TP->query_prop(ROSE_PROP))
    {
        write("The virtues of the enchanted rose spare you from the "+
            "flames.\n");
        say("The flames part for "+ QCNAME(TP) +".\n");
        return 0;
    }
    if (TP->query_stat(SS_INT) < 30) 
    {
        write("You walk right through the "+ short() +".\n");
        say(QCTNAME(TP) +" walks heedlessly through the flames.\n");
        return 0;
    }
    if (TP->query_skill(SS_FORM_ILLUSION) > 40 + random(30))
    {
        write("You recognize the flames for what they are, an "+
            "illusion, and pass safely through.\n");
        say(QCTNAME(TP) +" parts the flames and steps through.\n");
        return 0;
    }
    write("The "+ short() +" drive you away with their heat! You "+
        "cannot go "+ blocked +".\n");
    say(QCTNAME(TP) +" tries to go "+ blocked +" but is driven back "+
        "by the flames!\n");
    return 1;
}
