inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

void create_hero() { }
   
void create_monster()
{
  create_hero();

  set_race_name("ghost");
  
  set_skill(SS_BLIND_COMBAT, 100);

  add_prop(LIVE_I_NO_CORPSE, 1);
  add_prop(MAGIC_I_RES_FIRE, 100);
  add_prop(MAGIC_I_RES_COLD, 100);
  add_prop(MAGIC_I_RES_ELECTRICITY, 100);
  add_prop(MAGIC_I_RES_LIGHT, 100);
  add_prop(MAGIC_I_RES_POISON, 100);
  add_prop(MAGIC_I_RES_EARTH, 100);
  add_prop(MAGIC_I_RES_AIR, 100);
  add_prop(MAGIC_I_RES_WATER, 100);
  add_prop(MAGIC_I_RES_IDENTIFY, 15);
  add_prop(MAGIC_I_RES_MAGIC, 50);
  add_prop(MAGIC_I_RES_DEATH, 100); // They're dead already!
  add_prop(LIVE_I_QUICKNESS, 100);
  add_prop(LIVE_I_SEE_DARK, 99);
  add_prop(LIVE_I_SEE_INVIS, 99);
  add_prop(LIVE_I_UNDEAD, query_average_stat() * 2 / 3);
}

void set_combat_skills(int level)
{
  int i;

  set_skill(SS_PARRY, level);
  set_skill(SS_DEFENCE, level);

  for (i = 0; i < 7; i++)
  {
    set_skill(i, level);
  }
}

void attacked_by(object ob)
{
  ::attacked_by(ob);
  add_prop(LIVE_O_ENEMY_CLING, ob);
}  

#ifndef THIS_IS_BUGGY
mixed hit_me(int wcpen, int dt, object attacker, int attack_id)
{
  object wep = attacker->query_weapon(attack_id);
  int *hitlocs, i, j, ran;

  if (wep && !wep->query_prop(OBJ_I_IS_MAGIC_WEAPON))
  {  
    ran = random(100);
    hitlocs = query_combat_object()->query_hitloc_id();
    for (i = sizeof(hitlocs); i--;)
    {
      if ((j += query_combat_object()->query_hitloc(hitlocs[i])) > ran)
      {      
        break;
      }
    }

    i = MAX(0, i);

    query_combat_object()->cb_got_hit(hitlocs[i], -1, attacker, attack_id,
        dt, 0);

    return ({ -1, hitlocs[i], 0, 0 });
  }

  return ::hit_me(wcpen, dt, attacker, attack_id);
}
#endif

/*
void init_living()
{
  ::init_living();

  if (member_array(this_player(), people_to_attack) >= 0 &&
      )
  {
*/  
