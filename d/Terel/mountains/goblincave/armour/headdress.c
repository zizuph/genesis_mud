/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * headdress.c
 *
 * Worn by the goblin lord.
 * Tomas  -- December 1999
 *
 * Modification Log:
 * May 2000 Tomas -- added emotes and wear description.
                     increased armour class from 20 to 40.

   30 Apr 2003, Bleys -- fixed a typo in the long desc

    26 Sep 2003, by Bleys
        - Fixed a typo in the warcry emote.
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;
inherit "/lib/keep";


#include <tasks.h>
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <options.h>
#include <filter_funs.h>


/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_terel_armour()
{
    set_name("headdress");
    set_adj("feathered");
    set_pname("headdresses");
    set_short("feathered headdress");
    set_long("You examine the headdress and note the large black feathers " +
       "that create a train almost two feet down the lenth of the back of " +
       "the headdress. The feathers are attached to a hard leather shell " +
       "which has been mounted on a hardened steel helmet.\n " +
       "You notice a worn out tag affixed to the inside of the headdress. " +
       "Perhaps you can read it.\n");

    add_item(("tag"),"You notice a worn out tag afixed to the inside of the " +
       "headdress. Perhaps you might be able to read it.\n");

    set_ac(40);
    set_armour_size(SMALL);
    set_at(A_HEAD);
    set_af(this_object());   /* setup below: wear/remove */
    set_keep(1);
    set_am(({ 1, 1, -2}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1000);

    add_cmd_item("tag","read","The tag reads: hdwarcry, " +
                 "hddance, hddisagree.\n");
}


mixed
wear_terel_armour(object ob)
{

    if (wearer->query_intoxicated() > 100)
    {
       write("In a drunken stupor you attempt to wear the " +short()+
           " backwards. Cursing your misfortune, you turn it around.\n");
       say(QCTNAME(TP) + " clumsily wears the " + short() + " backwards, saying " +
          "something that is muffled by the feathers, then manages " +
          "to get it turned around.\n");
       return 0;
    }
       write("You slide the " + short() + " over your head, adjusting " +
             "the long train of feathers behind your back.\n");
       say(QCTNAME(TP) + " slides the " + short() + " over " +
             HIS_HER + " head, then adjusts the long train of feathers " +
             "behind " + HIS_HER + " back.\n");
       return 0;
}


mixed
remove(object ob)
{
   return 0;
}


/* Special thanks to Goldberry for her outstanding emote ideas */

init()
{
    ::init();
    add_action("do_warcry", "hdwarcry");
    add_action("do_disagree", "hddisagree");
    add_action("do_dance", "hddance");
}



int
do_warcry(string str)
{
    string wepdesc;
    object *weapons = (TP->query_weapon(-1));

    if (!query_worn())
    {
       NF("You need to wear the headdress first.\n");
       return 0;
    }

    if (!sizeof(weapons))
    {
        write("You dance around shouting a piercing warcry at " +
         "the top of your lungs.\n");
        say(QCTNAME(TP) + " dances around shouting a piercing warcry " +
         "at the top of " + HIS_HER + " lungs.\n");
        return 1;
    }
    wepdesc = weapons[random(sizeof(weapons))]->query_short();
      write("You dance around shouting a piercing warcry at " +
         "top of your lungs while waving your " +wepdesc+ ".\n");
      say(QCTNAME(TP) + " dances around shouting a piercing warcry " +
         "at the top of "+HIS_HER+" lungs while waving "+HIS_HER +
         " "+wepdesc+".\n");

    return 1;
}


int
do_disagree()
{

    if (!query_worn())
    {
       NF("You need to wear the headdress first.\n");
       return 0;
    }

    write("You shake your head in disagreement, sneezing " +
       "violently as one of the feathers from the headdress " +
       "tickles your nose.\n");
    say(QCTNAME(TP) + " shakes " + HIS_HER + " head in disagreement, " +
       "then promptly sneezes violently as one of the feathers on " +
       (HIS_HER) + " headdress tickles " + HIS_HER + " nose.\n");

    return 1;
  }


int
do_dance(string *str)
{
    object *weapons = TP->query_weapon(-1);
    string wepdesc;

    if (!query_worn())
    {
       NF("You need to wear the headdress first.\n");
       return 0;
    }

    if (!sizeof(weapons))
    {
        write("You perform an ancient wardance, chanting " +
           "in some unknown dialect while waving your hands " +
           "wildy in the air.\n");
        say(QCTNAME(TP) + " dances around in a circle chanting " +
           "in some strange dialect while waving " + HIS_HER + " hands " +
           "wildly in the air.\n");
        return 1;
    }
    wepdesc = weapons[random(sizeof(weapons))]->query_short();

      write("You perform an ancient wardance, chanting " +
         "in some unknown dialect while waving your " +
         wepdesc+ " in the air.\n");
      say(QCTNAME(TP) + " dances around in a circle chanting " +
         "in some strange dialect while waving "+HIS_HER +
         " "+wepdesc+" in the air.\n");

    return 1;
}



