/* periwinkle poison object, coded by Elizabeth Cook/Mouse, June 1997 */
inherit "/std/poison_effect";
#include <poison_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../mouse.h"

int num = 0;

void create_poison_effect() 
{
     set_strength(60);
     set_poison_type("herbal");
     set_silent(1);
     set_time(600);
     set_interval(20);
     set_damage( ({ POISON_USER_DEF, 0}) ); 
}

void
special_damage(int damage)
{

    if(num<11)
    {
        int a = random(5);
        switch(a)

        {

        case 0:
             tell_object(poisonee,"one.\n");

        case 1:
             tell_object(poisonee,"two.\n");


        case 2:
             tell_object(poisonee,"three.\n");
             break;

        case 3:
             tell_object(poisonee,"four.\n");

        case 4:
      
             tell_object(poisonee,"five.\n");
        }
     }
    
     else if(num<21)
     {
        int a = random(5);
        switch(a)

        {

        case 0:
             tell_object(poisonee,"one.\n");

        case 1:
             tell_object(poisonee,"two.\n");


        case 2:
             tell_object(poisonee,"three.\n");
             break;

        case 3:
             tell_object(poisonee,"four.\n");

        case 4:

             tell_object(poisonee,"five.\n");
        }
     }
     
     else
     {
        int a = random(5);
        switch(a)

        {

        case 0:
             tell_object(poisonee,"one.\n");

        case 1:
             tell_object(poisonee,"two.\n");


        case 2:
             tell_object(poisonee,"three.\n");
             break;

        case 3:
             tell_object(poisonee,"four.\n");

        case 4:

             tell_object(poisonee,"five.\n");
        }
     }

     num++;
}
