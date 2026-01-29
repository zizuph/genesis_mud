/* 
 * Warfare greaves/gauntlets standard file for the various factions.
 *
 * Arman Kharas, May 2018
 */
 
inherit "/std/armour";
inherit "/lib/keep";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void   setup_warfare_armour(int level, int location, string faction);

int           gLevel, gAc, gAt, *gAm;
string        gFaction;

public int
query_krynn_warfare_armour()
{
    return 1;
}

varargs void
set_armour_level(int level = 0, int location = A_ARMS, string faction = "blue")
{
    if ( !level )
        gLevel = 0;
    else
        gLevel = level;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 5)
        gLevel = 5;

    if ( !location )
        gAt = A_ARMS;
    else
        gAt = location;

    if ( !faction )
        gFaction = "blue";
    else
        gFaction = faction;
        
    setup_warfare_armour(gLevel, gAt, gFaction);
}

public void
setup_warfare_armour(int level, int location, string faction)
{
    switch(level)
    {  
       case 0: 
          gAc = 16;
          break;
       case 1: 
          gAc = 20;
          break;
       case 2: 
          gAc = 24;
          break;
       case 3: 
          gAc = 28;
          break;
       case 4: 
          gAc = 30;
          break;
       case 5: 
          gAc = 34;
          break;
       default:
          gAc = 34;
          break;
    }

    gAm = ({-2, 3, -1});
}

string
warfare_armour_short()
{
    string short;

        switch(gLevel)
        {  
           case 0:
              if (gAt == A_ARMS) 
              {
                  short = "leather bracers";
                  add_name("bracers");
                  add_adj("leather");
              }
              else
              {
                  short = "leather greaves";
                  add_name("greaves");
                  add_adj("leather");
                  remove_name("bracers");
              }
              break;
           case 1: 
              if (gAt == A_ARMS) 
              {
                  short = "studded leather bracers";
                  add_name("bracers");
                  add_adj("leather");
                  add_adj("studded");
              }
              else
              {
                  short = "studded leather greaves";
                  add_name("greaves");
                  add_adj("leather");
                  add_adj("studded");
                  remove_name("bracers");
              }
              break;
           case 2..4: 
              if (gAt == A_ARMS) 
              {
                  short = "chain gloves";
                  add_name("gloves");
                  add_adj("chain");
                  add_adj("metal");
                  remove_name("bracers");
                  remove_adj("leather");
              }
              else
              {
                  short = "chain leggings";
                  add_name("leggings");
                  add_adj("chain");
                  add_adj("metal");
                  remove_name("bracers");
                  remove_adj("leather");
              }
              break;
           case 5: 
              if (gAt == A_ARMS) 
              {
                  short = "steel gauntlets";
                  add_name("gauntlets");
                  add_adj("steel");
                  add_adj("metal");
                  remove_name("bracers");
                  remove_adj("leather");
              }
              else
              {
                  short = "steel greaves";
                  add_name("greaves");
                  add_adj("steel");
                  add_adj("metal");
                  remove_name("bracers");
                  remove_adj("leather");
              }
              break;
           default:
              if (gAt == A_ARMS) 
              {
                  short = "steel gauntlets";
                  add_name("gauntlets");
                  add_adj("steel");
                  add_adj("metal");
                  remove_name("bracers");
                  remove_adj("leather");
              }
              else
              {
                  short = "steel greaves";
                  add_name("greaves");
                  add_adj("steel");
                  add_adj("metal");
                  remove_name("bracers");
                  remove_adj("leather");
              }
              break;
        }

    set_pshort("pairs of " +short);

    return short;
}

string
warfare_armour_long()
{
    string long;
    string faction = gFaction;

    if(faction == "blue" || faction == "red" || faction == "white" ||
        faction == "black" || faction == "green")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0: 
                  long = "This is a pair of " +short+ ", padded " +
                      "for extra protection and comfort.\n";
                  break;
               case 1: 
                  long = "This is a pair of " +short+ ", its rivets " +
                      "of metal attached closely together to provide " +
                      "a flexible coating of hard metal to turn " +
                      "aside slashing and cutting attacks.\n";
                  break;
               case 2..4: 
                  long = "This is a pair of " +short+ ", providing " +
                      "good protection without sacrificing mobility. " +
                      "It has been stained " +faction+
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 5: 
                  long = "This is a pair of " +short+ ", skillfully " +
                      "crafted by a master armourer to provide excellent " +
                      "protection. It has been stained " +faction+
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               default:
                  long = "This is a pair of " +short+ ", skillfully " +
                      "crafted by a master armourer to provide excellent " +
                      "protection. It has been stained " +faction+
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
            }
    }
    else if(faction == "knights")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0: 
                  long = "This is a pair of " +short+ ", padded " +
                      "for extra protection and comfort.\n";
                  break;
               case 1: 
                  long = "This is a pair of " +short+ ", its rivets " +
                      "of metal attached closely together to provide " +
                      "a flexible coating of hard metal to turn " +
                      "aside slashing and cutting attacks.\n";
                  break;
               case 2..4: 
                  long = "This is a pair of " +short+ ", providing " +
                      "good protection without sacrificing mobility. " +
                      "It is fashioned in the solamnic fashion from ore " +
                      "mined from the Vingaard Mountain range.\n";
                  set_short("solamnic " + short);
                  add_adj("solamnic");
                  break;
               case 5: 
                  long = "This is a pair of " +short+ ", skillfully " +
                      "crafted by a master armourer to provide excellent " +
                      "protection. It has been engraved with symbols " +
                      "of the Solamnian Order of Knights - the Kingfisher, " +
                      "Crown, Sword, and Rose.\n";
                  set_short("solamnic " + short);
                  add_adj("solamnic");
                 break;
               default:
                  long = "This is a pair of " +short+ ", skillfully " +
                      "crafted by a master armourer to provide excellent " +
                      "protection. It has been engraved with symbols " +
                      "of the Solamnian Order of Knights - the Kingfisher, " +
                      "Crown, Sword, and Rose.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
            }
    }
    else if(faction == "neidar")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0: 
                  long = "This is a pair of " +short+ ", padded " +
                      "for extra protection and comfort.\n";
                  break;
               case 1: 
                  long = "This is a pair of " +short+ ", its rivets " +
                      "of metal attached closely together to provide " +
                      "a flexible coating of hard metal to turn " +
                      "aside slashing and cutting attacks.\n";
                  break;
               case 2..4: 
                  long = "This is a pair of " +short+ ", providing " +
                      "good protection without sacrificing mobility. " +
                      "It is dwarven made from ore " +
                      "mined in the hills near Iron Delving.\n";
                  set_short("dwarven " + short);
                  add_adj("dwarven");
                  break;
               case 5: 
                  long = "This is a pair of " +short+ ", skillfully " +
                      "crafted by a dwarven armourer to provide excellent " +
                      "protection.\n";
                  set_short("dwarven " + short);
                  add_adj("dwarven");
                 break;
               default:
                  long = "This is a pair of " +short+ ", skillfully " +
                      "crafted by a dwarven armourer to provide excellent " +
                      "protection.\n";
                  set_short("dwarven " +short);
                  add_adj("dwarven");
                  break;
            }
    }
    else
    {
            string short = query_short();

            switch(gLevel)
            {  
               case 0:  
                  long = "This is a pair of " +short+ ", padded " +
                      "for extra protection and comfort.\n";
                  break;
               case 1: 
                  long = "This is a pair of " +short+ ", its rivets " +
                      "of metal attached closely together to provide " +
                      "a flexible coating of hard metal to turn " +
                      "aside slashing and cutting attacks.\n";
                  break;
               case 2..4: 
                  long = "This is a pair of " +short+ ", providing " +
                      "good protection without sacrificing mobility.\n";
                  break;
               case 5: 
                  long = "This is a pair of " +short+ ", skillfully " +
                      "crafted by a master armourer to provide excellent " +
                      "protection.\n";
                 break;
               default:
                  long = "This is a pair of " +short+ ", skillfully " +
                      "crafted by a master armourer to provide excellent " +
                      "protection.\n";
                  break;
            }
    }

    return long;
}

public void
create_warfare_armour()
{
    if ( !gLevel )
        set_armour_level();
}

public void
update_warfare_armour()
{
    set_name("armour");
    set_short(warfare_armour_short());
    set_long(warfare_armour_long());
      
    set_ac(gAc);
    set_at(gAt);
    set_am(gAm);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(gAc) + random(20) - 10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(gAc, gAt) +
        random(50) - 25);

    if (objectp(query_worn()))
        query_worn()->update_armour(this_object());
}

void
create_armour()
{
    create_warfare_armour();
    update_warfare_armour();
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + gLevel + "&&" + 
        gAc + "&&" + gAt + "&&" + gFaction;
}
void 
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    gLevel = atoi(a[1]);
    gAc = atoi(a[2]);
    gAt = atoi(a[3]);
    gFaction = (a[4]);
    init_arm_recover(a[0]);
    update_warfare_armour();
}

