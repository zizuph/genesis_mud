/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";
#include <wa_types.h>
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <ss_types.h>

#define TO               this_object()
#define TP               this_player()
#define ETO              environment(TO)
#define ETP              environment(TP)
#define MIN_DUR          20
#define MAX_DUR          1000
#define A_SPEAR          0
#define H_FORM           0

int aid, duration;

void set_duration(int t);

public string
query_mm_in()
{
    return "descends from a bright mist above.";
}

public string
query_mm_out()
{
    return "ascends into a bright mist above and is followed by " +
           "a gust of wind.";
}

public void
init_living()
{
   ::init_living();
   add_action("heal", "heal");
   add_action("defend", "defend");
}

public int
heal(string str)
{
   string spirit;

   if (!str) return 0;

   if (sscanf(str, "me %s", spirit) != 1) return 0;

   if (present(spirit, ETP) != TO) return 0;

   if (TO->query_prop("owner") != TP->query_name()) return 0;

   write("The angelic spirit says: Let the healing of light be upon you. " +
         "The angelic spirit lays its hands upon you.\n");
   say("The angelic spirit speaks some mystic words and places its hands "
       + "upon " + QTNAME(TP) + ". Suddenly " +
       TP->query_pronoun() + " is surrounded by a white aura.\n");
   TP->heal_hp(300 + TP->query_skill(SS_ELEMENT_LIFE));
   write("The angelic spirit says: I have done all I may do.\n");
   tell_room(ETO, "The angelic spirit departs upwards " +
             "in a flash of light, followed by a gust of wind.\n", TO);
   if (aid) remove_alarm(aid);
   remove_object();
   return 1;
}

public int
defend(string str)
{
   int i;
   object enemy=0, *enemies;
   string spirit;

   if (!str) return 0;

   if (sscanf(str, "me %s", spirit) != 1) return 0;

   if (present(spirit, ETP) != TO) return 0;

   if (TO->query_prop("owner") != TP->query_name()) return 0;
   
   if (query_attack()) {
       write("The angelic spirit says: I am already defending you!\n");
       return 1;
   }

   write("The angelic spirit says: I shall defend you.\n");
   enemies = TP->query_enemy(-1);
   for(i=0; i<sizeof(enemies); i++) {
       if (environment(enemies[i]) == ETP) {
           enemy = enemies[i];
           break;
       }
   }
   if (!enemy) {
      write("The angelic spirit says: You have summoned me in vain.\n");
      write("The angelic spirit says: I find no enemies of you.\n");
      return 1;
   }
   tell_room(ETO, "The angelic spirit glows with a bright light and attacks " +
             QTNAME(enemy) + "!\n", TO);
   TO->attack_object(enemy);
   enemy->attack_object(TO);
   return 1;
}

public void
create_creature()
{
   set_race_name("spirit");
   set_adj("angelic");
   set_name(({"holy spirit", "guardian", "angel", "spirit"}));

   set_long(
         "An ancient spirit, born from the ageless light. It has " +
         "somehow descended from the heavens. Clad in a silvery " +
         "breastplate and helm, this spirit is arrayed for battle. " +
         "It wears a long white cloak, in its left hand a shield " +
         "bearing the emblem of the star, its right hand holding " +
         "a long spear. Its face shines with light, its body strong " +
         "and proud. Its eyes glow bright blue, its hair silvery-" +
         "white. From its back protrude long thin wings.\n");

   set_base_stat(SS_STR, random(30) + 100);
   set_base_stat(SS_DEX, random(30) + 110);
   set_base_stat(SS_CON, random(30) + 150);
   set_base_stat(SS_INT, random(30) + 65);
   set_base_stat(SS_WIS, random(30) + 60);
   set_base_stat(SS_DIS, random(30) + 70);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_SPELLCRAFT, 80);
   set_skill(SS_ELEMENT_LIFE, 100);
   set_skill(SS_ELEMENT_AIR, 50);
   set_hp(9999);
   set_mana(9999);
   set_alignment(900);
   set_gender(2);

   set_attack_unarmed(A_SPEAR, 90, 80, W_IMPALE, 100, "holy spear");
   set_hitloc_unarmed(H_FORM, 80, 100, "luminous form");

   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
}

public string
wizinfo()
{
   string str;
   mixed *calls;
   int tl=-1;
   
   if (aid) {
       calls = get_alarm(aid);
       tl = ftoi(calls[2]);
   }

   str = "This angel is here at a mystic's calling, " +
         "it will be able to perform certain functions for the " +
         "player.\n";
   str += "Summoned by: " + TO->query_prop("owner") + "\n";
   str += "Time left:   " + tl + " (" + duration + ")\n";
   return str;
}

public void
destroy_spirit()
{
   aid = 0;
   tell_room(ETO, "The " + short() + " fades away.\n", TO);
   remove_object();
}

public void
set_duration(int t)
{
   if (t < MIN_DUR) t = MIN_DUR;
   if (t > MAX_DUR) t = MAX_DUR;
   duration = t;
   aid = set_alarm(itof(duration), -1.0, destroy_spirit);
}
