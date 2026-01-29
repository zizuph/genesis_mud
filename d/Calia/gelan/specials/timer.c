/* 	this is an object of the town Gelan

    coder(s):   Merlin

    history:    12. 2.93    installed path object               Merlin
                10. 1.93    townspecials.h -> special.h         Merlin
                 4. 1.93    slight modifications                Merlin
                31.10.92    leading " " and "0" for time        Merlin
                30.10.92    string functions                    Merlin
                29.10.92    tests                               Merlin
                28.10.92    creation                            Merlin

    purpose:    timer, gives the actual time of Calia, it is simplified,
                each calit has the same number of big gams.

                the time is calculated from timer(). I use the following
                conversion

                    #small clems in a clem      SCLEMS_PER_CLEM
                    #clems per gan              CLEMS_PER_GAN
                    #gans per gam               GANS_PER_GAM
                    #gams per big gam           GAMS_PER_BIGGAM
                    #big gams per calit         BIGGAMS_PER_CALIT
                    #calit per calid            CALITS_PER_CALID

                conversion normal time to Calia time

                    normal time * CONVERSION_FACTOR = Calia time


                the timer furnishes the following function (except for
                Calia_time_founding() you have to give the small clems to
                the functions, for example

                    Calia_time_calid(Calia_time_founding());

                here the functions:

                    int Calia_time_founding()

                        gives the small clems since founding of Gelan

                    int Calia_time_calid(int small clems)

                        gives the calids since founding of Gelan

                    int Calia_time_calit(int small clems)

                        gives the calit of the actual calid

                    int Calia_time_biggams(int small clems)

                        give the actual big gams of the CALID

                    int Calia_time_biggam(int small clems)

                        give the actual big gam of the CALIT

                    int Calia_time_gams(int small clems)

                        gives the actual gam of the CALID

                    int Calia_time_gam(int small clems)

                        gives the actual gam of the CALIT

                    int Calia_time_bigsgam(int small clems)

                        gives the actual gam of the BIG GAM

                    int Calia_time_gan(int small clems)

                        gives the actual gan of the GAM

                    int Calia_time_clem(int small clems)

                        gives the actual clem of the GAN

                    int Calia_time_smallclem(int small clems)

                        gives the actual small clem of the CLEM

                    string Calia_time_time(int small clems)

                        gives a string with the time in the format

                            "gan:clem"

                    string Calia_time_date(int small clems)

                        gives a string with the date in the format

                            "calid/calit/gam"


                function returning strings

                    string Calia_strgnumber(int number)

                        returns the string for a given number

                    string Calia_strnumber_long(int number)

                        returns a long string for a given number

                    string Calia_strtime_calit(int small clems)

                        gives the name of the calit of the actual calid

                    string Calia_strtime_bigsgam(int small clems)

                        gives the name of the actual gam of the BIGGAM

                    string Calia_strtime_date(int small clems)

                        gives a string with the date in the format

                            "xx gam of yy calit in zz calid"


                    int Calia_time_light(int small clems)

                        returns 1 if light ('day'), 0 if dark ('night')

    quests:     none
    special:    none

    to do:      some random for strtime function,
                weather in strtime function,
                function to reset the timer
    bug:        problems with #define
*/

inherit "/std/object";

#include "specials.h"
#include TIMER_INCLUDE
#include "/sys/stdproperties.h"

string * number_desc = ({
                     "st",                     /* 1st */
                     "nd",                     /* 2nd */
                     "rd",                     /* 3rd */
                     "th",                     /* xth */
                  });

string * number_desc_long = ({
                     "first",
                     "second",
                     "third",
                     "fourth",
                     "fifth",
                     "sixth",
                     "seventh",
                     "eighth",
                     "ninth",
                     "tenth",
                     "eleventh",
                     "twelfth",
                     "thirteenth",
                     "fourteenth",
                     "fifteenth",
                     "sixteenth",
                     "seventeenth",
                     "eighteent",
                     "twentieth",
                            });

string * bigsgam_desc = ({
                     "start",
                     "blood",
                     "hope",
                     "turn",
                     "win",
                        });

string * calit_desc = ({
                     "colour",
                     "storm",
                     "ill",
                     "death",
                     "dark",
                     "cold",
                     "snow",
                     "awake",
                     "wet",
                     "mild",
                     "warm",
                     "sun",
                     "bright",
                      });

/*
 * Function name: Calia_time_founding
 * Description:   gives the small clems since founding of Gelan
 * Arguments:     none
 * Returns:       small clems
 */

int
Calia_time_founding()
{
    return ((time() - GELAN_FOUNDING) * CONVERSION_FACTOR);
}

/*
 * Function name: Calia_time_calid
 * Description:   gives the calids since founding of Gelan
 * Arguments:     small clems since founding of Gelan
 * Returns:       calids
 */

int
Calia_time_calid(int sclems)
{
    return (sclems / SCLEMS_PER_CALID) + 1;
}

/*
 * Function name: Calia_time_calit
 * Description:   gives the calits of the actual calid
 * Arguments:     small clems since founding of Gelan
 * Returns:       calits
 */

int
Calia_time_calit(int sclems)
{
    return ((sclems - (Calia_time_calid(sclems) - 1 )* SCLEMS_PER_CALID)
            / SCLEMS_PER_CALIT) + 1;
}

/*
 * Function name: Calia_time_biggams
 * Description:   gives the actual big gam of the calid
 * Arguments:     small clems since founding of Gelan
 * Returns:       big gams
 */

int
Calia_time_biggams(int sclems)
{
    return ((sclems - (Calia_time_calid(sclems) - 1) * SCLEMS_PER_CALID)
            / SCLEMS_PER_BIGGAM) + 1;
}

/*
 * Function name: Calia_time_biggam
 * Description:   gives the actual big gam of the calit
 * Arguments:     small clems since founding of Gelan
 * Returns:       big gam
 */

int
Calia_time_biggam(int sclems)
{
    return ((sclems - (Calia_time_calid(sclems) - 1) * SCLEMS_PER_CALID
             - (Calia_time_calit(sclems) - 1) * SCLEMS_PER_CALIT)
            / SCLEMS_PER_BIGGAM) + 1;
}

/*
 * Function name: Calia_time_gams
 * Description:   gives the actual gam of the calid
 * Arguments:     small clems since founding of Gelan
 * Returns:       gams
 */

int
Calia_time_gams(int sclems)
{
    return ((sclems - (Calia_time_calid(sclems) - 1) * SCLEMS_PER_CALID)
            / SCLEMS_PER_GAM) + 1;
}

/*
 * Function name: Calia_time_gam
 * Description:   gives the actual gam of the calit
 * Arguments:     small clems since founding of Gelan
 * Returns:       gam
 */

int
Calia_time_gam(int sclems)
{
    return ((sclems - (Calia_time_calid(sclems) - 1) * SCLEMS_PER_CALID
             - (Calia_time_calit(sclems) - 1) * SCLEMS_PER_CALIT)
            / SCLEMS_PER_GAM) + 1;
}

/*
 * Function name: Calia_time_bigsgam
 * Description:   gives the actual gam of the big gam
 * Arguments:     small clems since founding of Gelan
 * Returns:       gam
 */

int
Calia_time_bigsgam(int sclems)
{
    return ((sclems - (Calia_time_calid(sclems) - 1) * SCLEMS_PER_CALID
            - (Calia_time_calit(sclems) - 1) * SCLEMS_PER_CALIT
            - (Calia_time_biggam(sclems) - 1) * SCLEMS_PER_BIGGAM)
           / SCLEMS_PER_GAM) + 1;
}

/*
 * Function name: Calia_time_gan
 * Description:   gives the gan of the gam
 * Arguments:     small clems since founding of Gelan
 * Returns:       gan
 */

int
Calia_time_gan(int sclems)
{
    return (sclems - (Calia_time_calid(sclems) - 1) * SCLEMS_PER_CALID
           - (Calia_time_gams(sclems) - 1) * SCLEMS_PER_GAM) / SCLEMS_PER_GAN;
}

/*
 * Function name: Calia_time_clem
 * Description:   gives the clem of the actual gan
 * Arguments:     small clems since founding of Gelan
 * Returns:       clem
 */

int
Calia_time_clem(int sclems)
{
    return (sclems - (Calia_time_calid(sclems) - 1) * SCLEMS_PER_CALID
           - (Calia_time_gams(sclems) - 1) * SCLEMS_PER_GAM
           - Calia_time_gan(sclems) * SCLEMS_PER_GAN) / SCLEMS_PER_CLEM;
}

/*
 * Function name: Calia_time_smallclem
 * Description:   gives the small clem of the actual clem
 * Arguments:     small clems since founding of Gelan
 * Returns:       small clem
 */

int
Calia_time_smallclem(int sclems)
{
    return sclems - (Calia_time_calid(sclems) - 1) * SCLEMS_PER_CALID
           - (Calia_time_gams(sclems) - 1) * SCLEMS_PER_GAM
           - Calia_time_gan(sclems) * SCLEMS_PER_GAN
           - Calia_time_clem(sclems) * SCLEMS_PER_CLEM;
}

/*
 * Function name: Calia_time_time
 * Description:   gives the time
 * Arguments:     small clems since founding of Gelan
 * Returns:       time as "hh:mm"
 */

int
Calia_time_time(int sclems)
{
    int gan, clem;
    string strgan, strclem;

    gan = Calia_time_gan(sclems);
    clem = Calia_time_clem(sclems);

    if(gan < 10)
      strgan = " " + gan + ":";
    else
      strgan = gan + ":";

    if(clem < 10)
      strclem = "0" + clem;
    else
      strclem = clem + "";

    return strgan + strclem;
}

/*
 * Function name: Calia_time_date
 * Description:   gives the date
 * Arguments:     small clems since founding of Gelan
 * Returns:       date as "mm/dd/yy"
 */

int
Calia_time_date(int sclems)
{
    return Calia_time_calit(sclems) + "/" + Calia_time_gam(sclems) + "/"
           + Calia_time_calid(sclems);
}

/*
 * Function name: Calia_strnumber
 * Description:   gives the number as string
 * Arguments:     number
 * Returns:       number as string
 */

string
Calia_strnumber(int number)
{
    if(number < 0)
        return "Error, number not positiv";

    if(number >= 4)
        return number + number_desc[3];
    else
        return number + number_desc[number - 1];
}

/*
 * Function name: Calia_strnumber_long
 * Description:   gives the number as string (long format)
 * Arguments:     number
 * Returns:       number as string
 */

string
Calia_strnumber_long(int number)
{
    if(number <= 0)
        return "Error, number not positiv";

    if(number >= 20)
        return Calia_strnumber(number);
    else
        return number_desc_long[number - 1];
}

/*
 * Function name: Calia_strtime_calit
 * Description:   gives the name of the calid
 * Arguments:     sclems since founding
 * Returns:       name of calid
 */

string
Calia_strtime_calit(int sclems)
{
    return calit_desc[Calia_time_calit(sclems) - 1];
}

/*
 * Function name: Calia_strtime_bigsgam
 * Description:   gives the name of the gam of the big gam
 * Arguments:     sclems since founding
 * Returns:       name of gam
 */

string
Calia_strtime_bigsgam(int sclems)
{
    return bigsgam_desc[Calia_time_bigsgam(sclems) - 1];
}

/*
 * Function name: Calia_strtime_date
 * Description:   gives the date with names
 * Arguments:     sclems since founding
 * Returns:       date with names
 */

string
Calia_strtime_date(int sclems)
{
    return Calia_strnumber(Calia_time_gam(sclems)) + " gam of the "
    + calit_desc[Calia_time_calit(sclems) - 1] + " calit in the "
    + Calia_strnumber_long(Calia_time_calid(sclems)) + " calid";
}

/*
 * Function name: Calia_time_light
 * Description:   indicates if light (day) or dark (night)
 * Arguments:     sclems since founding
 * Returns:       1 for light, 0 for dark
 */

int
Calia_time_light(int sclems)
{
    int gan;

    gan = Calia_time_gan(sclems);

    if(gan < DARK_LIGHT || gan >= LIGHT_DARK)
        return DARK;
    else
        return LIGHT;
}
