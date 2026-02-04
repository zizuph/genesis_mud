/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/potion";
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define CAST_LIMIT    80  /* The limit for this to become a success */
#define TP            this_player()
#define ETP           environment(TP)

/* Function name: sanare
* Description:   heals target of divine wound
* Arguments:     str -
* Returns:       1/0
*/
nomask mixed
purus(string str)
{
    object who, *inv;
    int mana_limit, suc, i, strength;
    string *types;

    if (str)
        who = present(lower_case(str), ETP);
    if (!who)
    {
        if (!str || str == "myself" || str == "me")
            who = TP;
        else
            return "Who shall you purify?\n";
    }
    
    if (who != TP && !CAN_SEE(TP, who))
        return "Who shall you purify?\n";

    if (NPMAGIC(who)) /* See if it is possible to cast a magic spell on obj. */
        return "Something prevents you from cast this spell.\n";

    mana_limit = 80;
    if (who == TP) /* Costs more to heal yourself */
        mana_limit = 100;

    if (TP->query_mana() < mana_limit)
        return "You do not have the strength to call out.\n";

    suc = TP->query_skill(SS_FORM_ABJURATION) +
          TP->query_skill(SS_ELEMENT_LIFE);
    if (random(suc) < random(CAST_LIMIT))
    {
        write("Your call is not heard.\n");
        TP->add_mana(-mana_limit / 3);
        return 1;
    }

    TP->add_mana(-mana_limit);
   write("You call upon the sacred spirits to bring their purifying presence to the world.\n");
   say(QCTNAME(TP) + " hunches over like some sorrowful beggar and places " + TP->query_possessive() + " hands upon " + TP->query_possessive() + " chest, moaning out some arcane incantation.\n");
  set_alarm(4.0, -1.0, "cure_me", who);
   return 1;
}

cure_me(object who){

    object them, *inv;
    int mana_limit, suc, i, strength;
    string *types;
  who->catch_msg("A great power passes through your body, a cleansing spirit of holiness.\n");
   who->heal_hp(30);
    
    inv = all_inventory(who);
    strength = 700;
    types = ({ "all" });

    for (i=0; i<sizeof(inv); i++)
    {
        if (function_exists("query_poison_type", inv[i]) == "/std/poison_effect")
        {
            inv[i]->cure_poison(types, strength);
            strength = strength / 2;
    inv[i]->remove_object();
        }
    }

   if(present("poison", who)){
  set_alarm(4.0, -1.0, "cure_me", who);
  }
    return 1;
}
