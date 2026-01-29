inherit "/std/armour.c";

inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "../domain.h"


void
create_armour()
{

  set_name("scalemail");
  set_adj(({"battleworn","scuffed", "dented", "ruined"}));
  set_short("ruined scalemail");
  set_long("Once a perfect set of scalemail, having seen one " +
  "too many a battle, it looks to be failing in these times. " +
  "Seemingly crafted during the time of Caliana's reign, it " +
  "holds more significance rather than use. A tear shows through " +
  "a part of the scales, as well as a considerable amount of " +
  "damage to the scales, having been scuffed and dented. Much " +
  "like the ages of the past, this scalemail is at its end.\n");
  
  add_item(({"scale", "scales"}), "Hundreds of scales, each sewn " +
  "into place on a larger suit of treated leather. A few are " +
  "missing here and there, but the real damage is shown by the " +
  "scuffed and dented pieces that look more like bent coins. " +
  "Taking a closer look, you notice minute inscriptions of runes " +
  "hidden in the grime and ruin of the scales.\n\n");
  
  add_item("runes", "The more you stare, you more you seem to lose " +
  "meaning in the runes. They seem to twist and turn away from " +
  "your eyes, only to draw them closer. Straining further does " +
  "little more than keep you from reading them.\n\n");
  
  set_at(A_BODY);
  set_ac(40);
  set_am(({-2, -2, -1}));
  
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_BODY));
  add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(15, A_BODY) / 5);
  
  set_af(this_object());
  set_keep(1);
  
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1));
  add_prop(OBJ_M_NO_BUY, "This scalemail is much too damaged to be sold.");
  add_prop(MAGIC_AM_MAGIC, ({60, "enchantment"}));
  add_prop(MAGIC_AM_ID_INFO, ({"The scalemail before you glows with " +
  "enchantments, their presence tries to elude you. ", 15, 
  "Covered various runes, they hold the meaning of protection, yet " +
  "something still hides from you. ", 35,
  "To look closer only brings chase, relaxing you find that the " +
  "scalemail is hidden in illusions.\n", 60}));
  add_prop(OBJ_S_WIZINFO, "The scalemail reveals its hidden nature " +
  "when worn, dispelling its illusions and is truly good armour.\n");
  
}

mixed
wear(object ob)
{

    if (wearer->query_intoxicated() > 100)
    {
        return "As you decide to use the "+ short() +", its becomes more "+
               "and more a task of trying to even put it on. Straps "+
               "fall part, scales shift, it is useless to try.\n";
    }

    if (wearer->resolve_task(TASK_DIFFICULT, ({TS_DIS, SS_AWARENESS})) < 0)
    {
        return "As you decide to use the "+ short() +", its becomes more "+
               "and more a task of trying to even put it on. Straps "+
               "fall part, scales shift, it is useless to try.\n";
    }

    wearer->catch_tell("A loss of words is explained by the fact " + 
        "of the change in the " + short(wearer) + ", a glamour " +
        "upon the "+ short() +" is dispelled as you wear it.\n");
    

    set_short("runed scalemail");
    set_long("As perfect as the day it was made, the scales of the " +
    "armour hold a shine of steel, with a glow shown by the runes. " +
    "Knowingly crafted during the days of Caliana, the mark of it is " +
    "apparent in the craftsmanship and the magic bespelled on it. " +
    "A cloth interior gives comfort, while the runes and steel " +
    "keep a person protected.\n");
    
    remove_item("scale");
    add_item(({"scale", "scales"}), "Hundreds of scales, each sewn " +
    "into place on a larger suit of treated leather. Shining in " +
    "splendor, steel has been taken and hammered and bent into scales. " +
    "Various writings of runes cover its entirety, allowing no doubt " +
    "to be had of its magical glamour. Heeding its meaning they instill " +
    "a sense of fortitude.\n\n");
  
    remove_item("runes");
    add_item("runes", "Glowing to show their presence, they hold still " +
    "for all to see. Hundreds of little runes written across even as " +
    "many scales, reflect a sense of fortitude and protection.\n\n");
 
    return 0;
}

mixed
remove(object ob)
{

    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        wearer->catch_tell("A blink of the eye transforms the " +
        ""+ short() +" into the worthless piece it was.\n");
    }

    set_short("ruined scalemail");
    set_long("Once a perfect set of scalemail, having seen one " +
    "too many a battle, it looks to be failing in these times. " +
    "Seemingly crafted during the time of Caliana's reign, it " +
    "holds more significance rather than use. A tear shows through " +
    "a part of the scales, as well as a considerable amount of " +
    "damage to the scales, having been scuffed and dented. Much " +
    "like the ages of the past, this scalemail is at its end.\n");

    remove_item("scale");
    add_item(({"scale", "scales"}), "Hundreds of scales, each sewn " +
    "into place on a larger suit of treated leather. A few are " +
    "missing here and there, but the real damage is shown by the " +
    "scuffed and dented pieces that look more like bent coins. " +
    "Taking a closer look, you notice minute inscriptions of runes " +
    "hidden in the grime and ruin of the scales.\n\n");

    remove_item("runes");
    add_item("runes", "The more you stare, you more you seem to lose " +
    "meaning in the runes. They seem to twist and turn away from " +
    "your eyes, only to draw them closer. Straining further does " +
    "little more than keep you from reading them.\n\n");
  
    return 0;
}
