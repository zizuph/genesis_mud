inherit "/d/Ansalon/std/creature.c";
inherit "/std/act/action.c";
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <wa_types.h>

/* Sarr */

object Aowner;


string
check_estring(object ob)
{
    int i;
    string str1,*str;
    str1 = ob->query_m_out();
    str = explode(str1," ");
    for(i=0;i<sizeof(str);i++)
    {
        str[i] = "'"+str[i]+"'";
    }
    str1 = implode(str," ");
    return str1;
}


int
set_owner(object ob)
{
    if(!ob)
        return 0;
    trig_new("%s "+check_estring(ob)+" %w","react_leave");
    Aowner = ob;
    return 1;
}

object
query_owner()
{
    return Aowner;
}

void
create_creature()
{
    ::create_creature();
    set_name("cat");
    add_adj("cute");
    add_adj("fuzzy");
    set_race_name("cat");
    set_short("cute fuzzy cat");
    set_long("This is a cute little adorable cat! It looks so happy and "+
    "playful. Its soft white fur feels so good to stroke.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_stats(({20,20,20,3,3,20}));
    set_act_time(4);
    add_act("purr");
    add_act("nuzzle all");
    add_act("curl all");
    add_act("meow");
    add_act("emote meows.");
    add_act("snuggle all");
    set_hitloc_unarmed(0,20,100,"body");
    set_attack_unarmed(0,20,30,W_BLUDGEON,40,"front paws");
    set_attack_unarmed(1,20,25,W_BLUDGEON,40,"tiny teeth");
    set_attack_unarmed(2,20,30,W_BLUDGEON,20,"back paws");
}
    
void
react_leave(string name, string dir)
{
    object tone;
    tone = find_player(lower_case(name));
    if(!tone)
    {
        return;
    }
    if(query_owner() == tone)
    {
        dir = extract(dir,0,-3);
        set_alarm(0.5,0.0,&command(dir));
        return;
    }
}

