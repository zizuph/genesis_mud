
inherit "/std/shadow.c";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../guild.h"

#define HE(x)		(x)->query_pronoun()
#define HIS(x)		(x)->query_possessive()
#define HIM(x)		(x)->query_objective()


//	Prototypes
void   flicker();

// 	Global variables
static int     Duration,
               Flicker;
               
static object  Playa,
               OldWieldFunc;
static string  OldShort;

static mixed   FlickMess = ({ 
       ({ "The black flames engulfing ", " flicker ominously.\n" }),
       ({ "The black flames dance up and down the weapon of ", "hissing and cracking dangerously.\n" }),
       ({ "A loud 'Pop!' can be heard as the black flames on ", "flare up momentarily.\n" }),
       ({ "The black flames enveloping ", " glow bizarrely, as no light or shadow is cast on the surroundings.\n" }),
       ({ "The black flames on ", " dims a little, yet you "
       +"notice no change in the luminance of the surroundings.\n" })
						});

public mixed
unwield(object ob)
{
     set_alarm(0.0, 0.0, remove_shadow);

    return (Duration == 0);
}


public void
remove_shadow()
{
    int     wt;
    object  env;

    remove_alarm(Duration);
    
    Duration = 0;


    if (objectp(Playa))
    {
        env = environment(Playa);
    }
    
    else if (objectp(env = environment(shadow_who)))
    {
        while (!env->query_prop(ROOM_I_IS))
            env = environment(env);
    }
    else
    {
        // if we don't have an environment, then let's just go away
        shadow_who->remove_object(); 
        ::remove_shadow();
    }

    if (!objectp(Playa))
    {
        tell_room(env, "The black flames engulfing the "
          + shadow_who->short() + " quietly flicker out of "
          + "existence.\n");
    }
    else
    {
        tell_room(env, "The sblack flames engulfing " + QTNAME(Playa)
          + "'s " + shadow_who->short() + " quietly flicker out of "
          + "existence as " + HE(Playa) + " releases " + HIS(Playa)
          + " grip upon it.\n", Playa);
          
        Playa->catch_msg("The searing-hot flames engulfing your "
          + shadow_who->short() + " quietly flicker out of existence "
          + "as you release your grip upon it.\n");
          
        shadow_who->remove_adj("black-flamed");
        shadow_who->set_short(OldShort);
        
        shadow_who->unwield_me();
        unwield(shadow_who);       
    }

    remove_alarm(Flicker);
    
    ::remove_shadow();
}


public int
enchant_weapon(int duration)
{
    object  env;

    if (!objectp(Playa))
    {
        ::remove_shadow();
        return 0;
    }

    env = environment(Playa);
    
    tell_room(env, QCTNAME(Playa) + "'s " + shadow_who->short()
      + " is suddenly engulfed in black flames.\n", Playa);
      
    Playa->catch_msg("Your " + shadow_who->short() + " is suddenly "
      + "engulfed in black flames.\n", Playa);

    Duration = set_alarm(99999.0, 0.0, remove_shadow);
    
    Flicker = set_alarm(20.0 + rnd() * 20.0, 0.0, flicker);
    
    OldShort = shadow_who->short();
    
    shadow_who->set_adj("black-flamed");
        
    shadow_who->set_short("black-flamed " + shadow_who->short());

    return 1;
}


public void
set_playa(object playa)
{
    Playa = playa;
}


public int
query_bf_summoned()
{
    return 1;
}


string
long()
{
    return (shadow_who->long() + "It is engulfed in black flames.\n");
}


public void
flicker()
{
    int     i;

    if (!objectp(Playa))
    {
        remove_shadow();
        return;
    }

    Flicker = set_alarm(30.0 + rnd() * 60.0, 0.0, flicker);

    i = random(sizeof(FlickMess));

    Playa->catch_msg(FlickMess[i][0] + "your "
      + shadow_who->short() + FlickMess[i][1]);
      
 	tell_room(environment(Playa), FlickMess[i][0] + QTNAME(Playa)
	  + "'s " + shadow_who->short() + FlickMess[i][1],
		Playa);
}


/*public string
stat_object()
{
    string  str = shadow_who->stat_object();

    str += "This weapon has been enchanted by a spell of the Society "
        +  "of Morgul Mages, engulfing it in flames, inflicting extra "
        +  "damage upon successful hits.\n"
        +  "Remaining duration: " + ftoa(get_alarm(Duration)[2])
        +  " seconds.\n";
    return str;
}*/


mixed query_flick_message() { return FlickMess; }

