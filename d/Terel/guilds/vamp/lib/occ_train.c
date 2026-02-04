
#include "../guild.h"

inherit LIB_DIR+"train_ob";

#include <ss_types.h>


public void create_object()
{
    ::create_object();
    
    sk_add_train(VAMP_SKILL_BITE, "bite an opponent", "savage", 100, 100);
    sk_add_train(VAMP_SKILL_FLURRY, "unleash a flurry of attacks", 
                                        "flurry", 100, 100);

    sk_add_train(SS_WEP_SWORD, "fight with swords", "sword", 0, 75);
    sk_add_train(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat", 0,75);
    sk_add_train(SS_WEP_CLUB, "fight with clubs", "club", 0, 75);
    sk_add_train(SS_WEP_POLEARM, "fight with polearms", "polearm", 0, 75);
    sk_add_train(SS_WEP_AXE, "fight with axes", "axe", 0, 75);

    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 75);
    sk_add_train(SS_PARRY, "parry attacks", "parry", 0, 75);
    sk_add_train(SS_BLIND_COMBAT, "fight while blind", 
                                    "blindfighting",0,50);

    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 75);

    sk_add_train(SS_SPELLCRAFT, "understand magical theory", 
                                        "spellcraft", 0 ,75);

    sk_add_train(SS_ELEMENT_AIR, "use air magic",
                                        "air spells", 0, 60);
    sk_add_train(SS_ELEMENT_DEATH, "use death magic",
                                        "death spells", 0, 40);
    sk_add_train(SS_FORM_DIVINATION, "use divination magic",
                                        "death spells", 0, 40);
    sk_add_train(SS_FORM_ENCHANTMENT, "use enchantment magic",
                                        "enchantment spells", 0, 40);
    sk_add_train(SS_FORM_CONJURATION, "use conjuration magic",
                                        "conjuration spells", 0, 60);
    sk_add_train(SS_FORM_ILLUSION, "use illusion magic",
                                        "illusion spells", 0, 60);

    //Some training halls cannot be reached by vampires - add those here
    sk_add_train(SS_ELEMENT_LIFE,  "use life spells",
                                        "life spells", 0 , 20);
    sk_add_train(SS_ELEMENT_EARTH,  "use earth spells",
                                        "earth spells", 0 , 20);
    sk_add_train(SS_ELEMENT_WATER,  "use water spells",
                                        "water spells", 0 , 20);
    sk_add_train(SS_FORM_ABJURATION,"use abjuration spells",
                                        "abjuration spells", 0 , 20);

    sk_add_train(SS_LANGUAGE, "speak foreign languages", 
                                        "language", 0, 60);
    sk_add_train(SS_WEP_KNIFE, "fight with knives", "knife", 0, 60);


    sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 50);
    sk_add_train(SS_LOC_SENSE, "track your location", 
                              "location sense", 0, 50);
    sk_add_train(SS_CLIMB, "climb", "climb", 0, 50);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 50);
    sk_add_train(SS_TRADING, "trade", "trading", 0, 50);
    sk_add_train(SS_TRACKING, "track your prey", "tracking", 0, 75);

}

public int
sk_hook_allow_train(object who, string str, string verb)
{
    return who->query_vampire();
}

