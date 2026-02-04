/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * body_guard.c
 *
 * A body guard for Charlie the chisel salesman
 *
 * Sorgum
 *
 * Modification Log:
 *   Added clone_unique code per AoB's request  -- Tomas April 2000
 *
   Modified by Udana:
    he is now a member of a caravan
*/
 


#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"
inherit STDMONSTER;
inherit "/lib/unique";
inherit NPC + "caravan_member.c";

#include <options.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>

#include <ss_types.h>
#include <money.h>
#define KILL_LOG SILVER_DIR+"log/bg_kills"

void dress_me();
int drink_all();


/* sets unarmed combat off, giving more sword attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}



/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    
    set_name("buddy");
    set_adj("strong");
    set_race_name("dwarf"); 
    set_long("This is the salesmans bodyguard. He seems to be a " +
             "very capable at what he does. You probably shouldn't " +
             "mess with him or his employer.\n");
  
    set_stats(({220, 220, 220, 60, 50, 180}));

    SET_MAX_HP;
  
    set_skill(SS_UNARM_COMBAT, 0);
    set_skill(SS_WEP_AXE,     100);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_AWARENESS,    70);
    set_skill(SS_2H_COMBAT,   100);
    set_skill(SS_BLIND_COMBAT,100);
    set_all_hitloc_unarmed(30);
  
    PASSIVE;
    set_attack_chance(0);
  
    set_cchat_time(3);
    add_cchat("This is fun!");
    add_cchat("I love my work!");
    add_cchat("Well didn't we do a big mistake!");
    add_prop(LIVE_I_SEE_DARK,3);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
  
    add_prop(CONT_I_WEIGHT, 90000);   /* 90 Kg  */
    add_prop(CONT_I_VOLUME, 90000);   /* 90 Ltr */
    add_prop(CONT_I_MAX_WEIGHT, 190000);   /* 190 Kg  */
    add_prop(CONT_I_MAX_VOLUME, 190000);   /* 190 Ltr */
    dress_me();
}

/* Two functions implemented for caravan member, by Udana */
void create_caravan_member()
{
  remove_prop(LIVE_I_NEVERKNOWN);
  set_aggressive(0);
  /* something out of range for native caravan members */
  type = 4;
  /* unexisting colour */
  set_colour("_chisel_man_colour");
}

public void help_friend(object enemy, object victim)
{
  /* He only changes target for his own wagonmates, no point at attacking the same guy again. */
  if(query_attack())
    if(query_attack() == enemy || victim->query_colour() != colour ||
	    (query_attack()->query_attack() && query_attack()->query_attack()->query_colour() == colour))
    {
	if(member_array(enemy, query_enemy(-1)) == -1)
	{
		object tmp = query_attack();
		attack_object(enemy);
		attack_object(tmp);
	}
	return;
    }
  if(!present(enemy, E(TO)))
  {
    command("smirk");
    return;
  }
  /* Just assisting */
  remove_prop(LIVE_S_EXTRA_SHORT);
  attack_object(enemy);
  enemy->catch_msg(QCTNAME(TO) + " attacks you!\n");
  tell_room(E(TO), QCTNAME(TO) + " attacks " + QTNAME(enemy) + "!\n", enemy);
  SEND(file_name(TO) + " " + QCTNAME(TO));
}

/* No changes after this line - Udana */

void dress_me()
{
    seteuid(getuid(this_object()));



    switch(random(2)) 
   {
        case 0 :   clone_unique(WEAPON + "dwarf_axe",7,
                      WEAPON + "battleaxe")->move(TO);
                   command("wield axe");  
                  break;
        case 1 :   clone_unique(WEAPON + "mbattleaxe",7,
                      WEAPON + "battleaxe")->move(TO);
                   command("wield axe"); 
                  break;
    }
    clone_object(OBJ+"dwarven_whiskey")->move(TO);
    clone_object(OBJ+"dwarven_whiskey")->move(TO);
    clone_object(OBJ+"dwarven_whiskey")->move(TO);
    clone_object(ARMOUR+"dwarf_plate")->move(TO);
    clone_object(ARMOUR+"dwarf_shield")->move(TO);
    command("wear all");
}

public int
query_knight_prestige()
{
    return 2;
}



void
attacked_by(object ob) {
  ::attacked_by(ob);
  set_alarm(1.0, 0.0, drink_all);
}


int
drink_all() 
{
   if(!present("whiskey", TO))
   {
      return 0;
   }
else
   {
      command("say Ahh, I hope you can fight, otherwise, dont " +
         "waste my time!");
      command("drink all");
      command("emote belches loudly.");
      return 1;
   }
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


int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, *enemies;
    int intox,hurt, i, goblinz;
    goblinz = 0;

    intox = enemy->query_intoxicated();
    if(enemy->query_race() == "goblin")
    {
        goblinz = 50;
    }

    me = TO;

    if(random(10) > 8) 
    {
        hurt = F_PENMOD(80  + goblinz + (intox / 3), 80 + goblinz + (intox / 3));

        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        tell_watcher(QCTNAME(me) + " charges into " + QCTNAME(enemy) + ".\n",
                             enemy);
        enemy->catch_tell(query_The_name(enemy) + " charges into you!\n" +
            "You feel " + how + ".\n");

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(me);
        }
        enemies = query_my_enemies();
        for (i=0; i<sizeof(enemies); i++)
        {
            if(enemies[i]->query_race_name() == "goblin")
                command("kill "+enemies[i]->query_real_name());
        }

        return 1;
    }


    return 0;
}


