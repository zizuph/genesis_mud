/*
* /d/Gondor/common/npc/rabbit.c
* an animal for the plains of Rohan
* attack and hitloc id's copied from Zephram,
* idea and code for making the corpse edible from Glindor
*
* Olorin              feb 1993
*
*Taken for the Shire, and fixed up the alignment problem ;) Elix Jan 95
  */

#pragma save_binary
inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/lib/goodkill.h"
#include "/d/Shire/sys/defs.h"
#include "defs.h"


/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_LHPAW 3
#define A_RHPAW 4

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

create_creature()
{
  if (!IS_CLONE) return;
  set_name("rabbit");
  add_name("animal");
  add_name("creature");
  add_name("buck");
  set_short("small brown rabbit");
  set_long("A small brown rabbit with large eyes and long ears, looking quite harmless. \n");
  set_adj(({"small","brown"}));
  set_race_name("rabbit");
set_alignment(75-random(50));
  set_stats(({7+random(8),10+random(6),5+random(5),5+random(5),5+random(10),1+random(5)}));
  set_hp(5000);
  set_gender(random(2));
  set_skill(SS_UNARM_COMBAT,20+random(10));
  set_skill(SS_DEFENCE,20+random(10));
  set_skill(SS_SWIM,40+random(20));
  set_whimpy(50);
  set_random_move(5);
  add_prop(CONT_I_WEIGHT,4500+random(2500));
  add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
  add_prop(LIVE_I_NO_CORPSE,1);
  seq_new("do_first");
  seq_addfirst("do_first",({"@@arm_me","stare","emote nibbles at the grass."}));
}

arm_me()
{
  seteuid(getuid(TO));
  set_m_out("hops");
  set_m_in("hops into view.");
}

/*
 * Here we add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */
public void
cr_configure()
{
    add_attack(5+random(5),5+random(5),W_IMPALE,30,A_BITE);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_LPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_RPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_LHPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_RHPAW);

    add_hitloc(({5+random(5),5+random(5),5+random(5)}),20,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),50,"body",H_BODY);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"legs",H_LEGS);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    case A_LPAW:return "left paw";
    case A_RPAW:return "right paw";
    case A_LHPAW:return "left hind paw";
    case A_RHPAW:return "right hind paw";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}

do_die(object killer)
{
    object corpse;
    if (query_hp() > 0) return;

    corpse = clone_object(OLD_FOR_DIR+"rabbit_corpse");
    corpse->add_prop(OBJ_I_WEIGHT,TO->query_prop(OBJ_I_WEIGHT));
    corpse->add_prop(CONT_I_WEIGHT,TO->query_prop(CONT_I_WEIGHT));
    corpse->add_prop(OBJ_I_VOLUME,TO->query_prop(OBJ_I_VOLUME));
    corpse->add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_VOLUME));
    corpse->move(environment(TO));

    ::do_die(killer);
}
void
attacked_by(object ob)
{
    ::attacked_by(ob);
    stop_fight(ob);
    ob->stop_fight(TO);
    run_away();
}
