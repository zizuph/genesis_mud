/* 
 * paranoia.c - make someone paranoid
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#define PERIOD  (30.0 + itof(random(30)))

int gAlarm;     /* Effect alarm */
int gLevel;     /* Level of insanity */
object gTarget; /* The target of the insanity */

varargs void do_effect(int no_repeat);

void
create_object()
{
    add_name("paranoia");
    add_name(PARA_ID);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO,
        "A magical object affecting the bearer with paranoia.\n");

    set_no_show();
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (gAlarm)
    {
        remove_alarm(gAlarm);
        gAlarm = 0;
    }
    
    remove_spell_effect_object();
    return 1;
}

public int
start()
{
    set_spell_effect_desc("paranoia");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    if (move(spell_target,1))
    {
        remove_spell_effect_object();
        return 0;
    }

    gAlarm = set_alarm(PERIOD, 0.0, do_effect);
    set_alarm(3500.0 - itof(spell_target->query_stat(SS_WIS) * 10),
        0.0, dispel_spell_effect);

    return 1;
}

void
do_effect_one()
{
    string s;
    
    switch (random(10))
    {
    	case 0..2:
            s = "Someone snickers.";
            break;
        case 3..4:
            s = "Someone giggles.";
            break;
        case 5:
        default:
            s = "Someone chortles.";
            break;
    }
    if (stringp(s))
        spell_target->catch_tell(s + "\n");
}

void
do_effect_many(object *ob)
{
    string s;
    object *obi = filter(ob, interactive);

    /* The best effect is if other players seem to conspire about or
       laugh at the person, */

    if (sizeof(obi) > 1)
    {
    	object ob1, ob2;

    	ob1 = ob2 = obi[random(sizeof(obi))];
    	while (ob1 == ob2)
    	    ob2 = obi[random(sizeof(obi))];

    	switch (random(10))
    	{
    	    case 0..3:
    	    s = ob1->query_The_name(spell_target) + " whispers something to " +
    	    ob2->query_the_name(spell_target) + ".";
    	    if (random(2))
    	        set_alarm(3.0 + itof(random(4)), 0.0, &do_effect(1));
    	    break;

    	    case 4..5:
    	    s = ob1->query_The_name(spell_target) + " points at you.";
    	    break;

    	    case 6:
    	    s = ob1->query_The_name(spell_target) + " nudges " +
    	    ob2->query_the_name(spell_target) + ".";
    	    break;

    	    case 7:
    	    s = ob1->query_The_name(spell_target) + " whistles innocently.";
    	    if (random(3))
    	        set_alarm(4.0 + itof(random(5)), 0.0, &do_effect(1));
    	    break;

    	    case 8..9:
    	    s = ob1->query_The_name(spell_target) + " grins.";
    	    break;
    	}
    }
    else if (sizeof(obi) == 1)
    {
    	object ob1;

    	ob1 = obi[0];

    	switch (random(10))
    	{
            case 0..2:
    	    s = ob1->query_The_name(spell_target) + " grins.";
    	    break;

    	    case 3..5:
    	    s = ob1->query_The_name(spell_target) + " whispers something " +
    	    "to someone.";
    	    break;

    	    case 6..7:
    	    s = ob1->query_The_name(spell_target) + " snickers.";
    	    break;
            default:
                break;
    	}
    }
    else
    {
        do_effect_one();
        return;
    }

    if (stringp(s))
        spell_target->catch_tell(s + "\n");
}
    	    

varargs void
do_effect(int no_repeat)
{
    int i;
    object *ob;

    ob = FILTER_LIVE(all_inventory(E(spell_target)) - ({ spell_target }));

    if (!sizeof(ob))
    {
    	/* There are no other people in the room */
    	if (gLevel > 15)
    	{
    	    do_effect_one();
    	}
    }
    else
    {
    	do_effect_many(ob);
    }

    if (!no_repeat)
    {
        gLevel++;
        gAlarm = set_alarm(PERIOD, 0.0, do_effect);
    }
}
