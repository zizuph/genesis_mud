/* Anduril */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/filter_funs.h"
#include "/d/Gondor/defs.h"
#define ORCS     2
#define UNDEAD   1

int slaying;

create_weapon() {
  set_name("broadsword");
  add_name("anduril");
  add_name("sword");
  set_adj("shining");
  set_adj("great");
  set_long("@@long_func");
  add_item("runes","The runes are of elven design, holding magic of great virtue.\n"+
    "You are unable to interpret their full meaning.\n");
  add_item("hilt","The hilt is wrapped with red hide, and strapped with leather.\n"+
    "It feels good to hold.\n");
  add_item("blade",BSN("On the blade is traced a device of seven stars set "+
    "between the crescent Moon and the rayed Sun, and about them is written "+
    "many runes. It is very bright; the light of the sun "+
    "shines redly, and the light of the moon shines cold, and the edge "+
    "is hard and keen."));
  set_default_weapon(48,45,W_SWORD,W_SLASH|W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(OBJ_I_LIGHT,1);
  add_prop(MAGIC_AM_MAGIC,({ 40, "enchantment" }));
  add_prop(OBJ_S_WIZINFO,"This two-handed sword is a magical weapon wielded by\n"+
    "Aragorn. The sword is orc-slaying and undead-slaying, but only\n"+
    "one or the other, according to the whim of the wielder.\n"+
    "Damage on orcs and undead will be between 1.5x and 2x normal damage\n"+
    "if slaying that kind of creature. It also has the power to\n"+
    "give extra head-criticals and break the helmet of the opponent.\n");
  add_prop(MAGIC_AM_ID_INFO,({ "The bright broadsword seems to be magical.\n",1,
    "It has powers to slay Orcs and Wraiths!\n",40,
    "The sword can only slay one OR the other, though. The wielder\n"+
    "may choose which race if he is wise and intelligent enough.\n",60}));
  add_prop(OBJ_I_WEIGHT,14500);
  add_prop(OBJ_I_VOLUME,7400);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(48,45)+random(2000)-100);
  add_prop(OBJ_M_NO_BUY,1);
  set_likely_break(0);
  set_likely_dull(0);
}

did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
  if (hdesc == "head")
    if (random(100) < dam && enemy->query_armour(TS_HEAD)) set_alarm(1.0,0.0,"head_critical",enemy);
  if (hdesc == "head" && !enemy->query_armour(TS_HEAD))
    {
    dam = dam * 2;
    enemy->heal_hp(-dam);
    set_alarm(1.0,0.0,"head_critical",enemy);
    }
  if (slaying == ORCS) {
    if (enemy->query_race_name()!="uruk" 
        && enemy->query_race_name()!="orc"
        && enemy->query_race_name()!="half-orc"
        && enemy->query_race_name()!="halforc"
        && enemy->query_race_name()!="uruk-hai" 
        && enemy->query_race_name()!="goblin")
    return 0;
    }
  else if (slaying == UNDEAD) {
    if (enemy->query_race_name()!="wraith" 
        && enemy->query_race_name()!="wight"
        && enemy->query_race_name()!="ghoul"
        && enemy->query_race_name()!="ghost"
        && enemy->query_race_name()!="undead"
        && enemy->query_race_name()!="vampyre"
        && enemy->query_race_name()!="vampire"
        && enemy->query_prop(LIVE_I_UNDEAD) < 1)
    return 0;
    }
  if (phurt == -1) {
    query_wielded()->catch_msg("You swing the "+sword_desc()+" with all your might - through open air.\n");
    enemy->catch_msg("You deftly duck as "+QTNAME(query_wielded())+" swings "+
      query_wielded()->query_possessive()+" "+sword_desc()+" at you.\n");
    tell_watcher(QCTNAME(query_wielded())+" swings the "+sword_desc()+" at "+
      QTNAME(enemy)+", who deftly ducks!\n",enemy);
    }
  else
  if (phurt == 0) {
    query_wielded()->catch_msg("Your "+sword_desc()+" just barely misses "+
      QTNAME(enemy)+"!\n");
    enemy->catch_msg("The "+sword_desc()+" of "+QTNAME(query_wielded())+
      " just barely misses your "+hdesc+"!\n");
    tell_watcher(QCTNAME(query_wielded())+" just barely misses "+QTNAME(enemy)+
      "'s "+hdesc+" with the "+sword_desc()+"!\n",enemy);
    }
  else 
  if (phurt < 5) {
    query_wielded()->catch_msg("You slash at the "+enemy->query_race_name()+
       "'s "+hdesc+" with your "+sword_desc()+".\n");
    enemy->catch_msg("You feel pain as the "+sword_desc()+" hits your "+hdesc+".\n");
    tell_watcher(QCTNAME(query_wielded())+" slashes at "+QTNAME(enemy)+", "+
    "hitting "+enemy->query_possessive()+" "+hdesc+" with the "+sword_desc()+".\n",enemy);
    }
  else
  if (phurt < 10) {
    query_wielded()->catch_msg("You strike at the "+enemy->query_race_name()
      +"'s "+hdesc+" with your "+sword_desc()+".\n");
    enemy->catch_msg(QCTNAME(query_wielded())+" strikes your "+hdesc+" with "+
      query_wielded()->query_possessive()+" "+sword_desc()+".\n");
    tell_watcher(QCTNAME(query_wielded())+" strikes at "+QTNAME(enemy)+" with "+
      query_wielded()->query_possessive()+" sword Anduril, hitting "+
      enemy->query_objective()+" in the "+hdesc+".\n",enemy);
    }
  else
  if (phurt < 20) {
    query_wielded()->catch_msg("You hurt the "+hdesc+" of "+QTNAME(enemy)+
      " with your "+sword_desc()+".\n");
    enemy->catch_msg("You are hurt in the "+hdesc+" by "+
      QTNAME(query_wielded())+"'s "+sword_desc()+"!\n");
    tell_watcher(QCTNAME(query_wielded())+" hurts "+QTNAME(enemy)+"'s "+hdesc+" with the "+sword_desc()+".\n",enemy);
      }
  else
  if (phurt < 30) {
    query_wielded()->catch_msg("You swing your "+sword_desc()+" at "+
      QTNAME(enemy)+", and hurt "+enemy->query_objective()+" very bad "+
      "in the "+hdesc+".\n");
    enemy->catch_msg(QCTNAME(query_wielded())+"'s "+sword_desc()+" hurts "+
      "your "+hdesc+" very hard!\n");
    tell_watcher(QCTNAME(query_wielded())+" wounds "+QTNAME(enemy)+"'s "+hdesc+" with a strong slash.\n",enemy);
    enemy->catch_msg("You scream with pain!\n");
    enemy->command("scream");
    }
  else
  if (phurt < 50) {
    query_wielded()->catch_msg("You cry: By Elendil! as you bring the "+
      sword_desc()+" down extremely hard on the "+enemy->query_race_name()+
      "'s "+hdesc+"!\n");
    enemy->catch_msg(QCTNAME(query_wielded())+" cries: By Elendil! as "+
      PRONOUN(query_wielded()) + " slashes your " + hdesc + " extremely "+
       "hard with " + POSSESSIVE(query_wielded()) + " " + sword_desc() + "!\n");
    tell_watcher(QCTNAME(query_wielded())+" brings the "+sword_desc()+" down extremely hard on "+QTNAME(enemy)+
      "'s "+hdesc+", shouting: By Elendil!\n",enemy);
    }
  else if (phurt < 70) {
    query_wielded()->catch_msg("You hear the sounds of bones breaking as you smash "+
      QTNAME(enemy)+"'s "+hdesc+" with a great strike of your "+sword_desc()+"!\n");
    enemy->catch_msg("As "+QTNAME(query_wielded())+"'s "+sword_desc()+" strikes your "+
      hdesc+", the sickening sound of bones being broken fills your mind.\n");
    tell_watcher("The sound of bones breaking resounds loudly as "+
      QTNAME(query_wielded())+" smashes the "+hdesc+" of "+QTNAME(enemy)+
      " with a mighty swing of the "+sword_desc()+"!\n");
    }
  else if (phurt < 90) {
    query_wielded()->catch_msg("Blood splatters everywhere as your "+sword_desc()+
      " wreaks havoc upon the "+hdesc+" of "+QTNAME(enemy)+"!\n");
    enemy->catch_msg("Blood splatters everywhere as the "+sword_desc()+" of "+
      QTNAME(query_wielded())+" causes severe and excruciating pain to your "+hdesc+"!\n");
    tell_watcher("Blood splatters all over as "+QTNAME(query_wielded())+"'s "+
      sword_desc()+" wreaks havoc on the "+hdesc+" of "+QTNAME(enemy)+"!\n");
    }
  else {
    query_wielded()->catch_msg("With a mighty slash you cut off "+
      QTNAME(enemy)+"'s "+hdesc+" with your great "+sword_desc()+"!\n");
    enemy->catch_msg(QCTNAME(query_wielded())+" wounds you mortally, cutting off your "+
      hdesc+" with "+query_wielded()->query_possessive()+" "+sword_desc()+
      "!\n");
    tell_watcher("With a mighty slash with the "+sword_desc()+", "+
      QCTNAME(query_wielded())+" cuts "+QTNAME(enemy)+"'s "+hdesc+" clean off, "+
      "wounding the "+enemy->query_race_name()+" mortally!\n",enemy);
    }
    enemy->heal_hp(-(random(dam/2)+dam/2));
  return 1;
}

sword_desc()
{
  if (slaying == UNDEAD) return "frozen broadsword";
  else if (slaying == ORCS) return "flaming broadsword";
  else return "gleaming broadsword";
}

init()
{
  ::init();
  add_action("change_slaying","slay");
}

change_slaying(string str)
{
  if (!str) return 0;
  if (str!= "orcs" && str!= "undead") return 0;
  if (!query_wielded()) {
    write("You must wield it first!\n"); return 0; 
  }
  if (str == "orcs" && slaying != ORCS) {
    slaying = ORCS;
    TP->catch_msg("The broadsword flames up as you align it towards Orcs!\n");
    say(QCTNAME(TP)+" holds "+TP->query_possessive()+" sword towards the sky.\n"+
	"'For Elendil!' "+TP->query_pronoun()+" yells, and the sword bursts into flames!\n",TP);
    add_prop(OBJ_I_LIGHT,1);
    remove_adj("cold");
    add_adj("flaming");
    return 1;
  }
  else if (str == "undead" && slaying != UNDEAD) {
    slaying = UNDEAD;
    TP->catch_msg("The broadsword grows cold to the touch as you align it towards Undead!\n");
    say(QCTNAME(TP)+" holds "+TP->query_possessive()+" sword towards the sky.\n"+
	"'For Elbereth!' "+TP->query_pronoun()+" cries, and the flames surrounding the sword\n"+
	"disappear, and a cold radiance take their place.\n",TP);
    add_prop(OBJ_I_LIGHT,0);
    remove_adj("flaming");
    add_adj("cold");
    return 1;
  }
  else write("The great sword Anduril is already aligned towards slaying "+str+".\n");
  return 1;
}

query_recover() { return MASTER+":"+query_wep_recover(); }

init_recover(arg) { init_wep_recover(arg); }





head_critical(object enemy)
{
  object ehelm;
  return;
  ehelm = enemy->query_armour(TS_HEAD);
  if (ehelm) {
  if (random(100) < (ehelm->query_likely_break()*4 + 10))
    {
    query_wielded()->catch_msg("As you hit "+QTNAME(enemy)+" on the "+
      ehelm->query_name()+" with a mighty stroke,\n"+
      "it breaks and falls to the ground in pieces!\n");
    enemy->catch_msg("As the "+sword_desc()+" strikes your "+ehelm->query_short() +
      ", the "+ehelm->query_name()+" breaks, and falls to the ground!\n");
    ehelm->remove_me();
    ehelm->move(ENV(enemy));
    }
    else (ehelm->set_likely_break(ehelm->query_likely_break()+2));
    }
  else if (!ehelm) {
    query_wielded()->catch_msg("The strike in the head seemed to hurt "+
      QTNAME(enemy)+" quite badly!\n");
    enemy->catch_msg("That hit in the head really hurt!\n");
    }
  return 1;
}

long_func()
{
  string str;
  str = "On the blade is traced a device of seven stars "+
    "set between the crescent Moon and the rayed Sun, and about "+
    "them is written many runes. The sword is very bright; the light of "+
    "the sun shines redly in it, and the light of the moon shines cold, "+
    "and its edge is hard and keen. ";
  if (TP->query_skill(SS_APPR_OBJ) > 40 || TP->query_guild_name_occ()=="Gondorian Rangers Guild")
    str = str + "This was once Elendil's sword Narsil, broken when he "+
    "fell by Sauron's hands, and now reforged anew as Anduril, "+
    "Flame of the West, the sword of Aragorn, Elendil's Heir.";
  return BSN(str);
}

tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
