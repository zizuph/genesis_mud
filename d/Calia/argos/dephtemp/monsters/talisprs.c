/* Keeper of the Talisman of Dephonia
**
** She will bless the sacramental wine to make it poisonous, a requirement
** for the vision quest.
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95    Created
** Zima           2/5/95    Since this priestess is required for the quest,
**                          her special attack includes a poison!
** ?              1998/6/6  ? Previous update
** Lavellan       2010/9/2  Typos
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define SpecAttackLevel 100
 
string random_bodypart() {
   string *randparts;
   randparts = ({"head","chest","leg","arm","hand","head","chest"});
   return randparts[random(sizeof(randparts))];
}
 
string random_effect() {
   string *randeffects;
   randeffects = ({
                 "You feel an intense pain throughout your body!\n",
                 "Your head begins to reel in pain!\n",
                 "Your blood feels as if it boiling!\n",
                 "You feel an intense darkness choke your heart!\n",
                 "Your skin feels as if it is on fire!\n"
                 });
   return randeffects[random(sizeof(randeffects))];
}
 
string random_chant() {
   string *randchant;
   randchant = ({
               " 'Behold the power of the Light of Darkness!'",
               " 'Smite the head of thine enemies, oh Mother!'",
               " 'Uprezia Nate Matera!'",
               " 'Dedokamus Postestes Matera!",
               " 'Lignus Nate Obsidia!'"
               });
   return randchant[random(sizeof(randchant))];
}
 
int special_attack(object victim) {
    string who;
    string pronoun;
    string bodypart;
    string Myname;
    object poison;
    object me = this_object();
 
    if(random(3)) return 0; /* stop here for normal attack 66% of time */
 
    who      = lower_case(victim->query_name());
    Myname   = QCTNAME(me);
    bodypart = random_bodypart();
    if (query_gender()) pronoun = "her";
    else                pronoun = "his";
 
    me->command("emote chants" + random_chant());
    victim->catch_msg(Myname + " raises " + pronoun + " hand and " +
          "a beam of black light strikes your " +bodypart+"!\n");
    tell_object(victim, random_effect());
    tell_room(environment(victim),
        Myname + " raises " + pronoun + " hand and " +
        "a beam of black light strikes " + QTNAME(victim) + "'s " +
        bodypart + ".\n",victim);
    victim->heal_hp(-(SpecAttackLevel+random(20)));
    poison=clone_object(OBJ_DIR+"talpoisn");
    poison->move(victim);
    poison->start_poison();
    return 1;
}
 
void equip_me() {
    object this=this_object();
    seteuid(getuid());
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "talisman")->move(this);
    clone_object(ARMOUR_DIR+"dring1")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"priestess of dephonia","priestess","dephonian",
               "dephonian priestess","human"}));
    set_adj("Dephonian");
    intro_resp_cmd=(({"say The Name is a doorway to the soul, foolish one.",
                     "emote cackles maniacally."}));
    set_adj("old");
    set_race_name("human");
    set_short("old Dephonian priestess");
    set_pshort(" Priestesses of Dephonia");
    set_long(
        "She is an old priestess of the Order, her wrinkled face "+
        "gaunt as that of a corpse, but with dark staring eyes "+
        "alive with evil.\n");
 
    set_act_time(5);
    add_act("emote holds her hands over the vessel and prays.");
    add_act("emote drops something into the vessel, "+
            "which erupts with a boom!");
    add_act("smile evilly");
    add_act("say the blessing of the Talisman is a sacred gift.");
    add_act("emote dips her finger in the vessel and tastes its brew.");
    add_act("smile mysteriously");
    add_act("emote raises her hands and whispers a prayer.");
    add_act("say Have you been selected? I have not been told.");
 
    set_cact_time(3);
    add_cact("say You have disturbed a force that shall kill you!");
    add_cact("emote surrounds herself in black light.");
    add_cact("emote points a crooked finger at you and chants a curse.");
    add_cact("say run in fear, infidel, for the Light of Darkness " +
             "overshadows you!");
    add_cact("emote hisses a serpentile curse at you.");
    add_cact("say the Talisman is powerless in the hands of an infidel!");
    add_cact("emote glares at you with jet black eyes.");
    add_cact("say You shall be swallowed up in Darkness!");
    add_cact("say I shall send you to you eternal damnation!");
 
    set_default_answer("The old Dephonian priestess says: I do not speak "+
       "your language well, I do not understand what you say.\n");
    add_ask(({"vision","of vision","about vision"}),
              "say The vision is truly a great revelation.\n",1);
    add_ask(({"quest","of quest","about quest"}),
              "say May the Light of Darkness guide you in your quest for "+
              "enlightenment.",1);
    add_ask(({"wine","of wine","about wine"}),
              "say Only sacred wine may receive the blessing.\n",1);
    add_ask(({"fruit","of fruit","about fruit","fruit of the vine",
              "of fruit of the vine","about fruit of the vine"}),
              "say The fruit of the vine is crushed by mortal hands, "+
              "and its blood may become sacred.\n",1);
    add_ask(({"blessing","of blessing","about blessing","for blessing"}),
       "say Pray for a blessing and perhaps you will receive it.",1);
 
    /* this NPC is not really meant to be killed, so discourage it */
    set_gender(1); /* female */
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    set_stats(({100,200,200,0,0,0})); /* STR DEX CON INT WIS DIS */
    set_hp(query_max_hp());
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_alignment(0);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
