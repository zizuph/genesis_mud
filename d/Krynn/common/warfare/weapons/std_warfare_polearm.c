/* 
 * Warfare polearm standard file for the various factions.
 *
 * Arman Kharas, May 2018
 */
 
inherit "/std/weapon";
inherit "/lib/keep";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void   setup_warfare_weapon(int level, int hand, string faction);

int           gLevel, gHit, gPen, gHand;
string        gFaction;

public int
query_krynn_warfare_weapon()
{
    return 1;
}

varargs void
set_weapon_level(int level = 0, int hand = W_ANYH, string faction = "free")
{
    if ( !level )
        gLevel = 0;
    else
        gLevel = level;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 5)
        gLevel = 5;

    if ( !hand )
        gHand = W_ANYH;
    else
        gHand = hand;

    if ( !faction )
        gFaction = "blue";
    else
        gFaction = faction;
        
    setup_warfare_weapon(gLevel, gHand, gFaction);
}

public void
setup_warfare_weapon(int level, int hand, string faction)
{
    switch(level)
    {  
       case 0: 
          gHit = 25;
          gPen = 25;
          break;
       case 1: 
          gHit = 28;
          gPen = 25;
          break;
       case 2: 
          gHit = 28;
          gPen = 28;
          break;
       case 3: 
          gHit = 28;
          gPen = 32;
          break;
       case 4: 
          gHit = 32;
          gPen = 32;
          break;
       case 5: 
          gHit = 35;
          gPen = 35;
          break;
       default:
          gHit = 35;
          gPen = 35;
          break;
    }

    if(hand == W_BOTH)
    {
       gHit += 5;
       gPen += 5;
    }

}

string
warfare_weapon_short()
{
    string short;

    if(gHand != W_BOTH)
    {
        switch(gLevel)
        {  
           case 0: 
              short = "fire-hardened spear";
              add_name("spear");
              add_adj("fire-hardened");
              add_adj("hardened");
              break;
           case 1: 
              short = "hunting spear";
              add_name("spear");
              add_adj("hunting");
              remove_adj("fire-hardened");
              remove_adj("hardened");
              break;
           case 2: 
              short = "iron spear";
              add_name("spear");
              add_adj("iron");
              add_adj("heavy");
              remove_adj("fire-hardened");
              remove_adj("hardened");
              break;
           case 3: 
              short = "spear";
              add_name("spear");
              add_adj("steel");
              add_adj("steel-tipped");
              add_adj("tipped");
              remove_adj("fire-hardened");
              remove_adj("hardened");
              break;
           case 4: 
              short = "steel spear";
              add_name("spear");
              add_adj("steel");
              add_adj("heavy");
              remove_adj("fire-hardened");
              remove_adj("hardened");
              break;
           case 5: 
              short = "military half-pike";
              add_name("half-pike");
              add_name("pike");
              add_adj("steel");
              add_adj("military");
              add_adj("half");
              remove_name("spear");
              remove_adj("fire-hardened");
              remove_adj("hardened");
              break;
           default:
              short = "military half-pike";
              add_name("half-pike");
              add_name("pike");
              add_adj("steel");
              add_adj("military");
              add_adj("half");
              remove_name("spear");
              remove_adj("fire-hardened");
              remove_adj("hardened");
              break;
        }
    }
    else
    {
        switch(gLevel)
        {  
           case 0..2: 
              short = "iron-tipped long-spear";
              add_name("spear");
              add_name("long-spear");
              add_adj("iron");
              add_adj("iron-tipped");
              add_adj("long");
              break;
           case 3: 
              short = "awl pike";
              add_name("pike");
              add_adj("iron");
              add_adj("awl");
              add_adj("iron-tipped");
              remove_name("spear");
              remove_name("long-spear");
              remove_adj("iron-tipped");
              remove_adj("long");
              break;
           case 4: 
              short = "steel-tipped pike";
              add_name("pike");
              add_adj("steel");
              add_adj("steel-tipped");
              remove_name("spear");
              remove_name("long-spear");
              remove_adj("iron");
              remove_adj("iron-tipped");
              remove_adj("long");
              break;
           case 5: 
              short = "steel lance";
              add_name("lance");
              add_adj("steel");
              remove_name("spear");
              remove_name("long-spear");
              remove_adj("iron");
              remove_adj("iron-tipped");
              remove_adj("long");
              break;
           default:
              short = "steel lance";
              add_name("lance");
              add_adj("steel");
              remove_name("spear");
              remove_name("long-spear");
              remove_adj("iron");
              remove_adj("iron-tipped");
              remove_adj("long");
              break;
        }
    }

    return short;
}

string
warfare_weapon_long()
{
    string long;
    string faction = gFaction;

    if(faction == "blue" || faction == "red" || faction == "white" ||
        faction == "black" || faction == "green")
    {
        string short = query_short();
        set_short("dragon-marked " +short);
        add_adj("dragon-marked");
        add_adj("marked");

        if(gHand != W_BOTH) 
        {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is a crude spear, its tip fire-hardened " +
                      "to a point... an effective way of swiftly fashioning " +
                      "such a weapon at the cost of brittleness. It is " +
                      "branded with the mark of a " +faction+ " dragon, " +
                      "and is commonly wielded by their new recruits " +
                      "or goblinoid forces.\n";
                  break;
               case 1: 
                  long = "This is a one-handed hunting spear " +
                      "approximately two metres in length with " +
                      "a shaft made from ash and a sharp iron head. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and is standard-issue for the forces of " +
                      "that dragonarmy.\n";
                  break;
               case 2: 
                  long = "This is a one-handed spear approximately two " +
                      "metres in length with a shaft made from ash and " +
                      "a sharp iron head. A heavy crossbar sits just " +
                      "beneath the blade, preventing the spear from " +
                      "penetrating too deeply into its target, allowing " +
                      "for repeated stabbing with little risk of the " +
                      "weapon getting stuck in an opponent. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and is standard-issue for the forces of " +
                      "that dragonarmy.\n";
                  break;
               case 3: 
                  long = "This is a one-handed spear approximately " +
                      "two metres in length with " +
                      "a shaft made from ash and a sharp steel head. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               case 4: 
                  long = "This is a one-handed spear approximately two " +
                      "metres in length with a shaft made from ash and " +
                      "a sharp steel head. A heavy crossbar sits just " +
                      "beneath the blade, preventing the spear from " +
                      "penetrating too deeply into its target, allowing " +
                      "for repeated stabbing with little risk of the " +
                      "weapon getting stuck in an opponent. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               case 5: 
                  long = "This is a military half-pike forged by the " +
                      "weaponsmiths of Sanction. At under seven feet in " +
                      "length, this polearm is able to be effectively " +
                      "wielded in one hand, with its elaborately carved " +
                      "steel blade capable of piercing through metal " +
                      "armours. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               default:
                  long = "This is a military half-pike forged by the " +
                      "weaponsmiths of Sanction. At under seven feet in " +
                      "length, this polearm is able to be effectively " +
                      "wielded in one hand, with its elaborately carved " +
                      "steel blade capable of piercing through metal " +
                      "armours. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
               case 0..2: 
                   long = "This is a two-handed long-spear forged by the " +
                       "weaponsmiths of Sanction, capped with a sharp " +
                       "iron blade. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and is standard-issue for dragonarmy " +
                       "forces.\n";
                   break;
               case 3: 
                   long = "This is an awl pike forged by the " +
                       "weaponsmiths of Sanction. Over sixteen feet in " +
                       "length, this polearm is capped with a leaf-shaped " +
                       "iron head. It is branded with the mark of a " +
                       faction+ " dragon, and is standard-issue for " +
                       "dragonarmy forces.\n";
                   break;
               case 4: 
                   long = "This is a pike forged by the " +
                       "weaponsmiths of Sanction. Over sixteen feet in " +
                       "length, this polearm is capped with a leaf-shaped " +
                       "steel head. It is branded with the " +
                       "mark of a " +faction+ " dragon, and due to the " +
                       "rarity of steel is issued only to that dragonarmy's " +
                       "elite forces.\n";
                   break;
               case 5: 
                   long = "This is a heavy lance made from toughened " +
                       "ash, with a long steel head affixed to its end by " +
                       "the weaponsmiths of Sanction. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and due to the rarity of steel is issued " +
                       "only to that dragonarmy's officer ranks and elite " +
                       "forces.\n";
                   break;
               default:
                   long = "This is a heavy lance made from toughened " +
                       "ash, with a long steel head affixed to its end by " +
                       "the weaponsmiths of Sanction. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and due to the rarity of steel is issued " +
                       "only to that dragonarmy's officer ranks and elite " +
                       "forces.\n";
                   break;
            }
        }
    }
    else if(faction == "knights")
    {
        string short = query_short();

        if(gHand != W_BOTH) 
        {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is a crude spear, its tip fire-hardened " +
                      "to a point... an effective way of swiftly fashioning " +
                      "such a weapon at the cost of brittleness.\n";
                  break;
               case 1: 
                  long = "This is a one-handed hunting spear " +
                      "approximately two metres in length with " +
                      "a shaft made from ash and a sharp iron head.\n";
                  break;
               case 2: 
                  long = "This is a one-handed spear approximately two " +
                      "metres in length with a shaft made from ash and " +
                      "a sharp iron head. A heavy crossbar sits just " +
                      "beneath the blade, preventing the spear from " +
                      "penetrating too deeply into its target, allowing " +
                      "for repeated stabbing with little risk of the " +
                      "weapon getting stuck in an opponent. It is branded " +
                      "with the mark of the Solamnian knighthood, and is " +
                      "standard-issue for their militia and knights.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               case 3: 
                  long = "This is a one-handed spear approximately " +
                      "two metres in length with a shaft made from ash " +
                      "and a sharp steel head. It has been forged by " +
                      "smiths from Vingaard Keep, and is engraved with " +
                      "symbols of the Solamnian knighthood.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               case 4: 
                  long = "This is a one-handed spear approximately two " +
                      "metres in length with a shaft made from ash and " +
                      "a sharp steel head. A heavy crossbar sits just " +
                      "beneath the blade, preventing the spear from " +
                      "penetrating too deeply into its target, allowing " +
                      "for repeated stabbing with little risk of the " +
                      "weapon getting stuck in an opponent. It has been " +
                      "forged by smiths from Vingaard Keep, and is " +
                      "beautifully engraved with symbols of the " +
                      "Solamnian knighthood.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               case 5: 
                  long = "This is a military half-pike forged by the " +
                      "dwarven weaponsmiths of Garnet. At under seven feet " +
                      "in length, this polearm is able to be effectively " +
                      "wielded in one hand, with its elaborately carved " +
                      "steel blade capable of piercing through metal " +
                      "armours.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               default:
                  long = "This is a military half-pike forged by the " +
                      "dwarven weaponsmiths of Garnet. At under seven feet " +
                      "in length, this polearm is able to be effectively " +
                      "wielded in one hand, with its elaborately carved " +
                      "steel blade capable of piercing through metal " +
                      "armours.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..2: 
                    long = "This is a two-handed long-spear forged by the " +
                        "weaponsmiths of Solanthus, capped with a sharp " +
                        "iron blade. It is branded with the mark of the " +
                        "Solamnian knighthood, and is standard-issue " +
                        "for their militia and knights.\n";
                    break;
                case 3: 
                    long = "This is an awl pike forged by the weaponsmiths " +
                       "of Vingaard Keep. Over sixteen feet in length, " +
                       "this polearm is capped with a leaf-shaped " +
                       "iron head engraved with symbols of the " +
                       "Solamnian knighthood.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                    break;
                case 4: 
                    long = "This is a pike forged by the weaponsmiths " +
                       "of Vingaard Keep. Over sixteen feet in length, " +
                       "this polearm is capped with a leaf-shaped " +
                       "steel head and is engraved with symbols " +
                       "of the Solamnian knighthood.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                    break;
                case 5: 
                  long = "This is a heavy lance made from toughened " +
                      "ash, with a long steel head affixed to its end by " +
                      "the dwarven weaponsmiths of Garnet. Its shaft " +
                      "is beautifully engraved with the symbols of " +
                      "the Solamnian knighthood - the thorny stem of a " +
                      "rose winding down to a circular vamplate shaped " +
                      "to resemble a kingfisher in flight. No doubt " +
                      "once the weapon of a highly ranked knight.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               default:
                  long = "This is a heavy lance made from toughened " +
                      "ash, with a long steel head affixed to its end by " +
                      "the dwarven weaponsmiths of Garnet. Its shaft " +
                      "is beautifully engraved with the symbols of " +
                      "the Solamnian knighthood - the thorny stem of a " +
                      "rose winding down to a circular vamplate shaped " +
                      "to resemble a kingfisher in flight. No doubt " +
                      "once the weapon of a highly ranked knight.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                    break;
            }
        }
    }
    else
    {
        string short = query_short();

        if(gHand != W_BOTH) 
        {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is a crude spear, its tip fire-hardened " +
                      "to a point... an effective way of swiftly fashioning " +
                      "such a weapon at the cost of brittleness.\n";
                  break;
               case 1: 
                  long = "This is a one-handed hunting spear " +
                      "approximately two metres in length with " +
                      "a shaft made from ash and a sharp iron head.\n";
                  break;
               case 2: 
                  long = "This is a one-handed spear approximately two " +
                      "metres in length with a shaft made from ash and " +
                      "a sharp iron head. A heavy crossbar sits just " +
                      "beneath the blade, preventing the spear from " +
                      "penetrating too deeply into its target, allowing " +
                      "for repeated stabbing with little risk of the " +
                      "weapon getting stuck in an opponent.\n";
                  break;
               case 3: 
                  long = "This is a one-handed spear approximately " +
                      "two metres in length with a shaft made from ash " +
                      "and a sharp steel head.\n";
                      set_short("one-handed " +short);
                      add_adj("one-handed");
                  break;
               case 4: 
                  long = "This is a one-handed spear approximately two " +
                      "metres in length with a shaft made from ash and " +
                      "a sharp steel head. A heavy crossbar sits just " +
                      "beneath the blade, preventing the spear from " +
                      "penetrating too deeply into its target, allowing " +
                      "for repeated stabbing with little risk of the " +
                      "weapon getting stuck in an opponent.\n";
                  break;
               case 5: 
                  long = "This is a military half-pike. Seven feet in " +
                      "length this polearm is able to be effectively " +
                      "wielded in one hand, with an elaborately carved " +
                      "steel blade capable of piercing through metal " +
                      "armours.\n";
                  break;
               default:
                  long = "This is a military half-pike. Seven feet in " +
                      "length this polearm is able to be effectively " +
                      "wielded in one hand, with an elaborately carved " +
                      "steel blade capable of piercing through metal " +
                      "armours.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..2: 
                    long = "This is a two-handed long-spear capped " +
                        "with a sharp iron blade forged " +
                        "from ore mined in the Kharolis mountain " +
                        "ranges. It is unadorned, and is a practical " +
                        "weapon common with mercenaries and soldiers " +
                        "throughout Krynn.\n";
                    break;
                case 3: 
                    long = "This is an awl pike. Over sixteen feet in " +
                       "length, this polearm is capped with a leaf-shaped " +
                       "iron head.\n";
                    break;
                case 4: 
                    long = "This is an awl pike. Over sixteen feet in " +
                       "length, this polearm is capped with a leaf-shaped " +
                       "steel head.\n";
                    break;
                case 5: 
                    long = "This is a heavy lance made from toughened " +
                       "ash, with a long steel head affixed to its end.\n";
                    break;
                default:
                    long = "This is a heavy lance made from toughened " +
                       "ash, with a long steel head affixed to its end.\n";
                    break;
             }
        }
    }

    return long;
}

public void
create_warfare_weapon()
{
    if ( !gLevel )
        set_weapon_level();
}

public void
update_warfare_weapon()
{
    set_name("polearm");
    set_short(warfare_weapon_short());
    set_long(warfare_weapon_long());
      
    set_hit(gHit);
    set_pen(gPen);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(gHand);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(gHit, gPen) + random(20) - 10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(gPen, W_POLEARM) +
        random(50) - 25);
        
    if (objectp(query_wielded()))
        query_wielded()->update_weapon(this_object());
}

void
create_weapon()
{
    create_warfare_weapon();
    update_warfare_weapon();
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" + gLevel + "&&" + 
        gHit + "&&" + gPen + "&&" + gHand + "&&" + gFaction;
}

void 
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    gLevel = atoi(a[1]);
    gHit = atoi(a[2]);
    gPen = atoi(a[3]);
    gHand = atoi(a[4]);
    gFaction = (a[5]);
    init_wep_recover(a[0]);
    update_warfare_weapon();
}