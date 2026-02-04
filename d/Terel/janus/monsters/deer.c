 /* deer.c */
 /* janus 920701 */
 
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_creature()
{
  int alig;
  if (!IS_CLONE) return;
  alig=random(60);
  set_name(({"deer"}));
  set_short("brown deer");
  set_long(break_string("Animals of this species where hunted by the famous " +
      "Robbing Hood, both for its excellent meat and nice pelt. " + 
       "Usually these animals are very shy, not this one though. " + 
       "It is examining you carefully, maybe its the first time it " + 
       "sees a creature like you.\n",70)); 
  set_adj(({"brown","large"}));
  set_race_name("deer");
  set_alignment(alig);
  set_stats(({40,30,30,4,4,30}));
  set_aggressive(0);
  set_hp(1600);
  set_gender(random(2));
  set_act_time(21);
  add_act(({"sniff"}));
  set_skill(SS_DEFENCE,random(15));
  add_prop(OBJ_I_WEIGHT, 600000);
  add_prop(OBJ_I_VOLUME, 600000);
  add_prop(CONT_I_MAX_WEIGHT, 700000);
  add_prop(CONT_I_MAX_VOLUME, 700000);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me"}));
  set_whimpy(0);
}
  equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Terel/janus/other/deerskin") -> move(this_object());
  clone_object("/d/Terel/janus/other/meat") -> move(this_object());
  clone_object("/d/Terel/janus/other/meat") -> move(this_object());
  clone_object("/d/Terel/janus/other/meat") -> move(this_object());
  clone_object("/d/Terel/janus/other/meat") -> move(this_object());
  clone_object("/d/Terel/janus/other/meat") -> move(this_object());
  clone_object("/d/Terel/janus/other/meat") -> move(this_object());
}


#define A_BUTT  0
#define A_TRAM  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(40,40,W_BLUDGEON,75,A_BUTT);
    add_attack(35,35,W_BLUDGEON,25,A_TRAM);

    add_hitloc( ({ 7, 7, 7 }), 35, "head", H_HEAD);
    add_hitloc( ({ 6, 6, 6 }), 45, "body", H_BODY);
    add_hitloc( ({ 6, 6, 6 }), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BUTT:return "head butt";
    case A_TRAM:return "trample";
    }
}
