
/*   Coded by Bishop June 15th, 1999. Most of this was taken from
 *   Maniac's resonance shadow and Igneous' Disguise Shadow.   
 *
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include <living_desc.h>
#include <stdproperties.h>
#include <ss_types.h>

#define SW   shadow_who

string *my_adjs; 

public void setup_adjs();


void
remove_shadow()
{	
    destruct();
}

varargs mixed
query_adj(int arg)
{
    if (!arg)
        return "luminous";
    else 
        return my_adjs; 
}


public varargs string
long(mixed for_obj)
{
    if (!objectp(for_obj))
    for_obj = this_player();

    return (SW == for_obj ? "Your body radiates light of great strength," +
        " illuminating your surroundings." : capitalize(SW->query_pronoun()) +
        " is a blazing pillar of light, looking at " + SW->query_objective() +
        " hurts your eyes.") + "\n";
} 

public varargs int
shadow_me(mixed to_shadow)
{
    ::shadow_me(to_shadow); 
    setup_adjs();      
}

void
setup_adjs()
{
    mixed ma; 

    ma = shadow_who->query_adj(1); 
    if (!pointerp(ma)) 
        ma = ({ }); 

    my_adjs = (({ "luminous" }) + ma); 
}