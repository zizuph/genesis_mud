/* 
 * Warfare shield standard file for the various factions.
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
set_armour_level(int level = 0, int location = A_SHIELD, string faction = "free")
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
        gAt = A_SHIELD;
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
          gAc = 20;
          break;
       case 1: 
          gAc = 24;
          break;
       case 2: 
          gAc = 28;
          break;
       case 3: 
          gAc = 32;
          break;
       case 4: 
          gAc = 34;
          break;
       case 5: 
          gAc = 38;
          break;
       default:
          gAc = 38;
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
              short = "wooden buckler";
              add_name("buckler");
              add_adj("wooden");
              break;
           case 1: 
              short = "wooden shield";
              add_name("shield");
              add_adj("wooden");
              break;
           case 2: 
              short = "iron shield";
              add_name("shield");
              add_adj("iron");
              remove_name("buckler");
              remove_adj("wooden");
              break;
           case 3: 
              short = "heater shield";
              add_name("shield");
              add_adj("heater");
              add_adj("metal");
              remove_name("buckler");
              remove_adj("wooden");
              break;
           case 4: 
              short = "steel body-shield";
              add_name("body-shield");
              add_adj("body");
              add_adj("steel");
              add_adj("metal");
              remove_name("buckler");
              remove_adj("wooden");
              break;
           case 5: 
              short = "steel kite-shield";
              add_name("kite-shield");
              add_adj("kite");
              add_adj("steel");
              add_adj("metal");
              remove_name("buckler");
              remove_adj("wooden");
              break;
           default:
              short = "steel kite-shield";
              add_name("kite-shield");
              add_adj("kite");
              add_adj("steel");
              add_adj("metal");
              remove_name("buckler");
              remove_adj("wooden");
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
                  long = "This is a small wooden buckler that attaches " +
                      "to the forearm. It offers limited protection but " +
                      "also does not hinder the wearer.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 1: 
                  long = "This is a small round shield approximately two " +
                      "feet in diameter made of wood and stained " +faction+
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 2: 
                  long = "This is a small round shield approximately two " +
                      "feet in diameter made of iron and stained " +faction+
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 3: 
                  long = "This is a heater shield made of steel and " +
                      "stained " +faction+ " to distinguish the wearer " +
                      "as a soldier of the " +capitalize(faction)+ 
                      " Dragonarmy. It provides good protection to the " +
                      "arm and body.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 4: 
                  long = "This is a large steel shield over five feet " +
                      "in length, providing good protection to the " +
                      "wearer's body. It is stained " +faction+ 
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 5: 
                  long = "This is a large kite-shield made of steel. Over " +
                      "six feet in height it provides good protection to " +
                      "the wearer's body and legs. It has been stained " +
                      faction+ " to distinguish the wearer as a soldier " +
                      "of the " +capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               default:
                  long = "This is a large kite-shield made of steel. Over " +
                      "six feet in height it provides good protection to " +
                      "the wearer's body and legs. It has been stained " +
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
                  long = "This is a small wooden buckler that attaches " +
                      "to the forearm. It offers limited protection but " +
                      "also does not hinder the wearer.\n";
                  break;
               case 1: 
                  long = "This is a small round shield approximately two " +
                      "feet in diameter made of wood.\n";
                  break;
               case 2: 
                  long = "This is a small round shield approximately two " +
                      "feet in diameter made of iron designed in " +
                      "Solamnic fashion and proudly emblazoned with " +
                      "knightly heraldry.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
               case 3: 
                  long = "This is a heater shield made of steel and " +
                      "emblazoned with the heraldry of the Knights " +
                      "of Solamnia. It provides good protection to the " +
                      "arm and body.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
               case 4: 
                  long = "This is a large steel shield over five feet " +
                      "in length, providing good protection to the " +
                      "wearer's body. Proudly emblazoned over it is the " +
                      "heraldry of the Knights of Solamnia.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
               case 5: 
                  long = "This is a large kite-shield made of steel. Over " +
                      "six feet in height it provides good protection to " +
                      "the wearer's body and legs. The shield has been " +
                      "engraved with symbols of the knights of Solamnia " +
                      "- the kingfisher in flight holding a thorned " +
                      "rose, top and tailed with crown and sword " +
                      "heraldry.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
               default:
                  long = "This is a large kite-shield made of steel. Over " +
                      "six feet in height it provides good protection to " +
                      "the wearer's body and legs. The shield has been " +
                      "engraved with symbols of the knights of Solamnia " +
                      "- the kingfisher in flight holding a thorned " +
                      "rose, top and tailed with crown and sword " +
                      "heraldry.\n";
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
                  long = "This is a small wooden buckler that attaches " +
                      "to the forearm. It offers limited protection but " +
                      "also does not hinder the wearer.\n";
                  break;
               case 1: 
                  long = "This is a small round shield approximately two " +
                      "feet in diameter made of wood.\n";
                  break;
               case 2: 
                  long = "This is a small round shield approximately two " +
                      "feet in diameter made of iron.\n";
                  break;
               case 3: 
                  long = "This is a heater shield made of steel, " +
                      "providing good protection to the arm and body.\n";
                  break;
               case 4: 
                  long = "This is a large steel shield over five feet " +
                      "in length, providing good protection to the " +
                      "wearer's body.\n";
                  break;
               case 5: 
                  long = "This is a large kite-shield made of steel. Over " +
                      "six feet in height it provides good protection to " +
                      "the wearer's body and legs.\n";
                  break;
               default:
                  long = "This is a large kite-shield made of steel. Over " +
                      "six feet in height it provides good protection to " +
                      "the wearer's body and legs.\n";
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
    set_name("shield");
    set_short(warfare_armour_short());
    set_long(warfare_armour_long());
      
    set_ac(gAc);
    set_at(gAt);
    set_am(gAm);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(gAc) + random(20) - 10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(gAc, gAt) +
        random(50) - 25);

   set_af(TO);

    if (objectp(query_worn()))
        query_worn()->update_armour(this_object());
}

void
create_armour()
{
    create_warfare_armour();
    update_warfare_armour();
}

int*
query_shield_slots()
{
    if(gLevel < 2)
       return (::query_shield_slots());
    else if (gLevel == 5)
       return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
    else
       return (::query_shield_slots() + ({ A_BODY }) );

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

