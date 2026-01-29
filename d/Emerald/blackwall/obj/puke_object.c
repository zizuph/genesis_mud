/* This object is passed to players who effectivly "poison" themselves 
   by drinking from the slimy pool in valley1_34. It auto-destructs
   after a set period of time, causing the player to throw up.

   Code (c) 1999 to Damian Horton (BKA Casimir)
*/

#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

//prototypes
void become_ill();

create_object()
{
    float destruct_time; //time until the object destructs

    destruct_time = itof(random(60 + random(600)));
    
    set_name("_valley34_puke_object");
    
    set_no_show(); //can't see this object, ever

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, "Sorry, no such luck.\n");
    add_prop(OBJ_I_NO_GIVE, "Give what to whom?\n");
//    add_prop(OBJ_M_NO_GET, "You don't want it!\n");

    set_alarm(destruct_time - 5.0, 0.0, become_ill);
    set_alarm(destruct_time, 0.0, remove_object);
}

// Just before the player pukes, this function prints some messages.
void
become_ill()
{
    environment()->catch_tell("You start to feel very "+
			      "sick to your stomach.\n");
    tell_room(environment(environment()), QCTNAME(environment()) +
	      "turns pale, " + environment()->query_possessive() +
	      "complexion taking on a distinctly greenish cast.\n",
	      environment(), environment());
}
/* This function is called when the object is removed.
   Removing this object prints messages and causes the player
   to "puke up" 1/2 his food, soft and alcohol.
*/

void
remove_object()
{
    environment()->catch_tell("You double over and puke out much of your "+
			      "most recent meal.\n");
    tell_room(environment(environment()), QCTNAME(environment()) + 
	      " doubles over in an undignified manner and pukes up "+
	      "mmuch of " + environment()->query_possessive() + " most "+
	      "recent meal.\n", environment(), environment());

    //player loses half his current food, water and alcohol
    
    environment()->drink_soft(- (environment()->query_soaked() / 2));
    environment()->eat_food(- (environment()->query_stuffed() / 2));
    environment()->drink_alco( - (environment()->query_intoxicated() /2));
    
    ::remove_object();
}






