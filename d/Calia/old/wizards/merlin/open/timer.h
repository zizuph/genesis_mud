/* this is the include file for use with the timer

    history:    12. 2.93    installed path object           Merlin
                 4. 1.93    moved some constants            Merlin
                 3.11.92    created                         Merlin

*/

/* don't forget to make a

            seteuid(getuid());

   before a call to one of the timers functions
*/

#define CALIA_TIME_FOUNDING         (SPECIAL("timer"))->Calia_time_founding()
#define CALIA_TIME_CALID            (SPECIAL("timer"))->Calia_time_calid(CALIA_TIME_FOUNDING)
#define CALIA_TIME_CALIT            (SPECIAL("timer"))->Calia_time_calit(CALIA_TIME_FOUNDING)
#define CALIA_TIME_BIGGAMS          (SPECIAL("timer"))->Calia_time_biggams(CALIA_TIME_FOUNDING)
#define CALIA_TIME_BIGGAM           (SPECIAL("timer"))->Calia_time_biggam(CALIA_TIME_FOUNDING)
#define CALIA_TIME_GAMS             (SPECIAL("timer"))->Calia_time_gams(CALIA_TIME_FOUNDING)
#define CALIA_TIME_GAM              (SPECIAL("timer"))->Calia_time_gam(CALIA_TIME_FOUNDING)
#define CALIA_TIME_BIGSGAM          (SPECIAL("timer"))->Calia_time_bigsgam(CALIA_TIME_FOUNDING)
#define CALIA_TIME_GAN              (SPECIAL("timer"))->Calia_time_gan(CALIA_TIME_FOUNDING)
#define CALIA_TIME_CLEM             (SPECIAL("timer"))->Calia_time_clem(CALIA_TIME_FOUNDING)
#define CALIA_TIME_SMALLCLEM        (SPECIAL("timer"))->Calia_time_smallclem(CALIA_TIME_FOUNDING)
#define CALIA_TIME_TIME             (SPECIAL("timer"))->Calia_time_time(CALIA_TIME_FOUNDING)
#define CALIA_TIME_DATE             (SPECIAL("timer"))->Calia_time_date(CALIA_TIME_FOUNDING)

#define CALIA_STRTIME_CALIT         (SPECIAL("timer"))->Calia_strtime_calit(CALIA_TIME_FOUNDING)
#define CALIA_STRTIME_BIGSGAM       (SPECIAL("timer"))->Calia_strtime_bigsgam(CALIA_TIME_FOUNDING)
#define CALIA_STRTIME_DATE          (SPECIAL("timer"))->Calia_strtime_date(CALIA_TIME_FOUNDING)

#define CALIA_TIME_LIGHT            (SPECIAL("timer"))->Calia_time_light(CALIA_TIME_FOUNDING)

/* some constants */

#define SCLEMS_PER_CLEM         57              /* small clems per clem */
#define CLEMS_PER_GAN           53              /* clems per gan */
#define GANS_PER_GAM            19              /* gans per gam */
#define GAMS_PER_BIGGAM         5               /* gams per big gam */
#define BIGGAMS_PER_CALIT       3               /* big gams per calit */
#define CALITS_PER_CALID        13              /* calits per calid */

/* #define SCLEMS_PER_GAN       CLEMS_PER_GAN * SCLEMS_PER_CLEM */
#define SCLEMS_PER_GAN          3021
/* #define SCLEMS_PER_GAM       GANS_PER_GAM * SCLEMS_PER_GAN */
#define SCLEMS_PER_GAM          57399
/* #define SCLEMS_PER_BIGGAM    GAMS_PER_BIGGAM * SCLEMS_PER_GAM */
#define SCLEMS_PER_BIGGAM       286995
/* #define SCLEMS_PER_CALIT     BIGGAMS_PER_CALIT * SCLEMS_PER_BIGGAM */
#define SCLEMS_PER_CALIT        860985
/* #define SCLEMS_PER_CALID     CALITS_PER_CALID * SCLEMS_PER_CALIT */
#define SCLEMS_PER_CALID        11192805

#define DARK                    0               /* indicates night */
#define LIGHT                   1               /* indicates day */

#define DARK_LIGHT              5               /* start of gam */
#define LIGHT_DARK              17              /* end of gam */

#define GELAN_FOUNDING          726194632       /* seconds when Gelan was founded */

#define CONVERSION_FACTOR       20              /* 1 Calia clem = 3 secs, */
                                                /* 1 Calia gam = 50 min   */

