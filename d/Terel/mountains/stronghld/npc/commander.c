/*
 * Dolgarth, Commander of Stronghold
 * Tomas  -- Jan 2000
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <options.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>

#define KILL_LOG "/d/Terel/log/dolgarth_kills"
#define ARM_DIR  MOUNTAIN_DIR + "stronghld/armour/"
#define WEP_DIR  MOUNTAIN_DIR + "stronghld/weapon/"
#define UNARMED_OFF         7



void dress_me();
int berzerked = 0;


/* sets unarmed combat off, giving more sword attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}


public void
create_monster()
{
    set_name("dolgarth");
    add_name("commander");
    set_living_name("dolgarth");
    set_adj(({"massive","stern"}));
    set_race_name("dwarf");
    set_title("Commander of the dwarven forces at Stonehold");
    set_long("This dwarf doesn't look like he should be trifled with.\n");

    set_stats(({200, 160, 200, 160, 160, 180}));
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_UNARM_COMBAT, 80);
    set_alignment(1200);

    set_cchat_time(3);
    add_cchat("By Mahal! You shall pay dearly for your stupid mistake!");
    add_cchat("Foul one.. DIE!");
    add_cchat("Surely, you do not have any thoughts of leaving in " +
        "one piece!");
    add_cchat("Any last requests?");
    add_cchat("Tired of living I see.. Very well, i'll help you along.");

    set_act_time(3);
    add_act("glances at a map.\n");
    add_act("caresses his shin thoughfully.\n");

    trig_new("%s 'attacks' 'you!\n' %s","react_attacked");

    set_alarm(1.0, 0.0, dress_me);

}


public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(1) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}



/* Get some equipment */
void
dress_me()
{
    FIX_EUID;
    clone_object(ARM_DIR + "commander_scalemail")->move(TO);
    clone_object(ARM_DIR + "dwarf_robe")->move(TO);
    clone_object(ARM_DIR + "dwarf_boots")->move(TO);    
    clone_object(ARM_DIR + "dwarf_helmet")->move(TO);  
    clone_object(ARM_DIR + "mithril_bracers")->move(TO);  
    clone_object(WEP_DIR + "warhammer")->move(TO);

    command("wield all");
    command("wear all");
}

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) {
       if (enemies[i] != killer)
           str += ", " + enemies[i]->query_name() +
           "[" + enemies[i]->query_average_stat() + "]";
      }
    write_file(KILL_LOG, str + " (" + ctime(time()) + ")\n");
    
    ::do_die(killer);
}


react_attacked(s,ss)
{
  set_alarmv(1.0, 5.0, "att",({TP}));
  return 1;

}


att(s,ss)
{
  int qryhp;

  qryhp = (TO->query_max_hp() / 2);

  if(berzerked == 1)
  return 0;

  if(TO->query_hp() <= qryhp)
  {
   set_alarm(1.0, 0.0, "go_berzerk",({TP}));
   return 1;
  }
   return 0; 
}


public void
go_berzerk()
{
    int base_stat;
    int i;
    berzerked = 1;

    for (i = 0; i < 6; i++)
        set_base_stat(i, query_stat(i) + random(30));

    set_hp(query_max_hp());
    set_fatigue(query_max_fatigue());
    add_prop(LIVE_I_QUICKNESS, 50 + random(50)); 
 
    
    command("emote mumbles something under his breath.");
    tell_room(environment(TO), "The commanders eyes glow a second " +
       "as he continues to mumble what sounds like a prayer.\n");
    command("emote roars showing renewed strength as he throws " +
            "himself into battle!");

}

// The following code is from the Shire/misty/gcave_lord.c 
// Many thanks to Jaypeg!
void
check_my_weapon() 
{
    if (!query_skill(SS_UNARM_COMBAT) && !sizeof(query_weapon(-1)))
    {
        set_skill(SS_UNARM_COMBAT, 94);
        map(query_combat_object()->query_attack_id(), cr_reset_attack);
    }
    else
    if (query_skill(SS_UNARM_COMBAT))
    {
        remove_skill(SS_UNARM_COMBAT);
        map(query_combat_object()->query_attack_id(), cr_reset_attack);
        map(query_weapon(-1), update_weapon);
    }
}


    
int
find_valid_enemy(object foe)
{
    if (ENV(foe) != ENV(TO))   
        return 0;
    if (!sizeof(foe->query_weapon(-1)))
        return 0;

    // Passed all checks.    
    return 1;
}


int
special_attack(object ob)
{
    object *foes, *weapons, *my_weapons, weapon;

    check_my_weapon();

    if (random(7))
        return 0;
    my_weapons = query_weapon(-1);
    weapons = ob->query_weapon(-1);

    // If I have no weapon wielded I can't do this attack.
    if (!sizeof(my_weapons))
    {
        // Posibily do an unarmed attack here?
        return 0;
    }

    // My enemy has no weapon so lets look for another :)
    if (!sizeof(weapons))
    {
        if (!sizeof(foes = filter(query_enemy(-1), find_valid_enemy)))
            return 0;
        ob = foes[random(sizeof(foes))];
        weapons = ob->query_weapon(-1);
    }

    // Sanity check
    if (!sizeof(weapons))
        return 0;
    // What weapon are we attacking.
    weapon = weapons[random(sizeof(weapons))];

    // Do we hit with this attack?
    if (query_combat_object()->cb_tohit(-1,100,ob) >= 0)
    {
        if (!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
        {
            // See if we are able to break non-magical weapons.
            if (resolve_task(TASK_DIFFICULT, ({TS_DEX, SS_WEP_POLEARM}), ob,
                ({SKILL_AVG, TS_DEX, TS_WIS, SKILL_END, SS_PARRY})) >= 0)
            {
                ob->catch_tell("The "+query_nonmet_name()+" strikes your "+
                  weapon->short()+" with "+POSSESSIVE(TO)+" "+
                  my_weapons[0]->short()+" with tremendous force damaging "+
                  "your "+weapon->short()+" beyond repair.\n");
                tell_room(ENV(TO), QCTNAME(TO) + " strikes "+QCTNAME(ob)+
                  "'s "+weapon->short()+" with "+POSSESSIVE(TO)+" "+
                  my_weapons[0]->short()+" with tremendous force damaging "+
                  QCTNAME(ob)+"'s "+weapon->short()+" beyond repair.\n", 
                  ({TO,ob}));
                weapon->remove_broken();
                return 1;
            }
        }
        ob->catch_tell("The "+query_nonmet_name()+" strikes your "+
          weapon->short()+" with "+POSSESSIVE(TO)+" "+
          my_weapons[0]->short()+" leaving your "+weapon->short()+
          " somewhat damaged from the blow.\n");
        tell_room(ENV(TO), QCTNAME(TO) + " strikes "+QCTNAME(ob)+
          "'s "+weapon->short()+" with "+POSSESSIVE(TO)+" "+
          my_weapons[0]->short()+" leaving "+QCTNAME(ob)+"'s "+
          weapon->short()+" somewhat damaged by the blow.\n",({TO,ob}));
        // The weapon condition gets worse by 1-2 levels.
        weapon->set_dull(weapon->query_dull() + random(2) + 1); 
        return 1;
    }
    else
    {
        // Damn we missed so nothing bad happens.. but lets let people
        // know we tried to do something.
        ob->catch_tell("The "+query_nonmet_name()+" trys to hammer "+
          "your "+weapon->short()+" with "+POSSESSIVE(TO)+" "+
          my_weapons[0]->short()+", but you manage to deflect the blow.\n");
        tell_room(ENV(TO), QCTNAME(TO) + " attempts to smash "+QCTNAME(ob)+
          "'s "+weapon->short()+" with "+POSSESSIVE(TO)+" "+
          my_weapons[0]->short()+", but "+QCTNAME(ob)+" manages to "+
          "deflect the blow.\n",({TO,ob}));    
        return 1;
    }
    return 1;
}

    


