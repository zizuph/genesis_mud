inherit "/d/Terel/std/monster";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include <language.h>

#define TO   this_object()
#define TP   this_player()
#define ETO  environment(TO)
#define ETP  environment(TP)

public string
random_weapon()
{
   switch (random(3))
   {
      case 0: return "knife";
      case 1: return "club";
      case 2: return "spear";
   }
}

public string
face()
{
   string *faces = ({"small", "black-horned", "savage", "impish",
                     "repulsive", "dingy", "lurid", "ghastly",
                     "putrid"});

   return faces[random(sizeof(faces))];
}

public void
get_weapon()
{
   object w;
   
   seteuid(getuid());
   
   w = clone_object("/d/Terel/common/swamp/" + random_weapon());
   w->move(TO);
   command("wield weapon");
}

public void
create_monster()
{
   int s = 10 + random(10);
   
   set_race_name("kobold");
   set_name("kobold");
   set_adj(face());
   set_long("These savage little creatures are repulsive, their " +
            "scaly rusty brown skin and hairless bodies coated with " +
            "swamp grime. They have reddish eyes and are topped by a " +
            "small pair of horns. They have dog-like faces.\n");

   set_base_stat(SS_STR, s + random(5));
   set_base_stat(SS_DEX, s + random(10));
   set_base_stat(SS_CON, s + random(10));
   set_base_stat(SS_INT, 3 + random(s));
   set_base_stat(SS_WIS, 3 + random(s));
   set_base_stat(SS_DIS, 10 + random(s));
   
   set_gender(1);
   set_aggressive(1);
   set_random_move(10 + 3*s);
   set_attack_chance(13);
   set_alignment(-20 - random(81));

   set_skill(SS_PARRY, s);
   set_skill(SS_DEFENCE, s);
   set_skill(SS_WEP_POLEARM, 15);
   set_skill(SS_WEP_SWORD, 40);
   set_skill(SS_WEP_KNIFE, 20);
   set_skill(SS_WEP_CLUB, 15);

   set_all_hitloc_unarmed(12);

   MONEY_MAKE_CC(1 + random(5))->move(TO);
   set_alarm(itof(4 + random(5)), -1.0, get_weapon);
}
