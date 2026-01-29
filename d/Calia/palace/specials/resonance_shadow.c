
/* 
   Resonance shadow for wolfhelms.

   Coded by Maniac 2/1/96.

   Made more efficient 29/1/97, Maniac
*/

inherit "/std/shadow";

string *my_adjs; 

void
remove_resonance_shadow()
{
    remove_shadow();
}

string
race_sound()
{
    return "resonates";
}

string
actor_race_sound()
{
    return "resonate";
}


varargs mixed
query_adj(int arg)
{
    if (!arg)
        return "wolf-headed";
    else 
        return my_adjs; 
}

void
setup_adjs()
{
    mixed ma; 

    ma = shadow_who->query_adj(1); 
    if (!pointerp(ma)) 
        ma = ({ }); 

    my_adjs = (({ "wolf-headed" }) + ma); 
}

public varargs int
shadow_me(mixed to_shadow)
{
    ::shadow_me(to_shadow); 
    setup_adjs();      
}

int
adjectiv_id(string str)
{
    return (member_array(str, query_adj(1)) >= 0);
}

string *
parse_command_adjectiv_id_list()
{
    return query_adj(1);
}

