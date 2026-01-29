/* 
 * Warfare hammer standard file for the various factions.
 *
 * Arman Kharas, Sept 2018
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
              short = "wooden club";
              add_name("club");
              add_adj("wooden");
              break;
           case 1: 
              short = "light mace";
              add_name("mace");
              add_adj("light");
              remove_name("club");
              remove_adj("wooden");
              break;
           case 2: 
              short = "iron hammer";
              add_name("hammer");
              add_adj("iron");
              remove_name("club");
              remove_adj("wooden");
              break;
           case 3: 
              short = "iron mace";
              add_name("mace");
              add_adj("iron");
              add_adj("heavy");
              remove_name("club");
              remove_adj("wooden");
              break;
           case 4: 
              short = "steel mace";
              add_name("mace");
              add_adj("steel");
              remove_name("club");
              remove_adj("wooden");
              break;
           case 5: 
              short = "steel heavy mace";
              add_name("mace");
              add_adj("steel");
              add_adj("heavy");
              remove_name("club");
              remove_adj("wooden");
              break;
           default:
              short = "steel heavy mace";
              add_name("mace");
              add_adj("steel");
              add_adj("heavy");
              remove_name("club");
              remove_adj("wooden");
              break;
        }
    }
    else
    {
        switch(gLevel)
        {  
           case 0..3: 
              short = "iron maul";
              add_name("maul");
              add_adj("iron");
              break;
           case 4: 
              short = "iron warhammer";
              add_name("warhammer");
              add_adj("iron");
              remove_name("maul");
              remove_adj("iron");
              break;
           case 5: 
              short = "great maul";
              add_name("maul");
              add_adj("steel");
              add_adj("great");
              remove_adj("iron");
              break;
           default:
              short = "steel warhammer";
              add_name("warhammer");
              add_adj("steel");
              remove_name("maul");
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
                  long = "This is a simple wooden club. It is " +
                      "branded with the mark of a " +faction+ " dragon, " +
                      "and is commonly wielded by their new recruits " +
                      "or goblinoid forces.\n";
                  break;
               case 1: 
                  long = "This is a small club made from iron. It is branded " +
                      "with the mark of a " +faction+ " dragon, and is " +
                      "standard-issue for the forces of " +
                      "that dragonarmy.\n";
                  break;
               case 2: 
                  long = "This is a one-handed hammer with a small iron " +
                      "head capable of crushing armours. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and is standard-issue for the forces of " +
                      "that dragonarmy.\n";
                  break;
               case 3: 
                  long = "This is a one-handed battle mace with a broad " +
                      "iron head mounted on the end of a stout four foot pole. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and is standard-issue for the forces of " +
                      "that dragonarmy.\n";
                  break;
               case 4: 
                  long = "This is a one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               case 5: 
                  long = "This is a heavy one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole. " +
                      "It is branded with the mark of a " +faction+ 
                      " dragon, and due to the rarity of steel is issued " +
                      "only to that dragonarmy's officer ranks and elite " +
                      "forces.\n";
                  break;
               default:
                  long = "This is a heavy one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole. " +
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
                   long = "This is a two-handed iron maul forged by the " +
                       "weaponsmiths of Sanction. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and is standard-issue for dragonarmy " +
                       "forces.\n";
                   break;
               case 3: 
                   long = "This is a warhammer forged by the weaponsmiths " +
                       "of Sanction. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a large iron head attached to it that would " +
                       "easily drop a horse. It is branded with the mark of a " +
                       faction+ " dragon, and is standard-issue for " +
                       "dragonarmy forces.\n";
                   break;
               case 4: 
                   long = "This is a two-handed great maul forged by the " +
                       "weaponsmiths of Sanction, with a huge head of steel " +
                       "attached to a long pole. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and due to the rarity of steel is issued " +
                       "only to that dragonarmy's officer ranks and elite " +
                       "forces.\n";
                   break;
               case 5: 
                   long = "This is a warhammer forged by the weaponsmiths " +
                       "of Sanction. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a large steel head attached to it that would " +
                       "easily drop a horse. It is branded with the mark of a " +
                       faction+ 
                       " dragon, and due to the rarity of steel is issued " +
                       "only to that dragonarmy's officer ranks and elite " +
                       "forces.\n";
                   break;
               default:
                   long = "This is a warhammer forged by the weaponsmiths " +
                       "of Sanction. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a large steel head attached to it that would " +
                       "easily drop a horse. It is branded with the mark of a " +
                       faction+ 
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
                  long = "This is a simple wooden club.\n";
                  break;
               case 1: 
                  long = "This is a small club made of iron.\n";
                  break;
               case 2: 
                  long = "This is a one-handed hammer with a small iron " +
                      "head capable of crushing armours.\n";
                  break;
               case 3: 
                  long = "This is a one-handed battle mace with a broad " +
                      "iron head mounted on the end of a stout four foot pole. " +
                      "It has been forged " +
                      "by smiths from Vingaard Keep, and is engraved " +
                      "with symbols of the Solamnian knighthood.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               case 4: 
                  long = "This is a one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole. " +
                      "It has been forged by smiths from Vingaard " +
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
        else
        {
            switch(gLevel)
            {  
               case 0..2: 
                   long = "This is a two-handed iron maul forged by the " +
                       "weaponsmiths of Palanthas.\n";
                   break;
               case 3: 
                   long = "This is a warhammer forged by the weaponsmiths " +
                       "of Palanthas. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a large iron head attached to it that would " +
                       "easily drop a horse.\n";
                   break;
               case 4: 
                   long = "This is a two-handed great maul forged by the " +
                       "weaponsmiths of Vingaard Keep, with a huge head of steel " +
                       "attached to a long pole. It is beautifully tooled " +
                       "with the symbols of the Knights of Solamnia.\n";
                   break;
               case 5: 
                   long = "This is a warhammer forged by the dwarven weaponsmiths " +
                       "of Garnet. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a large steel head attached to it that would " +
                       "easily drop a horse. It is beautifully tooled with " +
                       "the symbols of the Knights of Solamnia.\n";
                   break;
               default:
                   long = "This is a warhammer forged by the dwarven weaponsmiths " +
                       "of Garnet. While its pole is short for a " +
                       "two-handed weapon at only five feet in length, " +
                       "it has a large steel head attached to it that would " +
                       "easily drop a horse. It is beautifully tooled with " +
                       "the symbols of the Knights of Solamnia.\n";
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
                  long = "This is a simple but well-loved wooden club.\n";
                  break;
               case 1: 
                  long = "This is a small club made in dwarven style from iron.\n";
                  break;
               case 2: 
                  long = "This is a one-handed hammer with a small iron " +
                      "head capable of crushing armours.\n";
                  break;
               case 3: 
                  long = "This is a one-handed battle mace with a broad " +
                      "iron head mounted on the end of a stout four foot pole. " +
                      "It has been forged " +
                      "by dwarven smiths from Iron Delving, and is engraved " +
                      "with dwarven war symbols.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
               case 4: 
                  long = "This is a one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole. " +
                      "It has been forged " +
                      "by dwarven smiths from Iron Delving, and is engraved " +
                      "with dwarven war symbols.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
               case 5: 
                  long = "This is a heavy one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole, " +
                      "masterfully forged by the dwarven weaponsmiths of Iron " +
                      "Delving.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
               default:
                  long = "This is a heavy one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole, " +
                      "masterfully forged by the dwarven weaponsmiths of Iron " +
                      "Delving.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
               case 0..2: 
                   long = "This is a two-handed iron maul forged by the " +
                       "dwarven weaponsmiths of Iron Delving.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                   break;
               case 3: 
                   long = "This is a warhammer forged by the dwarven " +
                       "weaponsmiths of Iron Delving. While its pole is short " +
                       "for a two-handed weapon at only five feet in length, " +
                       "it has a large iron head attached to it that would " +
                       "easily drop a horse.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                   break;
               case 4: 
                   long = "This is a two-handed great maul forged by the " +
                       "dwarven weaponsmiths of Iron Delving, with a huge " +
                       "head of steel attached to a long pole.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                   break;
               case 5: 
                   long = "This is a warhammer beautifully forged by the dwarven " +
                       "weaponsmiths of Iron Delving. While its pole is short " +
                       "for a two-handed weapon at only five feet in length, " +
                       "it has a large steel head attached to it that would " +
                       "easily drop a horse.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
                   break;
               default:
                   long = "This is a warhammer beautifully forged by the dwarven " +
                       "weaponsmiths of Iron Delving. While its pole is short " +
                       "for a two-handed weapon at only five feet in length, " +
                       "it has a large steel head attached to it that would " +
                       "easily drop a horse.\n";
                      set_short("dwarven " +short);
                      add_adj("dwarven");
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
                  long = "This is a simple wooden club.\n";
                  break;
               case 1: 
                  long = "This is a small club made from iron.\n";
                  break;
               case 2: 
                  long = "This is a one-handed hammer with a small iron " +
                      "head capable of crushing armours.\n";
                  break;
               case 3: 
                  long = "This is a one-handed battle mace with a broad " +
                      "iron head mounted on the end of a stout four foot pole.\n";
                  break;
               case 4: 
                  long = "This is a one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole.\n";
                  break;
               case 5: 
                  long = "This is a heavy one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole.\n";
                  break;
               default:
                  long = "This is a heavy one-handed battle mace with a broad " +
                      "steel head mounted on the end of a stout four foot pole.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
               case 0..2: 
                   long = "This is a two-handed maul forged with iron.\n";
                   break;
               case 3: 
                   long = "This is a large iron warhammer. While its pole is short " +
                       "for a two-handed weapon at only five feet in length, " +
                       "it has a large iron head attached to it that would " +
                       "easily drop a horse.\n";
                   break;
               case 4: 
                   long = "This is a two-handed great maul with a huge " +
                       "head of steel attached to a long pole.\n";
                   break;
               case 5: 
                   long = "This is a warhammer beautifully forged. While its " +
                       "pole is short " +
                       "for a two-handed weapon at only five feet in length, " +
                       "it has a large steel head attached to it that would " +
                       "easily drop a horse.\n";
                   break;
               default:
                   long = "This is a warhammer beautifully forged. While its " +
                       "pole is short " +
                       "for a two-handed weapon at only five feet in length, " +
                       "it has a large steel head attached to it that would " +
                       "easily drop a horse.\n";
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
    set_name("club");
    set_short(warfare_weapon_short());
    set_long(warfare_weapon_long());
      
    set_hit(gHit);
    set_pen(gPen);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
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
