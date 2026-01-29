/* 
 * Warfare body armour standard file for the various factions.
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
set_armour_level(int level = 0, int location = A_TORSO, string faction = "blue")
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
        gAt = A_TORSO;
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
    string faction = gFaction;

        switch(gLevel)
        {  
           case 0: 
              short = "leather breastplate";
              add_name("breastplate");
              add_adj("leather");
              break;
           case 1: 
              short = "studded leather breastplate";
              add_name("breastplate");
              add_adj("leather");
              add_adj("studded");
              break;
           case 2: 
              short = "scale mail";
              add_name("mail");
              add_adj("scale");
              remove_name("breastplate");
              remove_adj("leather");
              break;
           case 3: 
              short = "steel chainmail";
              add_name("chainmail");
              add_adj("steel");
              add_adj("metal");
              remove_name("breastplate");
              remove_adj("leather");
              break;
           case 4: 
              short = "banded mail";
              add_name("mail");
              add_adj("banded");
              add_adj("metal");
              remove_name("breastplate");
              remove_adj("leather");
              break;
           case 5: 
              short = "platemail";
              add_name("platemail");
              add_adj("steel");
              add_adj("metal");
              remove_name("breastplate");
              remove_adj("leather");
              break;
           default:
              short = "platemail";
              add_name("platemail");
              add_adj("steel");
              add_adj("metal");
              remove_name("breastplate");
              remove_adj("leather");
              break;
        }

    if(faction == "ice")
    {
        switch(gLevel)
        {  
           case 0: 
              short = "leather breastplate";
              add_name("breastplate");
              add_adj("leather");
              break;
           case 1: 
              short = "studded leather breastplate";
              add_name("breastplate");
              add_adj("leather");
              add_adj("studded");
              break;
           case 2: 
              short = "bear-hide breastplate";
              add_name("breastplate");
              add_adj("leather");
              add_adj("hide");
              add_adj("bear");
              break;
           case 3: 
              short = "thanoi-hide breastplate";
              add_name("breastplate");
              add_adj("leather");
              add_adj("hide");
              add_adj("thanoi");
              break;
           case 4: 
              short = "yeti-hide breastplate";
              add_name("breastplate");
              add_adj("leather");
              add_adj("hide");
              add_adj("yeti");
              break;
           case 5: 
              short = "remorhaz scale mail";
              add_name("mail");
              add_adj("scale");
              add_adj("remorhaz");
              remove_name("breastplate");
              remove_adj("leather");
              break;
           default:
              short = "remorhaz scale mail";
              add_name("mail");
              add_adj("scale");
              add_adj("remorhaz");
              remove_name("breastplate");
              remove_adj("leather");
              break;
        }
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
                  long = "This is a strong and stiff leather breastplate, " +
                      "hardened in boiling oil to provide reasonable - " +
                      "and cheap - protection for militia and light " +
                      "infantry.\n";
                  break;
               case 1: 
                  long = "This is a breastplate of leather armour " +
                      "affixed with hundreds of metal rivets, studded " +
                      "so closely together that they form a flexible " +
                      "coating of hard metal that turns aside slashing " +
                      "and cutting attacks.\n";
                  break;
               case 2: 
                  long = "This is a coat of soft leather covered with " +
                      "overlapping pieces of metal, much like the " +
                      "scales of a giant snake, stained " +faction+
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 3: 
                  long = "This is a suit of chain mail made of " +
                      "interlocking steel rings over a layer of soft " +
                      "leather, stained " +faction+ " to distinguish " +
                      "the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 4: 
                  long = "This is a suit of chain mail with strips " +
                      "of horizontal metal rivetted across vital " +
                      "areas of the chest. It is stained " +faction+ 
                      " to distinguish the wearer as a soldier of the " +
                      capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               case 5: 
                  long = "This is a suit of chain mail with steel " +
                      "plates riveted in place to protect the chest, " +
                      "abdomen and groin. It has been stained " +
                      faction+ " to distinguish the wearer as a soldier " +
                      "of the " +capitalize(faction)+ " Dragonarmy.\n";
                  set_short(faction + " " + short);
                  add_adj(faction);
                  break;
               default:
                  long = "This is a suit of chain mail with steel " +
                      "plates riveted in place to protect the chest, " +
                      "abdomen and groin. It has been stained " +
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
                  long = "This is a strong and stiff leather breastplate, " +
                      "hardened in boiling oil to provide reasonable - " +
                      "and cheap - protection for militia and light " +
                      "infantry.\n";
                  break;
               case 1: 
                  long = "This is a breastplate of leather armour " +
                      "affixed with hundreds of metal rivets, studded " +
                      "so closely together that they form a flexible " +
                      "coating of hard metal that turns aside slashing " +
                      "and cutting attacks.\n";
                  break;
               case 2: 
                  long = "This is a coat of soft leather covered with " +
                      "overlapping pieces of metal, similar to the " +
                      "scales of a giant fish, however designed in " +
                      "Solamnic fashion to look like overlapping rose " +
                      "petals.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
               case 3: 
                  long = "This is a suit of chain mail made of " +
                      "interlocking rings of Solamnic steel over a " +
                      "layer of soft leather.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
               case 4: 
                  long = "This is a suit of chain mail with strips " +
                      "of horizontal metal rivetted across vital " +
                      "areas of the chest to provide extra protection.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
               case 5: 
                  long = "This is a suit of chain mail with steel " +
                      "plates riveted in place to protect the chest, " +
                      "abdomen and groin. These plates have been engraved " +
                      "with symbols of the knights of Solamnia - the " +
                      "kingfisher in flight holding a thorned rose, top " +
                      "and tailed with crown and sword heraldry.\n";
                  set_short("solamnic " +short);
                  add_adj("solamnic");
                  break;
               default:
                  long = "This is a suit of chain mail with steel " +
                      "plates riveted in place to protect the chest, " +
                      "abdomen and groin. These plates have been engraved " +
                      "with symbols of the knights of Solamnia - the " +
                      "kingfisher in flight holding a thorned rose, top " +
                      "and tailed with crown and sword heraldry.\n";
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
                  long = "This is a strong and stiff leather breastplate, " +
                      "hardened in boiling oil to provide reasonable - " +
                      "and cheap - protection for scouts and light " +
                      "infantry.\n";
                  break;
               case 1: 
                  long = "This is a breastplate of leather armour " +
                      "affixed with hundreds of metal rivets, studded " +
                      "so closely together that they form a flexible " +
                      "coating of hard metal that turns aside slashing " +
                      "and cutting attacks.\n";
                  break;
               case 2: 
                  long = "This is a coat of soft leather covered with " +
                      "overlapping pieces of metal, designed in dwarven " +
                      "fashion to resemble the scales of a giant lizard.\n";
                  set_short("dwarven " +short);
                  add_adj("dwarven");
                  break;
               case 3: 
                  long = "This is a suit of chain mail made of " +
                      "interlocking rings of dwarven steel over a " +
                      "layer of soft leather.\n";
                  set_short("dwarven " +short);
                  add_adj("dwarven");
                  break;
               case 4: 
                  long = "This is a suit of chain mail with strips " +
                      "of horizontal metal rivetted across vital " +
                      "areas of the chest to provide extra protection.\n";
                  set_short("dwarven " +short);
                  add_adj("dwarven");
                  break;
               case 5: 
                  long = "This is a suit of chain mail with steel plates " +
                      "masterfully riveted in place to protect the chest, " +
                      "abdomen and groin. The plates have been engraved " +
                      "with dwarven symbols of war and battle.\n";
                  set_short("dwarven " +short);
                  add_adj("dwarven");
                  break;
               default:
                  long = "This is a suit of chain mail with steel plates " +
                      "masterfully riveted in place to protect the chest, " +
                      "abdomen and groin. The plates have been engraved " +
                      "with dwarven symbols of war and battle.\n";
                  set_short("dwarven " +short);
                  add_adj("dwarven");
                  break;
            }
    }
    else if(faction == "qualinesti")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0: 
                  long = "This is a supple leather breastplate, " +
                      "providing reasonable protection for elven scouts " +
                      "and rangers without compromising their stealth.\n";
                  set_short("elven " +short);
                  add_adj("elven");
                  break;
               case 1: 
                  long = "This is a breastplate of leather armour " +
                      "affixed with hundreds of metal rivets, studded " +
                      "so closely together that they form a flexible " +
                      "coating of hard metal that turns aside slashing " +
                      "and cutting attacks.\n";
                  set_short("elven " +short);
                  add_adj("elven");
                  break;
               case 2: 
                  long = "This is a coat of soft leather covered with " +
                      "overlapping pieces of metal, designed in " +
                      "elven fashion to look like overlapping leaves.\n";
                  set_short("elven " +short);
                  add_adj("elven");
                  break;
               case 3: 
                  long = "This is a suit of elven chain mail made of " +
                      "interlocking rings of light steel over a " +
                      "layer of soft leather.\n";
                  set_short("elven " +short);
                  add_adj("elven");
                  break;
               case 4: 
                  long = "This is a suit of elven chain mail with strips " +
                      "of horizontal metal rivetted across vital " +
                      "areas of the chest to provide extra protection.\n";
                  set_short("elven " +short);
                  add_adj("elven");
                  break;
               case 5: 
                  long = "This is a suit of elven chain mail with steel " +
                      "plates riveted in place to protect the chest, " +
                      "abdomen and groin.\n";
                  set_short("elven " +short);
                  add_adj("elven");
                  break;
               default:
                  long = "This is a suit of elven chain mail with steel " +
                      "plates riveted in place to protect the chest, " +
                      "abdomen and groin.\n";
                  set_short("elven " +short);
                  add_adj("elven");
                  break;
            }
    }
    else if(faction == "ice")
    {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is a supple leather breastplate, " +
                      "providing reasonable protection and warmth " +
                      "for Ice Folk tribesman and hunters.\n";
                  break;
               case 1: 
                  long = "This is a breastplate of leather armour " +
                      "affixed with hundreds of cold stone rivets, studded " +
                      "so closely together that they form a flexible " +
                      "covering of that turns aside slashing " +
                      "and cutting attacks.\n";
                  break;
               case 2: 
                  long = "This is a breastplate of leather armour " +
                      "made from the thick hide of a polar bear, " +
                      "providing good protection from the cold as " +
                      "well as from weapons in battle.\n";
                  break;
               case 3: 
                  long = "This is a breastplate of leather armour " +
                      "made from the thick hide of a thanoi, " +
                      "providing good protection for Ice Folk from the " +
                      "cold, as well as enraging their vicious " +
                      "neighbours.\n";
                  break;
               case 4: 
                  long = "This is a breastplate of leather armour " +
                      "made from the thick hide of the fearsome yeti! " +
                      "Apart from providing excellent protection, this " +
                      "armour marks the wearer a mighty warrior - as " +
                      "few are capable of defeating one of the most feared " +
                      "creatures on the glacier.\n";
                  break;
               case 5: 
                  long = "This is a suit of whitish-blue mail made from the " +
                      "scales of the arctic remorhaz - a fearsome magical " +
                      "creature resembling a gigantic centipede of almost " +
                      "twenty feet in length, whose scales are as hard as " +
                      "the strongest steel. This mail is highly prized by " +
                      "the greatest warriors of the Ice Folk.\n";
                  break;
               default:
                  long = "This is a suit of whitish-blue mail made from the " +
                      "scales of the arctic remorhaz - a fearsome magical " +
                      "creature resembling a gigantic centipede of almost " +
                      "twenty feet in length, whose scales are as hard as " +
                      "the strongest steel. This mail is highly prized by " +
                      "the greatest warriors of the Ice Folk.\n";
                  break;
            }
    }
    else
    {
            switch(gLevel)
            {  
               case 0: 
                  long = "This is a strong and stiff leather breastplate, " +
                      "hardened in boiling oil to provide reasonable - " +
                      "and cheap - protection for militia and light " +
                      "infantry.\n";
                  break;
               case 1: 
                  long = "This is a a breastplate of leather armour " +
                      "affixed with hundreds of metal rivets, studded " +
                      "so closely together that they form a flexible " +
                      "coating of hard metal that turns aside slashing " +
                      "and cutting attacks.\n";
                  break;
               case 2: 
                  long = "This is a coat of soft leather covered with " +
                      "overlapping pieces of metal, similar to the " +
                      "scales of a giant snake.\n";
                  break;
               case 3: 
                  long = "This is a suit of chain mail made of " +
                      "interlocking rings of steel over a " +
                      "layer of soft leather, commonly worn by " +
                      "men-at-arms and mercenaries.\n";
                  break;
               case 4: 
                  long = "This is a suit of chain mail with strips " +
                      "of horizontal metal rivetted across vital " +
                      "areas of the chest to provide extra protection.\n";
                  break;
               case 5: 
                  long = "This is a suit of chain mail with steel " +
                      "plates riveted in place to protect the chest, " +
                      "abdomen and groin. This armour provides good " +
                      "protection, and is favoured by mercenary " +
                      "captains, royal guards and heavy infantry.\n";
                  break;
               default:
                  long = "This is a suit of chain mail with steel " +
                      "plates riveted in place to protect the chest, " +
                      "abdomen and groin. This armour provides good " +
                      "protection, and is favoured by mercenary " +
                      "captains, royal guards and heavy infantry.\n";
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

