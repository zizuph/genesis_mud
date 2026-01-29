/* 
 * Warfare bow standard file for the various factions.
 *
 * Arman Kharas, Sept 2018
 */
 
inherit "/std/bow";
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
set_weapon_level(int level = 0, int hand = W_BOTH, string faction = "knights")
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
        gFaction = "knights";
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
          gHit = 30;
          gPen = 30;
          break;
       case 1: 
          gHit = 33;
          gPen = 30;
          break;
       case 2: 
          gHit = 33;
          gPen = 33;
          break;
       case 3: 
          gHit = 33;
          gPen = 37;
          break;
       case 4: 
          gHit = 37;
          gPen = 37;
          break;
       case 5: 
          gHit = 40;
          gPen = 40;
          break;
       default:
          gHit = 40;
          gPen = 40;
          break;
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
           default:
              short = "one-handed crossbow";
              add_name("crossbow");
              add_adj("one-handed");
              add_adj("one");
              add_adj("handed");
              break;
        }
    }
    else
    {
        switch(gLevel)
        {  
           case 0..2: 
              short = "short bow";
              add_adj("short");
              break;
           case 3..4: 
              short = "longbow";
              add_name("longbow");
              add_adj("long");
              break;
           case 5: 
              short = "recurve longbow";
              add_name("longbow");
              add_adj("long");
              add_adj("recurve");
              break;
           default:
              short = "recurve longbow";
              add_name("longbow");
              add_adj("long");
              add_adj("recurve");
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

        if(gHand != W_BOTH) 
        {
            switch(gLevel)
            {  
               default:
                  long = "An unusual one-handed crossbow.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
               case 0..2: 
                   long = "This is a standard short bow of just over " +
                       "five feet in length. While it doesn't have the " +
                       "range of a longbow or the power of a recurve bow, " +
                       "it provides an effective ranged attack that can " +
                       "cause chaos to enemy forces.\n";
                   break;
               case 3..4: 
                   long = "This is a longbow made from the reddish-grey " +
                       "black locust tree found in the mountains north " +
                       "of Sanction. Over six feet in length, it is capable " +
                       "of firing arrows at a great distance and with " +
                       "considerable power. It is branded with the mark of a " +
                       faction+ " dragon, and is standard-issue for " +
                       "dragonarmy forces.\n";
                   set_short("dragon-marked " +short);
                   add_adj("dragon-marked");
                   add_adj("marked");
                   break;
               case 5: 
                   long = "This is a recurve longbow masterfully crafted " +
                       "from wood of the black locust tree found in the " +
                       "mountains north of Sanction, laminated together with " +
                       "horn and sinew to provide incredible energy and power. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and is issued " +
                       "only to that dragonarmy's finest marksmen and elite " +
                       "forces.\n";
                   set_short("dragon-marked " +short);
                   add_adj("dragon-marked");
                   add_adj("marked");
                   break;
               default:
                   long = "This is a recurve longbow masterfully crafted " +
                       "from wood of the black locust tree found in the " +
                       "mountains north of Sanction, laminated together with " +
                       "horn and sinew to provide incredible energy and power. " +
                       "It is branded with the mark of a " +faction+ 
                       " dragon, and is issued " +
                       "only to that dragonarmy's finest marksmen and elite " +
                       "forces.\n";
                   set_short("dragon-marked " +short);
                   add_adj("dragon-marked");
                   add_adj("marked");
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
               default:
                  long = "An unusual one-handed crossbow.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..2: 
                   long = "This is a standard short bow of just over " +
                       "five feet in length. While it doesn't have the " +
                       "range of a longbow or the power of a recurve bow, " +
                       "it provides an effective ranged attack that can " +
                       "cause chaos to enemy forces.\n";
                    break;
                case 3..4: 
                   long = "This is a longbow made from yew grown only in " +
                       "the mountains of the isle of Sancrist. Over six feet " +
                       "in length it is capable of firing arrows at a great " +
                       "distance and with considerable power, and is popular with " +
                       "Solamnian marksmen.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                    break;
                case 5: 
                   long = "This is a recurve longbow masterfully crafted " +
                       "from wood of the Ergothian red cedar, laminated together " +
                       "with horn and sinew to provide incredible energy and power. " +
                       "Expensive and difficult to make, these bows are found " +
                       "only in the hands of the best Solamnian marksmen " +
                       "or richest knights and nobles.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                  break;
               default:
                   long = "This is a recurve longbow masterfully crafted " +
                       "from wood of the Ergothian red cedar, laminated together " +
                       "with horn and sinew to provide incredible energy and power. " +
                       "Expensive and difficult to make, these bows are found " +
                       "only in the hands of the best Solamnian marksmen " +
                       "or richest knights and nobles.\n";
                      set_short("solamnic " +short);
                      add_adj("solamnic");
                    break;
            }
        }
    }
    else if(faction == "qualinesti")
    {
        string short = query_short();

        if(gHand != W_BOTH) 
        {
            switch(gLevel)
            {  
               default:
                  long = "An unusual one-handed crossbow.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..2: 
                   long = "This is an elven short bow of just over " +
                       "five feet in length. While it doesn't have the " +
                       "range of a longbow or the power of a recurve bow, " +
                       "it provides an effective ranged attack that can " +
                       "cause chaos to enemy forces.\n";
                      set_short("elven " +short);
                      add_adj("elven");
                    break;
                case 3..4: 
                   long = "This is a longbow made from ash found growing in " +
                       "the elven forest of Qualinesti. Over six feet " +
                       "in length it is capable of firing arrows at a great " +
                       "distance and with considerable power, and is deadly in " +
                       "the hands of elven archers.\n";
                      set_short("elven " +short);
                      add_adj("elven");
                    break;
                case 5: 
                   long = "This is a recurve longbow masterfully crafted " +
                       "from wood of Qualinesti ash, laminated together " +
                       "with horn and sinew to provide incredible energy and power. " +
                       "Expensive and difficult to make, these bows are rarely " +
                       "found in the hands of any other than elven archers or " +
                       "hunters.\n";
                      set_short("elven " +short);
                      add_adj("elven");
                  break;
               default:
                   long = "This is a recurve longbow masterfully crafted " +
                       "from wood of Qualinesti ash, laminated together " +
                       "with horn and sinew to provide incredible energy and power. " +
                       "Expensive and difficult to make, these bows are rarely " +
                       "found in the hands of any other than elven archers or " +
                       "hunters.\n";
                      set_short("elven " +short);
                      add_adj("elven");
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
               default:
                  long = "An unusual one-handed crossbow.\n";
                  break;
            }
        }
        else
        {
            switch(gLevel)
            {  
                case 0..2: 
                   long = "This is a standard short bow of just over " +
                       "five feet in length. While it doesn't have the " +
                       "range of a longbow or the power of a recurve bow, " +
                       "it provides an effective ranged attack that can " +
                       "cause chaos to enemy forces.\n";
                    break;
                case 3..4: 
                   long = "This is a longbow made from the wood of cornus trees " +
                       "that grow across the shores of the Newsea. Over six feet " +
                       "in length it is capable of firing arrows at a great " +
                       "distance and with considerable power.\n";
                    break;
                case 5: 
                   long = "This is a recurve longbow masterfully crafted " +
                       "from wood of the Kharolis red cedar, laminated together " +
                       "with horn and sinew to provide incredible energy and power. " +
                       "These bows are greatly prized by horse barbarians and archers " +
                       "from across Krynn for their sturdiness and effectiveness.\n";
                    break;
                default:
                   long = "This is a recurve longbow masterfully crafted " +
                       "from wood of the Kharolis red cedar, laminated together " +
                       "with horn and sinew to provide incredible energy and power. " +
                       "These bows are greatly prized by horse barbarians and archers " +
                       "from across Krynn for their sturdiness and effectiveness.\n";
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
    set_name("bow");
    set_short(warfare_weapon_short());
    set_long(warfare_weapon_long());
      
    set_hit(gHit);
    set_pen(gPen);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(gHit, gPen) + random(20) - 10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(gPen, W_AXE) +
        random(50) - 25);
        
    if (objectp(query_wielded()))
        query_wielded()->update_weapon(this_object());
}

void
create_bow()
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
