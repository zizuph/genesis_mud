#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"
#include <tasks.h>
#include <ss_types.h>

inherit "/std/object";
inherit SPELL_EFFECT_OBJECT;

#define REDUCED_TMP  "_reduced_tmp"

/* This is used for the spell 'hands of doom', a lich spell. */
/* It will slow a target down, reduce dex, and reduce chance of */
/* of escaping the room */
/* Sarr of Kalad, 8.Apr.97 */
/* Sarr, 2.Jun.98 recode */

int time; // duration

int power; // occ stat - resistance
int dex_pen = 10; // dex reduction
object enemy; // the hands' target

void
set_power(int i)
{
    power = i;
}

void
set_enemy(object me)
{
    enemy = me;
}

void
set_remove_time(int i)
{
    set_alarm(itof(i),0.0,"remove_object");
}


void
create_object()
{
    set_name("hands");
    add_adj(({"ethereal","skeletal"}));
    set_short("@@handshort@@");
    set_long("These are horrible, skeletal hands made of ethereal mist "+
    "that glows with a sickly yellow color.\n");
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GET,1);
}

string
handshort()
{
    if(TP == enemy)
        return "many ethereal hands floating in the ground-mist holding "+
        "onto you";
    if(!present(enemy,ENV(TO)))
        return "many etherlea hands floating in ground-mist";

    if(TP->query_met(enemy))
        return "many ethereal hands floating in the ground-mist holding "+
        enemy->query_name();
    return "many ethereal hands floating in the ground-mist holding "+
    enemy->query_nonmet_name();
}
    

void
set_up_reduction()
{
    int res;
    if(!objectp(enemy))
        return;

    if(TP != enemy)
        return;

    if(TP->query_prop(REDUCED_TMP))
        return;

    enemy->add_prop(REDUCED_TMP,1);

    enemy->set_stat_extra(SS_DEX,enemy->query_stat_extra(SS_DEX) - dex_pen);


    enemy->add_prop(LIVE_I_QUICKNESS,
         enemy->query_prop(LIVE_I_QUICKNESS) - power);
    enemy->query_combat_object()->cb_calc_speed();

    enemy->add_magic_effect(TO);
}

void
remove_reduction()
{
    if(!enemy->query_prop(REDUCED_TMP))
        return;

    enemy->set_stat_extra(SS_DEX,enemy->query_stat_extra(SS_DEX) + dex_pen);

    enemy->add_prop(LIVE_I_QUICKNESS,
           (enemy->query_prop(LIVE_I_QUICKNESS) + power ));

    enemy->remove_prop(REDUCED_TMP);

    enemy->query_combat_object()->cb_calc_speed();
    enemy->remove_magic_effect(TO);
}

void
remove_object()
{
    remove_reduction(); 
    tell_room(E(TO),"The hands waver slightly, and dissapear!\n");
    ::remove_object();
}


void
init()
{
    ::init();
    set_up_reduction();
    add_action("do_filter","",1);
}

int
do_filter(string str)
{
    int i;
    string *dircmds;
    if(!objectp(enemy))
        return 0;
    if(TP != enemy)
        return 0;
    dircmds = E(enemy)->query_exit_cmds();
    dircmds += ({"n","s","w","e","nw","ne","sw","se"});
    if(member_array(query_verb(),dircmds) != -1)
    {
        
        if(TP->resolve_task(TASK_DIFFICULT, ({TS_STR,TS_DEX}), 
           spell_caster, ({ TS_WIS, TS_INT }) ) > 0)
        {
            write("You break away from the horrible hands!\n");
            remove_reduction();
            return 0;
        }

        write("You try to leave, but you aren't able to break away "+
        "from the horrible hands!\n");
        say(QCTNAME(TP)+" tried to leave, but was not able to break "+
        "away from the horrible hands!\n");
        return 1;
    }
    return 0;
}

public void
start()
{
    set_enemy(spell_target);
}

public int
dispel_spell_effect(object ob)
{
    tell_object(ob,"You dispel the "+short()+" successfuly!\n");
    remove_object();
    return 1;
}
