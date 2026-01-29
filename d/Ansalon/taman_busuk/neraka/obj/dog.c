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
    set_name("dog");
    add_adj("black");
    add_adj("furry");
    set_race_name("dog");
    set_short("black furry dog");
    set_long("This is a nice looking black-maned dog. The fur on it is "+
    "warm and fluffy. He barks happily.\n"+
    "He is wearing a black spiked collar.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_stats(({20,20,20,3,3,20}));
    set_act_time(4);
    add_act("emote barks happily.");
    add_act("emote wags his tail.");
    add_act("growl");
    add_act("emote sniffs the ground.");
    add_act("emote barks loudly.");
    add_act("emote pants.");
    set_hitloc_unarmed(0,20,99,"body");
    set_hitloc_unarmed(16384,20,1,"neck");
    set_attack_unarmed(0,20,30,W_BLUDGEON,40,"front paws");
    set_attack_unarmed(1,20,25,W_BLUDGEON,40,"jaws");
    set_attack_unarmed(2,20,30,W_BLUDGEON,20,"back paws");
    seteuid(getuid());
    clone_object(NOBJ+"collar")->move(TO);
    command("wear all");
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

