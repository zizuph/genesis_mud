inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Shire/common/armour/recover"

object wearer;
int alarm_id;

create_armour()
{
    set_name("fullplate");
    add_name("plate");
    set_pname(({"fullplates","plates"}));
    set_adj("blackened");
    set_short("blackened fullplate");
    set_pshort("blackened fullplates");
    set_long(
    	"This is a " + short() + ". It was forged of black steel and " +
        "looks very durable. The armour looks banged up, as if it was " +
        "in numerous battles, but still appears to be able to protect " +
        "your body.\n");
    	
    set_ac(35);
    set_at( A_TORSO | A_ARMS | A_LEGS);
    set_am(({ -1, 2, -1 }));
    set_af(TO);
    set_keep();
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(40,A_TORSO) + 4000 + random(3000));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40) + 1200 - random(600));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
/*    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" })); 
    add_prop(MAGIC_AM_ID_INFO, 
    	({
    	    
*/    

}
        
wear(object to)
{
    wearer = TP;
    write("The fullplate tightens it grip on you, forming after your body as you wear it.\n");        
    say("The fullplate tightens it grip on "+QTNAME(wearer)+"'s body when "+HE_SHE(wearer)+" wears it.\n");
    
     alarm_id = set_alarm(50.0,0.0,"align_fall");
    return 1;
}

remove(object to)
{
    remove_alarm(alarm_id);
   write("You remove the fullplate.\n");
   say(QCTNAME(TP)+ " removes the fullplate.\n");
    return 1;
}

int
align_fall()
{
    wearer = TP;
    if(!wearer->query_npc())
    {
     if(TP->query_alignment() >= -1000)
     {
        write("You feel something evil radiate from the fullplate.\n");
        say(QCTNAME(wearer) + " all of a sudden gets a funny look in his face....\n");
        wearer->set_alignment(wearer->query_alignment()-10);
        return 1;
     }
    }
    else
    return 0;
}   
