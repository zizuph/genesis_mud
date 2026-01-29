/*
 * /d/Genesis/sys/deposit.h
 *
 * Contains definitions useful in the Gnomes of Genesis depository.
 */

#include "/d/Genesis/gems/gem.h"

#ifndef _gnomes_of_genesis_h
#define _gnomes_of_genesis_h

/* Indices into the player account data structure. */
#define DEPOSIT_COINS  "coins"
#define DEPOSIT_TIME   "time"
#define DEPOSIT_FEE    "fee"
#define DEPOSIT_GEMS   "gems"
/* Indices into the consolidation data structure. */
#define DEPOSIT_NAME   "name"
#define DEPOSIT_FROM   "from"
#define DEPOSIT_TO     "to"

 /* Identifications for old files. */
#define DEPOSIT_OLD_CC "cc"
#define DEPOSIT_OLD_SC "sc"
#define DEPOSIT_OLD_GC "gc"
#define DEPOSIT_OLD_PC "pc"
#define DEPOSIT_OLD_FD "fd"
#define DEPOSIT_OLD_TM "tm"

/* Fees for banking services. */
#define GOG_YEAR_PROC_FEE        (1)  /* 1% in fees per year */
#define GOG_MIN_FEE_TIME       (600)  /*  10 minutes */
#define GOG_MAX_FEE_TIME   (2592000)  /*  30 days */
#define GOG_ONE_YEAR      (31536000)  /* 365 days */
#define GOG_TRANSIT_FEE         (10)  /* 10% of the gem value */
#define GOG_TRANSIT_TIME     (21600)  /*   6 hours */

/* File definitions */
#define GOG_DEPOSIT     ("/d/Genesis/obj/deposit")
#define DEPOSIT_DIR     ("/data/gnome_deposit/")
#define DEPOSIT_FILE(n) (DEPOSIT_DIR + extract((n), 0, 0) + "/" + (n))
#define GEM_BANKS_FILE  (DEPOSIT_DIR + "gem_banks")
#define GEM_TRANSFERS   (DEPOSIT_DIR + "gem_transfers")

/* Logs */
#define TRANSACTION_OTHER (0)
#define TRANSACTION_GEMS  (1)
#define TRANSACTION_COINS (2)
#define LOG_GOG_ACCOUNT   ("GOG_ACCOUNTS")
#define LOG_GOG_COINS     ("GOG_COINS")
#define LOG_GOG_GEMS      ("GOG_GEMS")
#define LOG_GOG_BANKS     ("GOG_BANKS")

/*
 * BANK_NAME(sid) - Each bank that wants to have a gem deposit must have a
 *   bank identifyer, or SID. This SID takes the form "domainID##" where the
 *   domain ID is the global domain number and ## is a serial number that is
 *   unique within the domain (starting at 01).
 * BANK_ID_BY_NAME(name) - Obtain a bank ID based on the name.
 */
#define BANK_NAME(sid)        (DEPOSIT_GEMS + (sid))
/* Hardcoded the length of the DEPOSIT_GEMS name here for speed. */
#define BANK_ID_BY_NAME(name) atoi(extract(name, 4))

/* Property */
#define PLAYER_I_CONSOLIDATE_GEMS "_player_i_consolidate_gems"

/*
 * The Terms and Usage definitions are made for banks that offer gem deposit
 * as well as those who do not.
 * Lines starting with "B" are for banks who do not have a gem deposit.
 * Lines starting with "G" are for banks who do have a gem deposit.
 */
#define GOG_LINE_BANK "B"
#define GOG_LINE_GEMS "G"

#define GOG_TERMS                                                               \
"|    GnoMeS oF GenESiS - TeRMs AnD COndITiOns\n|\n" +                          \
"B 1. To oPeN aN aCCouNT you SiMPly DePoSiT MoNey. ThIS bRaNcH IS NoT\n" +      \
"B    CeRTiFiEd TO haNDlE GeMs.\n" +                                            \
"G 1. To oPeN aN aCCouNT you SiMPly DePoSiT MoNey Or GeMS. NoT aLl bRAnCHes\n" +\
"G    ARe CeRTiFiEd TO haNDlE GeMs.\n" +                                        \
"| 2. you May WiTHDWaW youR MoNey aT aNy BRaNCH oF THe GoG. SiNCe GemS ArE\n" + \
"|    UniQUe, ThEy cAN onLY bE ReTriEVeD aT ThE BRaNcH THeY WeRe DepOSItEd.\n" +\
"G    We CaN cONsOlIDaTE yOUr GEmS iNTo OnE loCaTIoN ViA ArmOUrEd TrANsFeR.\n" +\
"| 3. oNLy oFFiCiaL CoPPeR, SiLVeR, GoLD and PLaTiNuM CoiNS aRe aCCePTeD.\n" +  \
"| 4. THe Fee FoR SaFeKeePiNG oF MoNEy iS ONe PeR cEnT PeR AnNuM OvER tHe\n" +  \
"B    VaLUe Of ThE aCCouNT.\n" +                                                \
"G    VaLUe Of ThE aCCouNT. TrAnSpORt CHaRgES aRe TeN PeR cENt oF THe VaLUe\n" +\
"G    Of ThE GeMS. GeM dePOSiTs Are FRee As InTRoDuCTiOn OffER.\n" +            \
"| 5. FeeS aRe DeDuCTeD FRoM THe aCCouNT aT eVeRy WiTHDRaWaL aND\n" +           \
"|    ReCaLCuLaTeD aT eVeRy DePoSiT.\n" +                                       \
"| 6. you May MaKe SeVeRaL TRaNSaCTioNS WiTHiN a FeW MiNuTeS aND JuST Pay\n" +  \
"|    oNe Fee.\n" +                                                             \
"| 7. THe CLeRK WiLL TeLL you HoW MuCH MoNey you HaVe DePoSiTeD FoR FRee.\n" +  \
"| 8. aCCouNTS aRe PeRSoNaL aND THe CLeRK May oNLy TuRN MoNey oVeR To\n" +      \
"|    PeoPLe He CaN See aND ReCoGNiZe. iNViSiBLe PeoPLe aND PeoPLe in\n" +      \
"|    DiSGuiSe May HaVe PRoBLeMS WiTH WiTHDRaWaLS.\n" +                         \
"| 9. iF THe aCCouNT HaS NoT BeeN TouCHeD FoR 90 DayS, THe oWNeR iS\n" +        \
"|    CoNSiDeReD MiSSiNG aND aLL FuNDS oN THe aCCouNT BeCoMe THe PRoPeRTy\n" +  \
"|    oF THe GoG.\n" +                                                          \
"|10. THe GoG aRe NoT ReSPoNSiBLe FoR LoSS oF FuNDS Due To eaRTHQuaKeS,\n" +    \
"|    RoBBeRy, PoWeRFuL MeNaCiNG MaGiCiaNS, THe MaNaGeRS MoTHeR iN LaW oR\n" +  \
"|    aNy oTHeR FoRM oF FoRCe MaJeuRe.\n"

#define GOG_USAGE                                                              \
"|GnoMeS oF GenESiS - DePoSiT uSaGe:\n|\n" +                                   \
"|- account [gems / banks]\n" +                                                \
"|\tFind out how much money or how many gems you have in your account,\n" +    \
"|\tor find out where you have deposits, and at which total value.\n|\n" +     \
"G- consolidate gems from <bank>\n" +                                          \
"G\tOrder a transfer of your gems from <bank> to your current location.\nG\n" +\
"|- deposit <coins> [except for <coins>]\n" +                                  \
"|\tDeposit coins into your account. You can specify not to deposit a\n" +     \
"|\tcertain number of coins by adding the \"except for\" phrase\n" +           \
"G- deposit <gems>\n" +                                                        \
"G\tDeposit gems into your account. They will stay with this branch.\n|\n" +   \
"G- retrieve <gems>\n" +                                                       \
"G\tRetrieve gems from your account. Note that gems can only be retrieved\n" + \
"G\tat the Branch where they were stored.\nG\n" +                              \
"|- withdraw <coins> [except for <coins>]\n" +                                 \
"|\tWithdraw coins from your account. You can specify not to withdraw\n" +     \
"|\ta certain number of coins by adding the \"except for\" phrase\n|\n" +      \
"|Examples of usage:\n" +                                                          \
"|\taccount    or    account gems    or    account banks\n" +                  \
"|\tdeposit 10 gold coins\n" +                                                 \
"|\tdeposit silver, gold, and copper coins except for 20 silver coins\n" +     \
"|\tdeposit coins\n" +                                                         \
"G\tdeposit pink corals\n" +                                                   \
"G\tretrieve 7 glittering diamonds\n" +                                        \
"|\twithdraw 10 silver and copper\n" +                                         \
"|\twithdraw coins except copper coins\n"

/* No definitions beyond this line. */
#endif _gnomes_of_genesis_h
