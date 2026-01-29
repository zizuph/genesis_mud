inherit "/std/poison_effect";   
#include <poison_types.h>
#include <filter_funs.h>
#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"


/*
 * /d/Kalad/common/guilds/khiraa/lp/obj/disease.c
 * Purpose    : The poison for the lich spell 'black plague'
 * Located    : Lich spell 'black plague'.
 * Created By : Sarr 29.Mar.97
 * Modified By: 
 */



void
create_poison_effect()
{
     set_interval(20);
     set_damage( ({ POISON_FATIGUE,10, POISON_MANA, 20}) );
     set_poison_type("disease");
}

void
tell_damage_player(int phit, string str)
{
    switch(random(4))
    {
        case 0:
        tell_object(E(TO),"You feel very sick and mentally tired.\n");
        break;
        case 1:
        tell_object(E(TO),"You feel violent tugs in your stomach.\n");
        break;
        case 2:
        tell_object(E(TO),"You begin to break into a heavy sweat.\n");
        default:
        tell_object(E(TO),"Your begin to itch everywhere.\n");
    }
}
