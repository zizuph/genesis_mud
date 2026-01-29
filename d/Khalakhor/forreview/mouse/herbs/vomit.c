/* bryony vomiting object, coded by Elizabeth Cook/Mouse, June 1997 */
inherit "/std/poison_effect";
#include <poison_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../mouse.h"


void create_poison_effect() 
{
     set_strength(50);
     set_poison_type("herbal");
     set_silent(1);
     set_time(500);
     set_interval(20);
     set_damage( ({ POISON_USER_DEF, 0}) ); 
}

void
special_damage(int damage)
{
    int num = random(5);
    switch(num)
    {
        case 0:
             tell_object(poisonee,"Your stomach feels a bit unsettled.\n");
             break;

        case 1:
             tell_object(poisonee,"Your mouth has become very dry.\n");
             break;

        case 2:
             tell_object(poisonee,"Your stomach twists and wrenches itself "+
             "into a tight ball.\n");
             break;

        case 3:
             tell_object(poisonee,"You suddenly feel clammy and weak; "+
             "your knees begin to shake beyond your control.\n");

        case 4:
        {
             int stuffed = poisonee->query_stuffed();
             if(stuffed < 100)
                  poisonee->eat_food(stuffed-2*stuffed);
             else
                  poisonee->eat_food(-100);
             tell_object(poisonee,"The hard knot in your stomach "+
             "rises in your throat, bursting from your mouth and nostrils "+
             "in a bright green mass.\n");
             tell_room(ENV(poisonee),QCTNAME(poisonee)+
             " spews forth a mass of bright green vomit.\n",poisonee);
             break;
        }
     }
}
