inherit "/d/Ansalon/std/creature.c";
inherit "/std/act/action.c";
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <wa_types.h>

/* Sarr */

object Aowner;

string
check_estring(object ob, int x)
{
    int i;
    string str1,*str;
    if(x == 0)
        str1 = ob->query_m_out();
    else
        str1 = ob->query_mm_out();
    str = explode(str1," ");
    for(i=0;i<sizeof(str);i++)
    {
        if(x != 0 && i == sizeof(str)-1)
            str[i] = "'"+str[i]+"\n'";
        else
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
    trig_new("%s "+check_estring(ob,0)+" %w","react_leave");
    trig_new("%s "+check_estring(ob,1),"react_trans");
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
    set_name("cow");
    add_adj("brown");
    set_race_name("cow");
    add_adj("spotted");
    set_short("brown spotted cow");
    set_long("A large, brown spotted cow stands here, with a "+
    "bell on its neck. It looks like it is confused as to what "+
    "its doing here.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_gender(1);
    set_stats(({20,20,20,3,3,20}));
    set_act_time(4);
    add_act("emote goes moooo!");
    add_act("emote nudges you.");
    add_act("emote chews on some grass.");
    add_act("fart");
    add_act("emote rattles its bell.");
    add_act("say mooo!");
    set_hitloc_unarmed(0,20,80,"body");
    set_hitloc_unarmed(1,20,20,"head");
    set_attack_unarmed(0,20,30,W_BLUDGEON,60,"back feet");
    set_attack_unarmed(1,20,25,W_BLUDGEON,20,"horned head");
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
void
react_trans(string name, string dir)
{
    object tone;
    tone = find_player(lower_case(name));
    if(!tone)
    {
        return;
    }
    if(query_owner() == tone)
    {
        set_alarm(0.5,0.0,"trans_me",tone);
        return;
    }
}

trans_me(object ob)
{
    object dest;
    dest = E(ob);
    move_living("dissapears in a puff of smoke.",dest);
}

void
do_die(object ob)
{
    seteuid(getuid());
    clone_object("/d/Ansalon/taman_busuk/neraka/obj/beef.c")->move(TO);
    ::do_die(ob);
}

