#ifndef DIRS_H
#define DIRS_H

/* Directories. */

#define D_ROOT	    "/d/Shire/common/"
#define D_HOLLIN    D_ROOT + "hollin/"
#define D_BREE	    D_ROOT + "bree/"
#define D_EASTROAD  D_ROOT + "eastroad/"
#define D_RIVENDELL D_ROOT + "rivendell/"
#define D_INCLUDE   D_ROOT + "include/"
#define D_LIB	    D_ROOT + "lib/"
#define D_NPC	    D_ROOT + "monster/"
#define D_MONSTER   D_NPC
#define D_OBJ	    D_ROOT + "obj/"
#define D_WEAPON    D_ROOT + "weapon/"
#define D_ARMOUR    D_ROOT + "armour/"
#define D_MINES	    D_ROOT + "mines/"

#define D_ROGON	    "/d/Shire/rogon/"

#define D_AVD1_R    D_ROGON + "avd1/"
#define D_SPELLS    D_ROGON + "spells/"
#define D_SDIR      D_ROGON + "sdir/"
#define D_CRITICALS D_ROGON + "spells/criticals/"
#define D_CRITS     D_CRITICALS

/* Files */

/* Inherit files */

#define TellemFile   "/d/Shire/common/lib/tell"
#define HeatCritFile "/d/Shire/rogon/spells/criticals/heat"
#define ForestFile   "/d/Shire/common/lib/forest"
#define RomFile      "/d/Shire/common/lib/rom"
#define OutroomFile  "/d/Shire/common/lib/outroom"
#define LakeroomFile "/d/Shire/common/lib/lakeroom"
#define ShireArmour  "/d/Shire/common/armour/shire_armour"
#define ArmourFile   ShireArmour
#define MinesFile    "/d/Shire/common/lib/mines"
#define ExtraFile    "/d/Shire/rogon/sdir/lib/slextra"

/* Functions - Beware, these are normally inherited. */

#define Tellem                      TellemFile->tellem                   
#define HeatCrit                    HeatCritFile->heat_crit              
#define MakeBurn                    HeatCritFile->make_burn
#define ExtraDam                    HeatCritFile->do_extra_dam
#define DropWieldedWeapon           HeatCritFile->drop_wielded_weapon
#define AddDelay                    HeatCritFile->add_delay
#define AddFumble                   HeatCritFile->add_fumble

#define RatioStr(x,y)               ExtraFile->ratio_str((CommaUid(),x),y)

#define CreateArmour                create_shire_armour
#define ResetArmour                 reset_shire_armour
#endif
