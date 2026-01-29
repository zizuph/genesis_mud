/*magic_sabre.c
*magical sword for the elven outpost captain
*By Mhyrkhaan, November 1998.
*/

inherit "/std/weapon";
inherit "/d/Genesis/magic/resist";

#include "/d/Emerald/sys/macros.h";
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <tasks.h>

void
create_weapon()
{
    set_name("sabre");
    add_name("thin");
    add_name("thalshara");
    set_short("thin green sabre");
    add_adj( ({"thin" , "green"}) );
    set_long("This thin sabre looks to made of steel, " +
        "however upon cloer inspection the blade has a green tint to " +
        "it. The shine of the blade seems to go to the core of the sword. Almost as " +
        "if no matter how much damage this sword takes, it never lose " +
        "it's freshly polished luster. You notice fine runes engraves along the " +
        "edge of the blade. The hilt is made of mithril, and wrapped in white " +
        "leather that is bound with gold wire.\n");
    set_hit(40);
    set_pen(35);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(this_object());
    add_prop(OBJ_I_WEIGHT, 1300); 
    add_prop(OBJ_I_VOLUME,  550);
    set_hands(W_ANYH);
    add_prop(OBJ_M_NO_BUY, 1); 
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This sword is a any handed 40/35 " +
        "sword. It has one special capiable of 400 to 650 points of " +
        "damamge. You mus thave a sowrd skill of 55 or higher to use it.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"Your powers tell you the sword is " +
        "named Thalshara. You get the feeling it is VERY old.\n", 10}));
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
}

mixed
wield(object what)
{
    if (CREATURE_OF_VS(this_player()))
    {
        write("The sabre dims as it resists your atempts to wield it.\n");
        return -1;
    }
  
    if (this_player()->query_skill(SS_WEP_SWORD) <= 55)
    { 
        write("The sabre seems awkward and heavy in your grasp. You don't feel " +
            "you have the skill to use this blade.\n");
        return -1;
    }
  
    write("As you wrap your hands around the soft leather hilt, you are " +
        "amazed at the feeling of contentment you get from wielding this " +
        "sword.\n");
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
    if ((phurt < 0) || !CREATURE_OF_VS(enemy))
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
