/* 
 * Warfare sword standard file for the various factions.
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
    
    (gLevel < 0) ? 0 : gLevel;
    (gLevel > 5) ? 5 : gLevel;

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
              short = "iron shortsword";
              add_name("shortsword");
              add_adj("iron");
              break;
           case 1: 
              short = "iron longsword";
              add_name("longsword");
              add_adj("iron");
              remove_name("shortsword");
              break;
           case 2: 
              short = "iron broadsword";
              add_name("broadsword");
              add_adj("iron");
              remove_name("shortsword");
              break;
           case 3: 
              short = "steel longsword";
              add_name("longsword");
              add_adj("steel");
              remove_name("shortsword");
              remove_adj("iron");
              break;
           case 4: 
              short = "steel broadsword";
              add_name("broadsword");
              add_adj("steel");
              remove_name("shortsword");
              remove_adj("iron");
              break;
           case 5: 
              short = "steel flamberge";
              add_name("flamberge");
              add_adj("steel");
              remove_name("shortsword");
              remove_adj("iron");
              break;
           default:
              short = "steel flamberge";
              add_name("flamberge");
              add_adj("steel");
              remove_name("shortsword");
              remove_adj("iron");
              break;
        }
    }
    else
    {
        switch(gLevel)
        {  
           case 0..2: 
              short = "iron flambard";
              add_name("flambard");
              add_adj("iron");
              break;
           case 3: 
              short = "steel bastardsword";
              add_name("bastardsword");
              add_adj("steel");
              remove_name("flambard");
              remove_adj("iron");
              break;
           case 4: 
              short = "steel two-handed sword";
              add_adj("steel");
              add_adj("two-handed");
              remove_name("flambard");
              remove_adj("iron");
              break;
           case 5: 
              short = "steel greatsword";
              add_name("greatsword");
              add_adj("steel");
              remove_name("flambard");
              remove_adj("iron");
              break;
           default:
              short = "steel greatsword";
              add_name("greatsword");
              add_adj("steel");
              remove_name("flambard");
              remove_adj("iron");
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
                  long = "This is an iron shortsword forged by the " +
                      "weaponsmiths of Sanction. It is branded with the " +
                      "mark of a " +faction+ " dragon, and is standard-" +
                      "issue for the forces of that dragonarmy.\n";
                  break;
               case 1: 
                  long = "This is an iron longsword forged by the " +
                      "weaponsmiths of Sanction. It is branded with the " +
                      "mark of a " +faction+ " dragon, and is standard-" +
                      "issue for the forces of that dragonarmy.\n";
                  break;
               case 2: 
                  long = "This is an iron broadsword forged by the " +
                      "weaponsmiths of Sanction. It is branded with the " +
                      "mark of a " +faction+ " dragon, and is standard-" +
                      "issue for the forces of that dragonarmy.\n";
                  break;
               case 3: 
                  long = "This is a steel longsword forged by the " +
                      "weaponsmiths of Sanction. It is branded with the " +
                      "mark of a " +faction+ " dragon, and due to the " +
                      "rarity of steel is issued only to that dragonarmy's " +
                      "most experienced forces.\n";
                  break;
               case 4: 
                  long = "This is a steel broadsword forged by the " +
                      "weaponsmiths of Sanction. It is branded with the " +
                      "mark of a " +faction+ " dragon, and due to the " +
                      "rarity of steel is issued only to that dragonarmy's " +
                      "elite forces.\n";
                  break;
               case 5: 
                  long = "This is a steel flamberge forged by the " +
                      "weaponsmiths of Sanction. Its undulating blade makes " +
                      "it somewhat difficult to use by all but the most " +
                      "experienced swordsmen, but does cause unpleasant " +
                      "vibrations in the attackers blade when parrying. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               default:
                  long = "This is a steel flamberge forged by the " +
                      "weaponsmiths of Sanction. Its undulating blade makes " +
                      "it somewhat difficult to use by all but the most " +
                      "experienced swordsmen, but does cause unpleasant " +
                      "vibrations in the attackers blade when parrying. " +
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
                   long = "This is a two-handed iron flambard forged by the " +
                       "weaponsmiths of Sanction. Its undulating blade makes " +
                       "it somewhat difficult to use by all but the most " +
                       "experienced swordsmen, but does cause unpleasant " +
                       "vibrations in the attackers blade when parrying. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and is standard-issue for dragonarmy " +
                       "forces.\n";
                   break;
               case 3: 
                   long = "This is a steel bastardsword forged by the " +
                       "weaponsmiths of Sanction. It is branded with the " +
                       "mark of a " +faction+ " dragon, and due to the " +
                       "rarity of steel is issued only to that dragonarmy's " +
                       "most experienced forces.\n";
                   break;
               case 4: 
                   long = "This is a steel two-handed sword forged by the " +
                       "weaponsmiths of Sanction. It is branded with the " +
                       "mark of a " +faction+ " dragon, and due to the " +
                       "rarity of steel is issued only to that dragonarmy's " +
                       "elite forces.\n";
                   break;
               case 5: 
                   long = "This is a steel greatsword forged by the " +
                       "weaponsmiths of Sanction. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and due to the rarity of steel is issued " +
                       "only to that dragonarmy's officer ranks and elite " +
                       "forces.\n";
                   break;
               default:
                   long = "This is a steel greatsword forged by the " +
                       "weaponsmiths of Sanction. " +
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
        set_short("solamnic " +short);
        add_adj("solamnic");

        if(gHand != W_BOTH) 
        {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is an iron shortsword forged from ore " +
                      "mined in the Vingaard Mountains and forged " +
                      "by smiths of Solanthus. It is branded with the " +
                      "mark of the Solamnian knighthood, and is " +
                      "standard-issue for their militia and knights.\n";
                  break;
               case 1: 
                  long = "This is an iron longsword forged from ore " +
                      "mined in the Vingaard Mountains and forged " +
                      "by smiths of Solanthus. It is branded with the " +
                      "mark of the Solamnian knighthood, and is " +
                      "standard-issue for their militia and knights.\n";
                  break;
               case 2: 
                  long = "This is an iron broadsword forged from ore " +
                      "mined in the Vingaard Mountains and forged " +
                      "by smiths of Solanthus. It is branded with the " +
                      "mark of the Solamnian knighthood, and is " +
                      "standard-issue for their militia and knights.\n";
                  break;
               case 3: 
                  long = "This is a steel longsword forged by smiths " +
                      "from Vingaard Keep, and is engraved with symbols " +
                      "of the Solamnian knighthood.\n";
                  break;
               case 4: 
                  long = "This is a steel broadsword forged by smiths " +
                      "from Vingaard Keep, and is beautifully engraved " +
                      "with symbols of the Solamnian knighthood.\n";
                  break;
               case 5: 
                  long = "This is a steel flamberge masterfully forged " +
                      "by dwarven weaponsmiths of Garnet. Its " +
                      "undulating blade is engraved with the symbols of " +
                      "the Solamnian knighthood - the thorny stem of a " +
                      "rose winding down to a kingfisher crossguard. " +
                      "No doubt once the weapon of a highly ranked " +
                      "knight.\n";
                  break;
               default:
                  long = "This is a steel flamberge masterfully forged " +
                      "by dwarven weaponsmiths of Garnet. Its " +
                      "undulating blade is engraved with the symbols of " +
                      "the Solamnian knighthood - the thorny stem of a " +
                      "rose winding down to a kingfisher crossguard. " +
                      "No doubt once the weapon of a highly ranked " +
                      "knight.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..2: 
                    long = "This is a two-handed iron flambard forged " +
                        "from ore mined in the Vingaard Mountains and " +
                        "forged by smiths of Solanthus. It is branded with " +
                        "the mark of the Solamnian knighthood, and is " +
                        "standard-issue for their militia and knights.\n";
                    break;
                case 3: 
                    long = "This is a steel bastardsword forged by " +
                        "smiths from Vingaard Keep, and is engraved with " +
                        "symbols of the Solamnian knighthood.\n";
                    break;
                case 4: 
                    long = "This is a steel two-handed sword forged by " +
                        "smiths from Vingaard Keep, and is engraved with " +
                        "symbols of the Solamnian knighthood.\n";
                    break;
                case 5: 
                    long = "This is a steel greatsword masterfully " +
                        "forged by dwarven weaponsmiths of Garnet. Its " +
                        "undulating blade is engraved with the symbols of " +
                        "the Solamnian knighthood - the thorny stem of a " +
                        "rose winding down to a kingfisher crossguard. " +
                        "No doubt once the weapon of a highly ranked " +
                        "knight.\n";
                    break;
                default:
                    long = "This is a steel greatsword masterfully " +
                        "forged by dwarven weaponsmiths of Garnet. Its " +
                        "undulating blade is engraved with the symbols of " +
                        "the Solamnian knighthood - the thorny stem of a " +
                        "rose winding down to a kingfisher crossguard. " +
                        "No doubt once the weapon of a highly ranked " +
                        "knight.\n";
                    break;
            }
        }
    }
    else
    {
        if(gHand != W_BOTH) 
        {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is an iron shortsword forged from ore " +
                      "mined in the Kharolis mountain ranges. It is " +
                      "unadorned, and is a practical weapon common " +
                      "with travellers and brigands throughout " +
                      "Krynn.\n";
                  break;
               case 1: 
                  long = "This is an iron longsword forged from ore " +
                      "mined in the Kharolis mountain ranges. It is " +
                      "unadorned, and is a practical weapon common " +
                      "with mercenaries and soldiers throughout " +
                      "Krynn.\n";
                  break;
               case 2: 
                  long = "This is an iron broadsword forged from ore " +
                      "mined in the Kharolis mountain ranges. It is " +
                      "unadorned, and is a practical weapon common " +
                      "with mercenaries and soldiers throughout " +
                      "Krynn.\n";
                  break;
               case 3: 
                  long = "This is a steel longsword, unadorned and of " +
                      "unknown origin. With steel being a rare " +
                      "commodity in Krynn since the Cataclysm, this " +
                      "sort of blade would be carried by the career " +
                      "adventurer or experienced warrior.\n";
                  break;
               case 4: 
                  long = "This is a steel broadsword, unadorned and of " +
                      "unknown origin. With steel being a rare " +
                      "commodity in Krynn since the Cataclysm, this " +
                      "sort of blade would be carried by the career " +
                      "adventurer or soldier.\n";
                  break;
               case 5: 
                  long = "This is a steel flamberge masterfully forged " +
                      "by a weaponsmith of unknown origin. Its undulating " +
                      "blade makes it somewhat difficult to use by all " +
                      "but the most experienced swordsmen, but does " +
                      "cause unpleasant vibrations in the attackers " +
                      "blade when parrying.\n";
                  break;
               default:
                  long = "This is a steel flamberge masterfully forged " +
                      "by a weaponsmith of unknown origin. Its undulating " +
                      "blade makes it somewhat difficult to use by all " +
                      "but the most experienced swordsmen, but does " +
                      "cause unpleasant vibrations in the attackers " +
                      "blade when parrying.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..2: 
                    long = "This is a two-handed iron flambard forged " +
                        "from ore mined in the Kharolis mountain " +
                        "ranges. It is unadorned, and is a practical " +
                        "weapon common with mercenaries and soldiers " +
                        "throughout Krynn.\n";
                    break;
                case 3: 
                    long = "This is a steel bastardsword, unadorned " +
                        "and of unknown origin. With steel being a rare " +
                        "commodity in Krynn since the Cataclysm, this " +
                        "sort of blade would be carried by the career " +
                        "adventurer or soldier.\n";
                    break;
                case 4: 
                    long = "This is a steel two-handed sword, unadorned " +
                        "and of unknown origin. With steel being a rare " +
                        "commodity in Krynn since the Cataclysm, this " +
                        "sort of blade would be carried by the career " +
                        "adventurer or experienced warrior.\n";
                    break;
                case 5: 
                    long = "This is a steel greatsword masterfully " +
                        "forged by a weaponsmith of unknown origin. " +
                        "Massive in size and incredibly sharp, you " +
                        "have no doubt it would cause carnage on " +
                        "the battlefield.\n";
                    break;
                default:
                    long = "This is a steel greatsword masterfully " +
                        "forged by a weaponsmith of unknown origin. " +
                        "Massive in size and incredibly sharp, you " +
                        "have no doubt it would cause carnage on " +
                        "the battlefield.\n";
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
    set_name("sword");
    add_adj("metal");
    set_short(warfare_weapon_short());
    set_long(warfare_weapon_long());
      
    set_hit(gHit);
    set_pen(gPen);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(gHand);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(gHit, gPen) + random(20) - 10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(gPen, W_SWORD) +
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