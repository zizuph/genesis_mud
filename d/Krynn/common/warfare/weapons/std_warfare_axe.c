/* 
 * Warfare axe standard file for the various factions.
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
set_weapon_level(int level = 0, int hand = W_BOTH, string faction = "free")
{
    if ( !level )
        gLevel = 0;
    else
        gLevel = level;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 5)
        gLevel = 5;

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
              short = "hatchet";
              add_name("hatchet");
              break;
           case 1: 
              short = "hand axe";
              add_name("axe");
              add_adj("hand");
              remove_name("hatchet");
              break;
           case 2: 
              short = "broad axe";
              add_name("axe");
              add_adj("broad");
              remove_name("hatchet");
              break;
           case 3: 
              short = "iron battle axe";
              add_name("battleaxe");
              add_adj("iron");
              add_adj("battle");
              remove_name("hatchet");
              break;
           case 4: 
              short = "steel broad axe";
              add_name("axe");
              add_adj("broad");
              add_adj("steel");
              remove_name("hatchet");
              break;
           case 5: 
              short = "steel battle axe";
              add_name("battleaxe");
              add_adj("iron");
              add_adj("battle");
              remove_name("hatchet");
              break;
           default:
              short = "steel battle axe";
              add_name("battleaxe");
              add_adj("iron");
              add_adj("battle");
              remove_name("hatchet");
              break;
        }
    }
    else
    {
        switch(gLevel)
        {  
           case 0..3: 
              short = "iron pollaxe";
              add_name("pollaxe");
              add_adj("iron");
              break;
           case 4: 
              short = "iron greataxe";
              add_name("greataxe");
              add_adj("iron");
              add_adj("great");
              remove_name("pollaxe");
              break;
           case 5: 
              short = "steel greataxe";
              add_name("greataxe");
              add_adj("steel");
              add_adj("great");
              remove_name("pollaxe");
              remove_adj("iron");
              break;
           default:
              short = "steel greataxe";
              add_name("greataxe");
              add_adj("steel");
              add_adj("great");
              remove_name("pollaxe");
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
                  long = "This is a simple hatchet. It is " +
                      "branded with the mark of a " +faction+ " dragon, " +
                      "and is commonly wielded by their new recruits " +
                      "or goblinoid forces.\n";
                  break;
               case 1: 
                  long = "This is a one-handed hand-axe with a sharp " +
                      "blade of iron mounted on a wooden haft. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and is standard-issue for the forces of " +
                      "that dragonarmy.\n";
                  break;
               case 2: 
                  long = "This is a one-handed axe with a broad iron " +
                      "head capable of slicing through thick armours. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and is standard-issue for the forces of " +
                      "that dragonarmy.\n";
                  break;
               case 3: 
                  long = "This is a one-handed battle axe with a single " +
                      "edged trumpet-shaped iron blade mounted on the " +
                      "end of a stout four foot pole. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               case 4: 
                  long = "This is a one-handed broad axe with a single " +
                      "steel blade mounted on the end of a four foot pole." +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               case 5: 
                  long = "This is a one-handed battle axe with a double " +
                      "bladed trumpet-shaped steel blade mounted on the " +
                      "end of a stout four foot pole. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               default:
                  long = "This is a one-handed battle axe with a double " +
                      "bladed trumpet-shaped steel blade mounted on the " +
                      "end of a stout four foot pole." +
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
               case 0..3: 
                   long = "This is a two-handed pollaxe forged by the " +
                       "weaponsmiths of Sanction, consisting of a two " +
                       "metre pole capped with a sharp iron blade. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and is standard-issue for dragonarmy " +
                       "forces.\n";
                   break;
               case 4: 
                   long = "This is a greataxe forged by the weaponsmiths " +
                       "of Sanction. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a long cleaver-type iron blade attached " +
                       "to it. It is branded with the mark of a " +
                       faction+ " dragon, and is standard-issue for " +
                       "dragonarmy forces.\n";
                   break;
               case 5: 
                   long = "This is a greataxe forged by the weaponsmiths " +
                       "of Sanction. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a long cleaver-type steel blade attached " +
                       "to it. It is branded with the mark of a " +faction+ 
                       " dragon, and due to the rarity of steel is issued " +
                       "only to that dragonarmy's officer ranks and elite " +
                       "forces.\n";
                   break;
               default:
                   long = "This is a greataxe forged by the weaponsmiths " +
                       "of Sanction. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a long cleaver-type steel blade attached " +
                       "to it. It is branded with the mark of a " +faction+ 
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
                  long = "This is a simple hatchet, better suited to " +
                      "chopping wood than the battlefield.\n";
                  break;
               case 1: 
                  long = "This is a one-handed hand-axe with a sharp " +
                      "blade of iron mounted on a wooden haft.\n";
                  break;
               case 2: 
                  long = "This is a one-handed axe with a broad iron " +
                      "head capable of slicing through thick armours.\n";
                  break;
               case 3: 
                  long = "This is a one-handed battle axe with a single " +
                      "edged trumpet-shaped iron blade mounted on the " +
                      "end of a stout four foot pole. It has been forged " +
                      "by smiths from Vingaard Keep, and is engraved " +
                      "with symbols of the Solamnian knighthood.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               case 4: 
                  long = "This is a one-handed broad axe with a single " +
                      "steel blade mounted on the end of a four foot " +
                      "pole. It has been forged by smiths from Vingaard " +
                      "Keep, and is beautifully engraved with symbols " +
                      "of the Solamnian knighthood.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               case 5: 
                  long = "This is a one-handed battle axe with a double " +
                      "bladed trumpet-shaped steel blade mounted on the " +
                      "end of a stout four foot pole, masterfully " +
                      "forged by the dwarven weaponsmiths of Garnet.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               default:
                  long = "This is a one-handed battle axe with a double " +
                      "bladed trumpet-shaped steel blade mounted on the " +
                      "end of a stout four foot pole, masterfully " +
                      "forged by the dwarven weaponsmiths of Garnet.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
            }
        }
    }
    else if(faction == "neidar")
    {
        string short = query_short();

        if(gHand != W_BOTH) 
        {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is a simple hatchet, better suited to " +
                      "chopping wood than the battlefield.\n";
                  break;
               case 1: 
                  long = "This is a one-handed hand-axe with a sharp " +
                      "blade of iron mounted on a wooden haft.\n";
                  break;
               case 2: 
                  long = "This is a one-handed axe with a broad iron " +
                      "head capable of slicing through thick armours.\n";
                  break;
               case 3: 
                  long = "This is a one-handed battle axe with a single " +
                      "edged trumpet-shaped iron blade mounted on the " +
                      "end of a stout four foot pole. It has been forged " +
                      "by dwarven smiths from Iron Delving, and is engraved " +
                      "with dwarven war symbols.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
               case 4: 
                  long = "This is a one-handed broad axe with a single " +
                      "steel blade mounted on the end of a four foot " +
                      "pole. It has been forged by dwarven smiths from Iron " +
                      "Delving, and is engraved with dwarven war symbols.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
               case 5: 
                  long = "This is a one-handed battle axe with a double " +
                      "bladed trumpet-shaped steel blade mounted on the " +
                      "end of a stout four foot pole, masterfully " +
                      "forged by the dwarven weaponsmiths of Iron Delving.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
               default:
                  long = "This is a one-handed battle axe with a double " +
                      "bladed trumpet-shaped steel blade mounted on the " +
                      "end of a stout four foot pole, masterfully " +
                      "forged by the dwarven weaponsmiths of Iron Delving.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..3: 
                    long = "This is a two-handed pollaxe forged by the " +
                        "dwarven weaponsmiths of Iron Delving, consisting " +
                        "of a two metre pole capped with a sharp iron " +
                        "blade. It is branded with Neidar war runes " +
                        "and is standard-issue for hill dwarf throngs.\n";
                    break;
                case 4: 
                    long = "This is a greataxe forged by the dwarven " +
                        "weaponsmiths of Iron Delving. While its pole is " +
                        "short for a two-handed weapon at only five feet " +
                        "in length, it has a long cleaver-type iron blade " +
                        "attached to it that has been engraved with " +
                        "dwarven war runes.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                    break;
                case 5: 
                    long = "This is a greataxe forged by the dwarven " +
                        "weaponsmiths of Iron Delving. While its pole is " +
                        "short for a two-handed weapon at only five feet " +
                        "in length, it has a long cleaver-type steel blade " +
                        "attached to it that has been engraved with " +
                        "dwarven war runes.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
               default:
                    long = "This is a greataxe forged by the dwarven " +
                        "weaponsmiths of Iron Delving. While its pole is " +
                        "short for a two-handed weapon at only five feet " +
                        "in length, it has a long cleaver-type steel blade " +
                        "attached to it that has been engraved with " +
                        "dwarven war runes.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
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
                  long = "This is a simple hatchet, better suited to " +
                      "chopping wood than the battlefield.\n";
                  break;
               case 1: 
                  long = "This is a one-handed hand-axe with a sharp " +
                      "blade of iron mounted on a wooden haft.\n";
                  break;
               case 2: 
                  long = "This is a one-handed axe with a broad iron " +
                      "head capable of slicing through thick armours.\n";
                  break;
               case 3: 
                  long = "This is a one-handed battle axe with a single " +
                      "edged trumpet-shaped iron blade mounted on the " +
                      "end of a stout four foot pole.\n";
                  break;
               case 4: 
                  long = "This is a one-handed broad axe with a single " +
                      "steel blade mounted on the end of a four foot " +
                      "pole.\n";
                  break;
               case 5: 
                  long = "This is a one-handed battle axe with a double " +
                      "bladed trumpet-shaped steel blade mounted on the " +
                      "end of a stout four foot pole.\n";
                  break;
               default:
                  long = "This is a one-handed battle axe with a double " +
                      "bladed trumpet-shaped steel blade mounted on the " +
                      "end of a stout four foot pole.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..3: 
                    long = "This is a two-handed pollaxe consisting of " +
                        "a two metre pole capped with a sharp iron " +
                        "blade. It is unadorned, and is a practical " +
                        "weapon common with mercenaries and soldiers " +
                        "throughout Krynn.\n";
                    break;
                case 4: 
                    long = "This is an iron greataxe. While its pole " +
                        "is short for a " +
                        "two-handed weapon at only five feet in length, " +
                        "it has a long cleaver-type iron blade attached " +
                        "to it.\n";
                    break;
                case 5: 
                    long = "This is a steel greataxe. While its pole " +
                        "is short for a " +
                        "two-handed weapon at only five feet in length, " +
                        "it has a long cleaver-type steel blade attached " +
                        "to it.\n";
                    break;
                default:
                    long = "This is a steel greataxe. While its pole " +
                        "is short for a " +
                        "two-handed weapon at only five feet in length, " +
                        "it has a long cleaver-type steel blade attached " +
                        "to it.\n";
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
    set_name("axe");
    set_short(warfare_weapon_short());
    set_long(warfare_weapon_long());
      
    set_hit(gHit);
    set_pen(gPen);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(gHand);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(gHit, gPen) + random(20) - 10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(gPen, W_AXE) +
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
