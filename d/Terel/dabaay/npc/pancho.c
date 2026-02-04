/*  
 * Pancho, of Panchos by Dabaay (panchos.c)
 * Goldberry 5/13/99
 *
*/

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";
 
#include <ss_types.h>
#include <money.h>

create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;

   set_name("pancho");
   set_race_name("human");
   set_adj("sleepy");
   set_long("Here is a man who surely likes to sample his wares. "+
            "He has the look of one pleased with life, and without "+
            "a care in the world.\n");

   default_config_npc(40);

   set_all_hitloc_unarmed(25);
   set_gender(MALE);
   set_chat_time(8);
   add_chat("Niiiiiiice.");
   add_chat("This is a sweet, sweet bowl of stew!");
   add_chat("Forget about it.\n");

   add_prop(LIVE_I_ALWAYSKNOWN, 1);

   add_prop(OBJ_M_NO_ATTACK,"Pancho turns his back to you and goes "+
       "on with business.\n");

   trig_new("%w 'arrives' %s", "react_enter");
}

int
greet_enter(string who)
{
    command("greet " + who);
    command("say Welcome to my humble establishment!");
}

int
react_enter(string who, string dummy1)
{
    if (who == "Town_guard")
    {
        command("say Cheese-it! The guards!");
        command("say to town_guard Good day to you fine sir!");
        return 1;
    }
    set_alarm(1.0, -1.0, "greet_enter", who);
}


public void
emote_hook(string emote, object actor, string adverb=0)
{
    int ran;
    string who;
    
    if (!present(actor, ETO)) return;
 
    who = actor->query_real_name();
    
    switch (emote)
    {
    case "smile":  
        command("smile merrily " + who);  
        break;
    case "grin":
        command("grin broadly " + who);
        break;
    case "ponder":
        command("say to " + who + " Need food for thought?");
        break;
    case "cough":
        command("say to " + who + " Nasty thing, colds. Best way to "+
                "cure them is to eat!");
        break;
    case "choke":
        command("say Can anyone here help this pour soul?");
        command("say to " + who + " Perhaps a drink to wash that down?");
        break;
    case "puke":
        command("shout Hey Maggie! Got another thunder-puddle to mop up!");
        command("mumble I sure ain't cleaning that up....");
        command("emote glances disgustedly at the pool of vomit.");
        break; 
    }
}

/*
 * Find some player somewhere and go there
 */
find_someone(name)
{
    object ob;

    ob = find_player(name);

    if (!ob)
	return 0;

    move_living("X",environment(ob));
    return 0;
}
