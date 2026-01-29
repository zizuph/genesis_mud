/*
 * /d/Genesis/obj/deposit.c
 *
 * This is the deposit of the Gnomes of Genesis, Genesis branch. If you
 * want to offer the services of the Gnomes of Genesis in your bank,
 * just clone this object into your bank room.
 *
 * /Mercade, August 5 1995
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/obj/deposit_lib";

#include <money.h>

#define ACCOUNTS ("/d/Genesis/obj/accounts")
#define DAY_FEE  (6)
#define TERMS                                                                 \
" 1. To oPeN aN aCCouNT you HaVe To DePoSiT MoNey.\n" +                       \
" 2. you May WiTHDWaW youR MoNey aT aNy BRaNCH oF THe GoG.\n" +               \
" 3. oNLy oFFiCiaL CoPPeR, SiLVeR, GoLD and PLaTiNuM CoiNS aRe aCCePTeD.\n" + \
" 4. THe Fee FoR SaFeKeePiNG iS SiX CoPPeR CoiNS PeR Day. MiNiMuM Fee\n" +    \
"    TiMe iS oNe Day, TWo DayS FoR HoBBiT CuSToMeRS.\n" +                     \
" 5. FeeS aRe DeDuCeD FRoM THe aCCouNT aT eVeRy WiTHDRaWaL aND\n" +           \
"    ReCaLCuLaTeD aT eVeRy DePoSiT.\n" +                                      \
" 6. THe CLeRK WiLL TeLL you HoW MuCH MoNey you HaVe DePoSiTeD FoR FRee.\n" + \
"    you CoMMaND HiM To Do THiS By TyPiNG 'account'.\n" +                     \
" 7. aCCouNTS aRe PeRSoNaL aND THe CLeRK May oNLy TuRN MoNey oVeR To\n" +     \
"    PeoPLe He CaN See aND ReCoGNiZe. iNViSiBLe PeoPLe aND PeoPLe in\n" +     \
"    DiSGuiSe May HaVe PRoBLeMS WiTH WiTHDRaWaLS.\n" +                        \
" 8. you May MaKe SeVeRaL TRaNSaCTioNS WiTHiN a FeW MiNuTeS aND JuST Pay\n" + \
"    oNe Fee.\n" +                                                            \
" 9. iF THe aCCouNT HaS NoT BeeN TouCHeD FoR 90 DayS, THe oWNeR iS\n" +       \
"    CoNSiDeReD MiSSiNG aND aLL FuNDS oN THe aCCouNT BeCoMe THe PRoPeRTy\n" + \
"    oF THe GoG.\n" +                                                         \
"10. THe GoG aRe NoT ReSPoNSiBLe FoR LoSS oF FuNDS Due To eaRTHQuaCKeS,\n" +  \
"    RoBBeRy, PoWeRFuL MeNaCiNG MaGiCiaNS, THe MaNaGeRS MoTHeR iN LaW oR\n" + \
"    aNy oTHeR FoRM oF FoRCe MaJeuRe.\n"

/*
 * Function name: create_deposit
 * Description  : This function is called to create the deposit. Use it
 *                to set some variables.
 */
void
create_deposit()
{
    set_accounts(ACCOUNTS);
    set_money_types(MONEY_TYPES);
    set_terms(TERMS);
    set_fee(DAY_FEE);
    set_coin_file("/std/coins");
}
