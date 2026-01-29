
/*   
    The infamous man-eating clam...er...person-eating...

    coder(s):    Amelia

    Modified by Maniac 7/9/96
    added shut to add_ask and changed desc in my_long
    Hyde 27NOV15

 */

inherit "/std/creature";
inherit "/std/act/action"; 

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <composite.h>
#include <formulas.h>
#include <cmdparse.h>
#include <const.h>
#include "defs.h"

#include SEA_QUESTS

int bound = 0;
int unbind_alarm = 0;

void
create_creature()
{
   set_name("clam");
   set_race_name("clam");
   set_short("giant clam");
   set_pshort("giant clams");
   set_adj("giant");
   set_gender(G_NEUTER);
   set_long(VBFC_ME("my_long"));

   set_stats(({100, 10, 200, 10, 10, 100})); 

   add_prop(NPC_I_NO_LOOKS, 1); 
   add_prop(LIVE_I_NEVERKNOWN, 1); 

   set_act_time(10);
   add_act("burp loudly");
   add_act("emote emits a stream of water.");
   add_act("emote groans and gurgles.");

   add_prop(OBJ_M_NO_ATTACK, "@@no_attack");
}


void
unbind()
{
    bound = 0;
    unbind_alarm = 0;
    command("emote breaks the ropes and is once again free!");
}

string
no_attack()
{
    object tp = this_player(); 

    if (bound)
         return ("You wouldn't stand a chance of getting through that " +
                "shell!\n"); 
   
    tell_room(environment(tp), "The clam suddenly opens "+
       "and swallows "+QTNAME(tp)+" whole!\n", tp);
    tp->catch_msg("The clam suddenly opens and swallows you!\n");
    tp->move_living("M", INSIDE_CLAM, 1);
    tp->catch_msg("You are being eaten alive!!\n");
    return "";
}


int
do_bind(string str)
{
    object rope, clam, tp;

    if (!stringp(str) || !strlen(str)) {
        notify_fail("Bind what with what?\n");
        return 0;
    }

    if (bound)
    {
        notify_fail("The clam is already bound!\n");
        return 0;
    }

    tp = this_player(); 

    if (!parse_command(str, all_inventory(environment(tp)) + 
                            all_inventory(tp), 
                           " %o 'with' %o ", clam, rope)) { 
        notify_fail("Bind what with what??\n");  
        return 0;
    }

    if (clam != this_object()) { 
        notify_fail("Maybe binding the clam would be better!\n"); 
        return 0;
    } 

    if (!rope->id("rope"))
    {
        notify_fail("You can't bind the clam with that!\n");
        return 0;
    }

    rope->remove_object();
    bound = 1;

    unbind_alarm = set_alarm(1000.0, 0.0, unbind);

    write("You bind the clam with your rope.\n");
    say(QCTNAME(this_player())+" binds the clam with "+
        tp->query_possessive()+" rope.\n");
    return 1;
}


void
init_living()
{
    ::init_living();
    add_action(do_bind,"bind");
    add_action(do_bind,"tie");
    add_action(do_bind,"shut");
}



string
my_long()
{
    if(!bound)
        return ("This is the largest clam you have ever seen. "+
                "It is dark brown and as big as a room. It looks " +
                "rather menacing. It would need to " +
                "be shut to safely pass it.\n"); 

    return ("This is the largest clam you have ever seen.  "+
           "It is dark brown and as big as a room.  Currently "+
           "it is bound by a rather large rope so it cannot open "+
           "up.\n");
}

int query_bound() { return bound; }
