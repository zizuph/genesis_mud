 /* sheep.c */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/macros.h"

create_creature()
{
  if (!IS_CLONE) return;
  set_name(({"animal","beast","sheep"}));
  set_short("wooly brown sheep");
  set_long("A wooly brown grazing sheep.\n");
  set_adj(({"wooly","brown","grazing"}));
  set_race_name("animal");
  set_alignment(random(300)-100);
  set_stats(({random(20)+10,random(12)+10,random(20)+20,random(5),random(10),random(5)+5}));
  /* set_aggressive(random(2)); */
  set_hp(random(500)+500);
  set_gender(random(2));
  set_skill(SS_CLIMB,random(25)+20);
  set_skill(SS_SWIM,random(20)+10);
  set_whimpy(1);
  set_random_move(random(30)+5);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me","grin"}));
}
equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Gondor/zephram/armour/wcoat") -> move(this_object());
  }


/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_BUTT 1
#define A_BFHOOF 2
#define A_BRHOOF 3
#define A_TRAMPLE 4

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

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
    add_attack(4,12,W_IMPALE,5,A_BITE);
    add_attack(20,15,W_BLUDGEON,40,A_BUTT);
    add_attack(15,8,W_BLUDGEON,25,A_BFHOOF);
    add_attack(12,12,W_BLUDGEON,20,A_BRHOOF);
    add_attack(12,20,W_BLUDGEON,10,A_TRAMPLE);

    add_hitloc( ({ 5, 7, 3 }), 10, "head", H_HEAD);
    add_hitloc( ({ 7, 12, 10 }), 70, "body", H_BODY);
    add_hitloc( ({ 20, 5, 7 }), 20, "legs", H_LEGS);
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
    case A_BUTT:return "head butt";
    case A_BFHOOF:return "front hooves";
    case A_BRHOOF:return "rear hooves";
    case A_TRAMPLE:return "trample";
    }
    return "mind"; /* should never occur */
}

