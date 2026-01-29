inherit "/std/shadow";
 
#include "/d/Rhovanion/defs.h"
#include "spguild.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
 
#define OWNER query_shadow_who()
 
void msg( string what )
{
    object ob;
 
    ob = find_player( "paladin" );
    ob->catch_msg( what );
}
 
static void
tell_watcher(string str, object me, object enemy)
{
    object *ob;
    int i;
 
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
int spshadow_exist()
{
    return 1;
}
 
/* void heal_hp(int amount) */
/* { */
/*     OWNER->catch_msg("heal_hp()\n"); */
/*     OWNER->heal_hp(amount); */
/* } */
 
int query_ghost()
{
    object enemy,spider;
    int skill;
    int time;
 
    enemy=OWNER->query_attack();
    if (enemy)
        if (!OWNER->query_prop(ATTACK))
            if (OWNER->query_prop(MOUNTED))
              {
                skill=OWNER->query_skill(SPIDER_FIGHT_SKILL);
                time=random(60-skill/2)+4;
                set_alarm(itof(time),0.0,"spider_attack");
                OWNER->add_prop(ATTACK,time);
              }
    return OWNER->query_ghost();
}
 
string query_m_in()
{
    if (OWNER->query_prop(MOUNTED))
        return "arrives riding huge black spider.";
    return OWNER->query_m_in();
}
 
string query_m_out()
{
    if (OWNER->query_prop(MOUNTED))
        return "leaves riding huge black spider to the";
    return OWNER->query_m_out();
}
 
int install(object whom)
{
    ::shadow_me(whom);
}
 
int spider_attack()
{
    int damage,pen,str,dex,con,wis;
    mixed dmg;
    object enemy,spider;
    string res,dres;
 
    OWNER->remove_prop(ATTACK);
    enemy=OWNER->query_attack();
    if (OWNER->query_prop(MOUNTED)&&enemy)
      {
        spider=OWNER->query_prop(SPIDER);
        str=spider->query_stat(SS_STR);
        dex=spider->query_stat(SS_DEX);
        wis=spider->query_stat(SS_WIS);
        pen=str/3+dex/5+wis/7;
        dmg=enemy->hit_me(pen,W_BLUDGEON,OWNER,-1);
        damage=dmg[0];
        res=", but misses completely and runs past ";
        dres=".";
        if (damage>0)
            res=", but only tickles ";
        if (damage>2)
            res=" and grazes ";
        if (damage>5)
            res=" and hurts ";
        if (damage>11)
          {
            res=" and hurts ";
            dres=" rather bad.";
          }
        if (damage>15)
          {
            res=" and hurts ";
            dres=" very bad.";
          }
        if (damage>20)
          {
            res=" and smashes ";
            dres=" very hard!";
          }
        if (damage>30)
          {
            res=" and smashes ";
            dres=" with a bone crushing sound!";
          }
        if (damage>50)
          {
            res=" and nearly DESTROYES ";
            dres=" with a deadly hit!!!";
          }
        if (damage>99)
          {
            res=" and completely DESTROYES ";
            dres=" with a final hit!!!";
          }
        OWNER->catch_msg("Your spider comes running at your enemy, "+
                         "trying to dealt a heavy blow"+res+
                         QTNAME(enemy)+dres+"\n");
        enemy->catch_msg(QCTNAME(OWNER)+"'s spider comes running at "+
                         "you, trying to dealt a heavy blow"+res+
                         "you"+dres+"\n");
        tell_watcher(QCTNAME(OWNER)+"'s spider comes running at "+
                     QTNAME(enemy)+", trying to dealt a heavy blow"+res+
                     HIM(enemy)+dres+"\n",OWNER,enemy);
        if (damage>99)
            enemy->do_die(OWNER);
      }
}
