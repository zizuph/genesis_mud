/*
 * Created by Boron July 2002, this armour is only obtainable if you
 * get the ingredients to the blacksmith Chert, and wait for him to
 * finish it for ya.
 *
 * Ingredients are:   a scale of a dragon (slay the dragon, cut from corpse
 *                                         and sell it to Chert)
 *                    a silver bar (mine silver nuggets, sell nuggets,
 *                                  wait for another smith to finish and then
 *                                  buy a silver bar, bring it to Chert)
 *                    solamnian platemail (Get one made at Cherts place,
 *                                  also requires ingredients (iron and carbon)
 *
 * The armour offers about the same AC as dragon scale, it offers 8 more points
 * in magic protection, and since this is the newest design from Chert I also
 * made it a bit lighter.
 *
 * Copyright (c) 2002 by Boron, Daniel W. Mathiasen
 *
 */

/* Increased weight, and downgraded AC.
 * Insane to grant 46 ac full armour that weigh 5000-6000 grams.
 * - Navarre Feb 2007
 */


#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";
inherit "/d/Genesis/lib/commodity";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include "../local.h"
#include "../knight/guild.h"


int bless(string str);


#define BLESSED_KNIGHT_ARMOUR "_i_blessed"

public void
create_armour()
{
    set_name("scalemail");
    set_pname("scalemails");
    add_name(({"scale","mail","armour"}));
    add_pname(({"scales","mails","armours"}));
    add_adj("solamnian");
    add_adj("full");
    add_adj("body");
    set_short("solamnian scalemail");
    set_pshort("solamnian scalemails");
    set_long("This is a full body armour of a Solamnic Knight. The steel " +
      "is polished perfectly to shine brightly. The breast plate is made " +
      "of dragon scales, and upon the scales, emblazoned in silver you see " +
      "the symbols of the knighthood: Crown, Sword, Rose " +
      "and Kingfisher, deities whom from time to time are known to bestow " +
      "their blessings on armours. @@tradition@@\n");
    add_item(({"crown","sword","rose","kingfisher","symbols"}),
      "These are the symbols of the Solamnian knighthood, the crown, " +
      "sword and rose representing the three orders, and the " +
      "kingfisher symbolizing the knighthood as a unity.\n");
    set_ac(40);
    set_at(A_TORSO | A_ARMS | A_LEGS );

    set_commodity_name ("scalearmour"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_ARMOUR(35), 0);

     set_keep(1);
     add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
     add_prop(OBJ_S_WIZINFO,"This is a modified version of the solamnian "+
       "platemail, however a dragon scale have been added, where the magic " +
       "of the dragon provides resistance against LIGHT and FIRE.\n");
     add_prop(MAGIC_AM_ID_INFO,
         ({"The core of this armour is a solamnian platemail " +
         "however a dragon scale have been added to it.\n", 10,
         "A Krynnian dragon is magical and so is this armour.\n", 20,
         "There is a special protection from this armour against " +
         "natural threats.\n",50,
         "This armour may protect against fires and lightning.\n", 70}));

    add_prop(OBJ_I_VOLUME, 6239);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(40, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(46) + 3000);
    add_prop(VK_NOBUY, 1);

    // We want wear and remove to be called
    set_af(this_object());
}

public
void init()
{
    ::init();
    add_action(bless, "bless");

}

int
bless(string str)
{
    int lev = TP->query_knight_level();
    string god;

    if (str == "")
      return 0;

    if ( (str != "scalemail") || (str != "mail")
       || (str != "solamnian scalemail") || (str != "armour") )

    if (!TP->query_guild_member("Solamnian Knights"))
      return 0;

    switch(lev)
    {
    case 5:
      god = "Paladine";
    break;
    case 4:
      god = "Kiri-Jolith";
    break;
    case 3:
      god = "Habbakuk";
    break;
    default:
      god = "the Knighthood";
    }

    write("You kneel holding out the "+ TO->short() +" and bless it "+
      "in the name of " + god +".\n");
    say(QCTNAME(TP)+" kneels holding out "+POSSESSIVE(TP)+" "+
      TO->short()+" giving a short prayer to "+ god +".\n" +
      "The " + TO->short()+ " gives a brief pulse of light.\n");

    TO->add_prop(BLESSED_KNIGHT_ARMOUR, 1);

    log_file("armour_quest", ctime(time()) + " " + this_player()->query_name() +
        " blessed the solamnian scalemail\n");

    return 1;
}


string
tradition()
{
    string str = "";

    if (TP->query_guild_member("Solamnian Knights"))
    {
      str = " Traditionally, such an armour would be bequeathed along " +
     "a family of Knights of Solamnia. It would be the proud heritage " +
     "and a testament to nobility among knights. This particular armour " +
     "does however have the brand of Chert Armstrong, the current black" +
     "smith of Vingaard Keep.";

      if ( ( !TO->query_worn() ) && ( !TO->query_prop(BLESSED_KNIGHT_ARMOUR) ) )
      {
          str += " Holding this armour in your hands, gives you a " +
          "feeling it is somehow incomplete, though the craftmanship " +
          "is among the finest in the world.\n";
      }

      return str;
    }
    else
      return str;
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{

    if (protectee == query_worn() && TO->query_prop(BLESSED_KNIGHT_ARMOUR))
      {
      if (prop == MAGIC_I_RES_FIRE || prop == MAGIC_I_RES_LIGHT)
        return ({ 18, 1}); /* additive */
      }
    else
      return ::query_magic_protection(prop, protectee);
}

mixed
wear(object what)
{
    if (TO->query_prop(BLESSED_KNIGHT_ARMOUR))
    {
        TP->catch_msg("You feel a calm forgiving sensation as you wear the scalemail.\n");
        TP->add_magic_effect(TO);
        return 1;
    }
    return 0;
}

mixed
remove(object what)
{
    if (TO->query_prop(BLESSED_KNIGHT_ARMOUR))
    {
        TP->catch_msg("Unease slowly fills your heart as you remove the scalemail.\n");
        TP->remove_magic_effect(TO);
        return 1;
    }
    return 0;
}
