/* 
 * Warfare helm standard file for the various factions.
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
set_armour_level(int level = 0, int location = A_HEAD, string faction = "blue")
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
        gAt = A_HEAD;
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
              short = "leather cap";
              add_name("cap");
              add_name("helmet");
              add_adj("leather");
              break;
           case 1: 
              short = "leather skullcap";
              add_name("cap");
              add_name("skullcap");
              add_name("helmet");
              add_adj("leather");
              break;
           case 2: 
              short = "chain coif";
              add_name("coif");
              add_name("helmet");
              add_adj("chain");
              remove_name("cap");
              remove_adj("leather");
              break;
           case 3: 
              short = "open-faced helmet";
              add_name("helmet");
              add_adj("open-faced");
              add_adj("open");
              add_adj("steel");
              add_adj("metal");
              remove_name("cap");
              remove_adj("leather");
              break;
           case 4: 
              short = "visored helmet";
              add_name("helmet");
              add_adj("visored");
              add_adj("steel");
              add_adj("metal");
              remove_name("cap");
              remove_adj("leather");
              break;
           case 5: 
              short = "great helm";
              add_name("helm");
              add_adj("steel");
              add_adj("metal");
              remove_name("cap");
              remove_adj("leather");
              break;
           default:
              short = "great helm";
              add_name("helm");
              add_adj("steel");
              add_adj("metal");
              remove_name("cap");
              remove_adj("leather");
              break;
        }

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
                  long = "This is a close-fitted leather cap, padded " +
                      "more to provide comfort than additional " +
                      "protection.\n";
                  break;
               case 1: 
                  long = "This is a stiff leather skullcap moulded to fit " +
                      "the head of a humanoid.\n";
                  break;
               case 2: 
                  long = "This coif is a chain mail hood, fitting snugly " +
                      "around the neck and over the head, with only the " +
                      "face uncovered. It has been stained " +faction+
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 3: 
                  long = "This is a steel helmet reinforced with leather, " +
                      "covering most of the head with the exception of " +
                      "the face and neck. It is stained " +faction+ 
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 4: 
                  long = "This is a steel helmet reinforced with leather, " +
                      "with the addition of a visored faceplate for " +
                      "additional protection. It is stained " +faction+ 
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 5: 
                  long = "This massive metal helm is fearsome in appearance, " +
                      "fashioned to resemble the open maw of a dragon. " +
                      "It covers the entire head, and has been stained " +
                      faction+ " to distinguish the wearer as a soldier " +
                      "of the " +capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               default:
                  long = "This massive metal helm is fearsome in appearance, " +
                      "fashioned to resemble the open maw of a dragon. " +
                      "It covers the entire head, and has been stained " +
                      faction+ " to distinguish the wearer as a soldier " +
                      "of the " +capitalize(faction)+ " Dragonarmy.\n";
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
                  long = "This is a close-fitted leather cap, padded " +
                      "more to provide comfort than additional " +
                      "protection.\n";
                  break;
               case 1: 
                  long = "This is a stiff leather skullcap moulded to fit " +
                      "the head of a humanoid.\n";
                  break;
               case 2: 
                  long = "This coif is a chain mail hood, fitting snugly " +
                      "around the neck and over the head, with only the " +
                      "face uncovered. It provides a fair level of " +
                      "protection while not impacting the wearer's " +
                      "field of vision.\n";
                  break;
               case 3: 
                  long = "This is a steel helmet reinforced with leather, " +
                      "covering most of the head with the exception of " +
                      "the face and neck. It is fashioned in the solamnic " +
                      "fashion from ore mined from the Vingaard Mountain " +
                      "range.\n";
                  set_short("solamnic " + short);
                  add_adj("solamnic");
                  break;
               case 4: 
                  long = "This is a steel helmet reinforced with leather, " +
                      "with the addition of a visored faceplate for " +
                      "additional protection. It is fashioned in the " +
                      "solamnic fashion from ore mined from the Vingaard " +
                      "Mountain range.\n";
                  set_short("solamnic " + short);
                  add_adj("solamnic");
                  break;
               case 5: 
                  long = "This massive metal helm is beautifully crafted " +
                      "in solamnic fashion to resemble a glorious " +
                      "phoenix in flight. It covers the entire head, " +
                      "as well as the neck and shoulders, providing " +
                      "great protection to the wearer.\n";
                  set_short("solamnic " + short);
                  add_adj("solamnic");
                 break;
               default:
                  long = "This massive metal helm is beautifully crafted " +
                      "in solamnic fashion to resemble a glorious " +
                      "phoenix in flight. It covers the entire head, " +
                      "as well as the neck and shoulders, providing " +
                      "great protection to the wearer.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
            }
    }
    else
    {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is a close-fitted leather cap, padded " +
                      "more to provide comfort than additional " +
                      "protection.\n";
                  break;
               case 1: 
                  long = "This is a stiff leather skullcap moulded to fit " +
                      "the head of a humanoid.\n";
                  break;
               case 2: 
                  long = "This coif is a chain mail hood, fitting snugly " +
                      "around the neck and over the head, with only the " +
                      "face uncovered. It provides a fair level of " +
                      "protection while not impacting the wearer's " +
                      "field of vision.\n";
                  break;
               case 3: 
                  long = "This is a steel helmet reinforced with leather, " +
                      "covering most of the head with the exception of " +
                      "the face and neck.\n";
                  break;
               case 4: 
                  long = "This is a steel helmet reinforced with leather, " +
                      "with the addition of a visored faceplate for " +
                      "additional protection.\n";
                  break;
               case 5: 
                  long = "This massive metal helm covers the entire head, " +
                      "as well as the neck and shoulders, providing " +
                      "great protection to the wearer.\n";
                 break;
               default:
                  long = "This massive metal helm covers the entire head, " +
                      "as well as the neck and shoulders, providing " +
                      "great protection to the wearer.\n";
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
    set_name("helm");
    add_name("armour");
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

