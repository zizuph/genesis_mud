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
    set_name("pig");
    add_adj("pink");
    add_adj("dirty");
    set_race_name("pig");
    set_short("dirty pink pig");
    set_long("This is a little pink pig that looks like its been "+
    "in the mud. It sniffs the air, and rolls around in the dirt.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_gender(random(2));
    set_stats(({20,20,20,3,3,20}));
    set_act_time(4);
    add_act("emote goes oink!");
    add_act("emote squeels.");
    add_act("emote snorts.");
    add_act("emote sniffs the air.");
    add_act("emote rolls in the mud.");
    add_act("say oink!");
    set_hitloc_unarmed(0,20,100,"body");
    set_attack_unarmed(0,20,30,W_BLUDGEON,60,"back feet");
    set_attack_unarmed(1,20,25,W_BLUDGEON,20,"teeth");
    set_attack_unarmed(2,20,30,W_BLUDGEON,20,"front feet");
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

