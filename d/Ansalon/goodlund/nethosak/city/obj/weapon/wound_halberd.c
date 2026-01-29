/*
 * Info: This weapon is based on a mace made by Glain.
 * Wielded by: Suranir in 
 * Creator: Elmore.
 * 
 * This polearm was once created by the High Priests
 * of Istar to aid them and their guards in battle.
 * However this one has been blessed by the evil god
 * Sargonnas, thus no goodalignmed persons can wield
 * this weapon. The blade is serrated and this makes it
 * very hard to dull. 
 * Suranir, the priest of the village of Nethosak, has 
 * furthermore enchated the halberd giving it an
 * improved combat speed
 * Wielded by the High Priest in Nethosak, this item
 * is quite hard to get, since he casts spells, higher
 * speed then normal, and great skills.
 *
 */


#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>
 
#define WOUNDS 1

void
create_weapon()
{
   set_name("halberd");
   set_adj("serrated");
   add_adj("obsidian");
   set_long("The halberd is made out of a smoothe wooden staff "+
         "and has a large blade connected to one end. The blade "+ 
         "have been forged out of the precious obsidian and its "+
         "extremely sharp. There's a small crystal on the "+
         "other end of the staff, which might act like a "+
         "counterweight on combat. The entire halberd is very "+
         "light even though the blade seems quite large. You "+
         "notice some silvery runes which has been engraved "+
         "into to staff. As you look at them they seem to shimmer "+
         "slightly. Some of the runes are overlapped with each "+
         "other almost like they are trying to enchant this "+
         "halberd beyond it's capability.\n");

   set_short("serrated obsidian halberd");
   set_default_weapon(48,48, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);

   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO, ({"These polearms were created "+
      "by the High Priests of Istar before the Cataclysm.  "+
      "Forged from a long forgotten mixture of metals that give it "+
      "its durability and light weight, it was then enchanted to "+
      "leave ghastly wounds that could not be healed through normal means. "+
      "Many of the High Priests enemies slowly bled to death "+
      "attempting to flee from the cruel oppressors. This one "+
      "seems to be defiled by becoming blessed by the evil "+
      "god Sargonnas, which gives it some extra speed.\n", 35}));

   add_item(("blade"),"The blades are both identical and made out of "+
                     "obsidian, they are extremely sharp and the way they "+
                     "are constructed would make it quite easy to impale "+
                     "someone.\n");

   add_item(("staff"),"This staff is made from some unknown type of "+
                       "wood. It seems very dark and hard, you notice some "+
                       "strange runes on the staff.\n");

   add_item(({"runes", "silvery"}),
        "These runes may be of elven origin but neither "+
        "the writing nor the way that this weapon has been "+
        "forged indicate who could have done this. You start "+
        "to stare intensely on the runes, but but are unable "+
        "to decipher what they mean.\n");

   add_item(({"crystal"}),"This is a transparent crystal "+
        "that has been put here to make the weapon more steady in "+
        "combat.\n");

   set_wf(this_object()); 
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_WEIGHT, 4470);
   set_likely_dull(0);

}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{ 
    if (phurt < 0)
    {
       return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    if (!random(10))
    {
    switch (random(WOUNDS))
      {
      default:
         wielder->catch_msg("You feel a tug on the " + short() +
            " as you rip flesh out of the " + hdesc + " of " +
            QTNAME(enemy) + " with the serrated edge " +
            "of the " + short() + ", leaving behind a nasty " +
            "bleeding wound.\n");
         enemy->catch_msg("Pain shoots through your " + hdesc +
            " as your flesh is torn off from the serrated edge on " +
            "of the " + short() + ", leaving behind a " +
            "nasty bleeding wound.\n");
         wielder->tell_watcher(QCTNAME(wielder) + " rips the flesh " +
            "out of the " + hdesc + " of " + QTNAME(enemy) + " with " +
            "the serrated edge of the " + short() +
            ", leaving behind a nasty bleeding wound.\n", enemy);
         break;
      }
      clone_object("/d/Ansalon/goodlund/nethosak/city/std/bleed_obj.c")->move(enemy);
   }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

mixed
wield(object what)
{
    if (this_player()->query_alignment() <= 900)
    {
        wielder->catch_msg("As you grab around you runes of the halberd, "+
                           "you feel the power of Sargonnas running "+
                           "through your body!\n");
        wielder->tell_watcher(QCTNAME(wielder)+ " wields " +HIS(wielder)+ " "+
                     short()+ ".\n"); 
        return 1;
    }
    this_player()->heal_hp(-(random(1000)+800));
    wielder->tell_watcher(QCTNAME(wielder)+ " fails to wield the " +short() + ".\n");
    return "A bolt of lightning leap from the staff, hitting you "+
           "hard in your chest. The lightning surge through your "+
           "entire body causing extreme pain.\n"+
           "A distant voice speaks to you: Foolish mortal "+
           "you dare try to wield me!\n"+
           "You release your grip around the halberd.\n";
}

mixed
unwield(object what)
{
    wielder->catch_msg("You release your grip around the halberd.\n");
    wielder->tell_watcher(QCTNAME(wielder)+ " releases " +HIS(wielder)+
                          " grip around the " +short()+ ".\n");
    return 0;
}

