/*magic_sabre.c
*magical sword for the elven outpost captain
*By Mhyrkhaan, November 1998.
*/

inherit "/std/weapon";
inherit "/d/Genesis/magic/resist";
inherit "/lib/keep";

#include "/d/Emerald/sys/macros.h";
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <tasks.h>

void
create_weapon()
{
    set_name("sabre");
    add_name( ({ "sword", "blade" }) );
    add_name("thalshara");
    set_short("thin green sabre");
    add_adj( ({"thin" , "green"}) );
    set_long("Elegant and finely crafted, the blade of this sabre has"
      + " a green tint to it which, despite heavy use, never seems to"
      + " lose its lustre. The hilt is engraved with tempered silver,"
      + " which has been shaped into odd symbols you do not recognize.\n");
    set_hit(40);
    set_pen(35);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(this_object());
    add_prop(OBJ_I_WEIGHT, 1300); 
    add_prop(OBJ_I_VOLUME,  550);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 35) + 1000);
    set_hands(W_ANYH);
    add_prop(OBJ_M_NO_BUY, 1); 
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This sword is an any-handed 40/35 " +
        "sword. It has one special which increases enemy fatigue, while"
    + " reducing that of the wielder. You must have a sword skill"
      + " of 55 or higher to use it.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"Your powers tell you the sword is " +
        "named Thalshara. There is a power within of arcane nature.\n", 10}));
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    set_keep();
}

mixed
wield(object what)
{
    /*
     * For now, lets let everyone use it. Perhaps later, when there
     * are more such beings, we will add the restriction.
     */
//  if (CREATURE_OF_VS(this_player()))
//  {
//      write("The sabre dims as it resists your attempts to wield it.\n");
//      return -1;
//  }
  
    if (this_player()->query_skill(SS_WEP_SWORD) <= 55)
    { 
        write("The sabre seems awkward and heavy in your grasp. You don't feel " +
            "you have the skill to use this blade.\n");
        return -1;
    }
  
    write("As you wrap your hands around the hilt, you are struck with"
      + " an impression that this sword will be a worthy companion.\n");
    set_alarm(0.0, 0.0, &tell_room(environment(this_player()), 
        "The " + short() + " shimmers briefly!\n"));

    return 0;
}


public int
did_hit(int aid, string hdesc, int phurt, object enemy,
        int dt, int phit, int dam)
{
    object me = query_wielded();
    int fat, res;

    /* No effect if the weapon missed or the target is not a creature of VS */
    /* Actually, since we don't have very many creatures of VS in the game */
    /* yet, lets just leave that as a future restriction. */
    if (phurt < 0)
    {
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    res = spell_resist(me, enemy, SS_ELEMENT_LIFE, TASK_DIFFICULT);

    /* Try to sap fatigue */
    if (fat = random(5) * (100 - res) / 100)
    {
    	enemy->add_fatigue(-fat);
    
    	if ((fat > 3) && !enemy->query_npc())
    	{
    	    enemy->catch_tell("As the " + short() + " strikes you, you feel " +
    		"your energy being drained away!\nYou feel more tired.\n");
    	}
    
    	fat /= 2;
    
    	if (fat > 0)
    	{
    	    me->add_fatigue(fat);
    
    	    if ((fat > 1) && !me->query_npc())
    	    {
    		me->catch_tell("As your " + short() + " strikes " +
    		    enemy->query_the_name(me) + ", you feel energy pulse " +
    		    "through your body!\nYou feel less tired.\n");
    	    }
        }
    }

    /* Reduce target's CON */
    if (!random(10))
    {
    }
        
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
