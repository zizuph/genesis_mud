/**  Code for special attack by Priest/Priestesses of Dephonia
**
*** The Dephonian raises his/her hand and a black light strikes the enemy.
**  HP = - (SpecAttackLevel + Random(20))
**
**   Assumptions:
**   - included by Dephonian NPCs only
**   - SpecAttackLevel has been declared
**
**  Date       Coder      Action
** -------- -----------   -------------------------------------------
** 12/12/94  Zima         Created
** 8/10/95   Zima         Added a factor to allow "modulation" of the
**                        effect of the attack. Initially done because
**                        of MAX_HP changes for players. Change adjusts
**                        attack HP levels to 2/3 of levels specified
**                        in each Dephonian NPC.
**/
/* Adjust level to 2/3 of old level */
#define NUMERATOR 2
#define DENOMINATOR 3
string
random_bodypart()
{
   string *randparts;
   randparts = ({"head","chest","leg","arm","hand","head","chest"});
   return randparts[random(sizeof(randparts))];
}
 
string
random_effect()
{
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
 
string
random_chant()
{
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
 
int
special_attack(object victim)
{
    string who;
    string pronoun;
    string bodypart;
    string Myname;
    object me = this_object();
    int AtkHp;
 
    if(random(5)) return 0; /* stop here for normal attack 80% of time */
 
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
    AtkHp=SpecAttackLevel+random(20);          /* randomize initial level */
    AtkHp=(NUMERATOR * AtkHp) / DENOMINATOR;   /* scale level */
    victim->heal_hp(-AtkHp);
    return 1;
}
