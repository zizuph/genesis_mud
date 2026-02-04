/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/object";

#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#define PATH   "/d/Terel/mecien/valley/guild/spells/"
#define TO     this_object()
#define TP     this_player()
#define ETO    environment(TO)
#define ENV    environment
#define SUBLOC "curse_subloc"

#define CURSES ({"A feeling of gloom overshadows you.\n",\
                 "You feel very miserable.\n",\
                 "Doom is thy companion.\n",\
                 "A horrifying dread wraps you in its undying fold.\n"})

public void rand_curse(object who);

int aid = 0;

public string
query_auto_load()
{
   return MASTER + ":";
}

public void
create_object()
{
   set_name("mystic_curse");
   add_name("curse");
   set_adj("mystic");
   set_short("mystic curse");

   set_no_show();

   add_prop(OBJ_M_NO_DROP, 1);
   add_prop(OBJ_M_NO_SELL, 1);
}

public void
add_curse(object who)
{
   who->add_subloc(SUBLOC, TO);
   aid = set_alarm(10.0, itof(200+random(100)), &rand_curse(who));
}

public void
enter_env(object dest, object old)
{
   ::enter_env(dest, old);
   if (living(dest)) add_curse(dest);
}

public void
leave_env(object from, object to)
{
   ::leave_env(from, to);
   
   if (living(from)) {
      from->remove_subloc(SUBLOC);
      if (aid) remove_alarm(aid);
      from->catch_msg("You feel as though a doom has been lifted from you.\n");
   }
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;

   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "You have the mark of a black star upon your forehead.\n";
   else
      str = capitalize(carrier->query_pronoun()) +
            " has the mark of a black star upon " +
            carrier->query_possessive() + " forehead.\n";
   return str;
}

public void
itch(object who)
{
   who->catch_msg("You begin to itch all over.\n");
   who->add_fatigue(-random(25));
   tell_room(ENV(who), QCTNAME(who) + " begins scratching " +
             who->query_possessive() + " body all over.\n", who);
}

public void
voices(object who)
{
    who->catch_msg("You feel very strange, as if haunted.\n");
    tell_room(ENV(who), "A ghostly image appears over " + QTNAME(who) +
              ".\nGhost howls: " + QCTNAME(who) + " is cursed! I must warn you "
             +"that you are in danger to be with " + who->query_objective() +
              "!\nThe ghostly image fades away.\n", who);
}

public void
torment(object who)
{
    tell_room(ENV(who), "A shadowy void opens above you.\n");
}

public void
pain(object who)
{
   who->command("$scream");
   who->catch_msg("A horrible pain bites deeply into your side.\n");
   tell_room(ENV(who), QCTNAME(who) + " is gripped with a horrid pain.\n",
             who);
   who->heal_hp(-(who->query_hp())/15);
}

public void
fear(object who)
{
   who->catch_msg("You feel you are about to die!\n");
   tell_room(ENV(who), QCTNAME(who) + " looks horrified!\n", who);
   who->add_panic(100);
   who->add_temp_stat(SS_DIS, -10, random(200));
}

public void
confuse(object who)
{
    switch(random(4) + 1)
    {
      case 4:
        who->command("$say I am most foul!"); break;
      case 3:
        who->command("$say I am cursed forever!"); break;
      case 2:
        who->command("$say My time has come, I must die for my iniquity"); break;
      case 1:
        who->command("$say I must repent of my evil and do homage unto the Ancients");
        break;
      default:
        break;
    }
}

public void
encumber(object who)
{
    who->catch_msg("You feel as if the entire world rests on " +
                   "your shoulders.\n");
}

public void
thirst(object who)
{
    who->catch_msg("You feel the urgent need to drink something.\n");
}

public void
hunger(object who)
{
    who->catch_msg("You feel an intense craving for food.\n");
}

public void
weaken(object who)
{
   who->catch_msg("A weariness drapes your body, you feel your strength " +
                  "being drawn away into the void.\n");
   tell_room(ENV(who), QCTNAME(who) + " shakes and trembles as a shadowy " +
             "power looms over " + who->query_objective() + ".\n", who);
   who->add_tmp_stat(SS_STR, -10, random(150));
}

public void
slow(object who)
{
   who->catch_msg("Some dark force takes hold of you. A weariness strikes " +
                  "your limbs, as if decaying and weakened.\n");
   tell_room(ENV(who), QCTNAME(who) + " staggers, as dark shapes seem to " +
             "take hold of " + who->query_objective() + ".\n", who);
   who->add_tmp_stat(SS_DEX, -10, random(200));
}

public void
drain(object who)
{
   who->catch_msg("A feeling of anxiety enfolds your body. You feel weary, " +
                  "your vitality drained away.\n");
   tell_room(ENV(who), QCTNAME(who) + " turns pale. A black cloud forming " +
             "about " + who->query_objective() + ".\n", who);
   who->add_tmp_stat(SS_CON, -10, random(200));
}

public void
stench(object who)
{
  who->catch_msg("You smell a foul odor.\n");
  tell_room(ENV(who), "A wretched stench emanates from " +
            QTNAME(who) + ", you feel sick.\n", who);
}

public void
dumb(object who)
{
  who->catch_msg("A darkness enters your mind, you feel shaken.\n");
  tell_room(ENV(who), "A shadowy image circles " + QTNAME(who) +
            " then enters into " + who->query_possessive() + " ear.\n",
            who);
  who->add_temp_stat(SS_WIS, -10, random(200));
  who->add_temp_stat(SS_INT, -10, random(200));
}

public void
fumble(object who)
{
  if (who->query_weapon(512)) {
      who->catch_msg("Your right arm become numb.\n");
      who->command("$drop weapon");
      return;
  }
  if (who->query_weapon(1024)) {
      who->catch_msg("Your left arm becomes numb.\n");
      who->command("$drop weapon");
      return;
  }
  if (who->query_weapon(1536)) {
      who->catch_msg("Your hands become numb.\n");
      who->command("$drop weapon");
      return;
  }
  who->catch_msg("You stumble.\n");
  tell_room(ENV(who), QCTNAME(who) + " stumbles.\n", who);
}

public void
rand_curse(object who)
{
   if (!who) return;
   
   who->catch_msg(CURSES[random(sizeof(CURSES))]);

   switch (random(100))
   {
      case 101..1000:
       torment(who); break;
      case 97..100:
       weaken(who); break;
      case 90..96:
       encumber(who); break;
      case 87..89:
       hunger(who); break;
      case 80..86:
       drain(who); break;
      case 74..79:
       dumb(who); break;
      case 70..73:
       thirst(who); break;
      case 67..69:
       slow(who); break;
      case 65..66:
       pain(who); break;
      case 60..64:
       voices(who); break;
      case 50..59:
       fear(who); break;
      case 40..49:
       confuse(who); break;
      case 30..39:
       dumb(who); break;
      case 20..29:
       fumble(who); break;
      case 12..19:
       stench(who); break;
      case 0..11:
       itch(who); break;
      default:
      break;
   }
}
