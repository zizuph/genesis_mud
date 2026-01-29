/*
 * /d/Kalad/common/guilds/sh_walkers/arm/sh_gloves.c
 * Created By : Sarr
 * Modified By: Rico
 * First Modif: 30.01.97
 */

#include "/d/Kalad/defs.h"

inherit "/std/armour";

void
create_armour()
{
    set_name("gloves");
    add_adj("black");
    set_adj("shark-skin");
    set_short("pair of black shark-skin gloves");
    set_pshort("pairs of black shark-skin gloves");
    set_long("They are a pair of very valuable gloves made from "+
      "sharkskin. They are colored black, and on the back you see "+
      "a small skull and two crossed daggers painted. These gloves "+
      "are ideal for thieves since the sharp hooks on them help "+
      "snatch items. There are some words etched in a tag "+
      "on it.\n");

    add_item(({ "tag", "words", "etched tag", "etched words" }),
      "The tag reads:\n\n"+
      "\tYou could probably try 'glovegrip' and 'glovetug'.\n"+
      "\t'gloveg' and 'glovet' could be attempted also.\n\n");

    set_at(A_HANDS);
    set_ac(1);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3700);
    add_prop(OBJ_I_VALUE, 300);
}

void
init()
{
   ::init();

   add_action("do_emote1", "gloveg", 1);
   add_action("do_emote2", "glovet", 1);
}

int
do_emote1()
{
   write("Grinning evilly, you tightly clench your fists, "+
      "making the " + short() + " creak.\n");
   say(QCTNAME(TP) + " grins evilly and clenches " + HIS(TP) +
      " fists, causing the " + short() + " to creak.\n");

   return 1;
}

int
do_emote2()
{
   write("You tug on your " + short() + ", pulling them snug."+
      "\nA mischievous smirk slowly spreads across your face.\n");
   say(QCTNAME(TP) + " tugs tightly on " + HIS(TP) + " " +
      short() + ", a mischievous smirk slowly spreading across "+
      HIS(TP) + " face.\n");

   return 1;
}

int
wear(object arm)
{
    set_this_player(E(arm));

    TP->set_skill_extra(SS_PICK_POCKET,TP->query_skill_extra(SS_PICK_POCKET) + 2);
    write("You pull the " + short() + " over your hands.\n");
    say(QCTNAME(TP) + " pulls " + HIS(TP) + " " + short() +
      " on.\n");

    return 1;
}

int
remove(object arm)
{
    set_this_player(query_worn());    
    TP->set_skill_extra(SS_PICK_POCKET,TP->query_skill_extra(SS_PICK_POCKET)- 2);
    write("You pull off the " + short()+ ".\n");
    say(QCTNAME(TP) + " tugs off " + HIS(TP) + " " + short() + ".\n");

    return 1;
}

