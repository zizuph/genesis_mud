#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
int added_skill, added_skill2;


void
create_terel_armour()
{
    set_name("armour");
    set_adj("studded");
    set_adj("leather");
    set_short("studded leather armour");
    set_long("A studded leather shirt, to protect the body of it's wearer. "+
                  "The shirt is a medium brown with silver studs about two "+
                  "inches apart from each other. The shirt is light and allows "+  
                  "for quite a bit of mobility.\n");
    set_armour_size(SMALL);
    set_default_armour(50, A_BODY, 0, 0);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 1200);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,"Enchanted studded leather armour worn by "+
                  "Sliver hidden in Calathin. Armour class of 50, and adds 1/10 "+
                  "the wearers dex to both sneak and hide, capped at 200. The "+
                  "armour can only be worn by the hobbit race.\n");

    add_prop(MAGIC_AM_ID_INFO,({
             "The "+short()+" is enchanted to protect from physical blows.\n",40,
             "The "+short()+" will allow the wearer to hide and sneak better.\n",70}));

}

int
wear_terel_armour(object obj)
{
    if(TP->query_race() == "gnome" || TP->query_race() == "goblin" || TP->query_race() == "dwarf")
    {
        write("The "+short()+" will not fit you, try as you might.\n");
        return 0;
    }

    added_skill = (10 + ((TP->query_stat(SS_DEX))/10));
    added_skill2 = (10 + ((TP->query_stat(SS_DEX))/10));

    if(added_skill > 20)
        added_skill = 20;

    if(added_skill2 > 25)
        added_skill2 = 25;
    if ((TP->query_skill(SS_SNEAK) + added_skill) > 100)
    {
        added_skill = (100-(TP->query_skill(SS_SNEAK)));
    }
    TP->set_skill_extra(SS_SNEAK, (TP->query_skill_extra(SS_SNEAK)+
                                     added_skill));

    if ((TP->query_skill(SS_HIDE) + added_skill2) > 100)
    {
        added_skill2 = (100-(TP->query_skill(SS_HIDE)));
    }
    TP->set_skill_extra(SS_HIDE, (TP->query_skill_extra(SS_HIDE)+
                                     added_skill2));

    return 0;
}


int remove(object arm)
{

    object wearer;
    wearer = query_worn();

    wearer->set_skill_extra(SS_SNEAK,
            (wearer->query_skill_extra(SS_SNEAK) - added_skill));

    wearer->set_skill_extra(SS_HIDE,
            (wearer->query_skill_extra(SS_HIDE) - added_skill2));

    return 0;
}
