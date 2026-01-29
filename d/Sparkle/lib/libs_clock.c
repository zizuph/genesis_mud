/*******************************************************************\
| LIBS_CLOCK.C                                                      |
+-------------------------------------------------------------------+
| Library clock functions for everything in the domain.             |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Ported over from monks and extended
 * 01/12/15 Arandir	Added functions for VBFC output
 * 01/11/11 Arandir	Created
 *
 */

#include <macros.h>
#include <language.h>

#include "defs.h"

//-------------------------------------------------------------------

int	s_get_time ();
int	s_get_time_hour_of_period ();
int	s_get_time_hour_of_day ();
int	s_get_time_day_of_year ();

string	s_get_stime_hour_of_period ();
string	s_get_stime_period ();
string	s_get_stime_season ();

string  s_embed_stime_season ();

int	s_is_morning ();
int	s_is_afternoon ();
int	s_is_evening ();
int	s_is_night ();

int	s_is_spring ();
int	s_is_summer ();
int	s_is_autumn ();
int	s_is_winter ();

string	s_embed_when_morning (string sText);
string	s_embed_when_afternoon (string sText);
string	s_embed_when_evening (string sText);
string	s_embed_when_night (string sText);

string	s_embed_when_not_night (string sText);

string	s_embed_when_spring (string sText);
string	s_embed_when_summer (string sText);
string	s_embed_when_autumn (string sText);
string	s_embed_when_winter (string sText);

string	s_embed_when_not_winter (string sText);

string	s_get_when_morning (string sText);
string	s_get_when_afternoon (string sText);
string	s_get_when_evening (string sText);
string	s_get_when_night (string sText);

string	s_get_when_not_night (string sText);

string	s_get_when_spring (string sText);
string	s_get_when_summer (string sText);
string	s_get_when_autumn (string sText);
string	s_get_when_winter (string sText);

string	s_get_when_not_winter (string sText);

//-------------------------------------------------------------------

// These constants determine how fast the clock runs relative
// to the real time clock, how long the day is and such.

// When playing with these constants, keep in mind that:
//
// 1) One should be able to reasonably wait for any given
//    hour, meaning a day should not take more than 20 to
//    30 minutes real time.
//
// 2) One should not witness a season change more than once
//    a few days real time, meaning a year should take more
//    than the usual number of days.

#define S_CLOCK_GEN2SEC	55
#define S_CLOCK_SEC2MIN	60
#define S_CLOCK_MIN2HRS	60
#define S_CLOCK_HRS2DAY	24
#define S_CLOCK_DAY2YRS	666

#define S_CLOCK_SEC2HRS	(S_CLOCK_SEC2MIN * S_CLOCK_MIN2HRS)
#define S_CLOCK_SEC2DAY	(S_CLOCK_SEC2HRS * S_CLOCK_HRS2DAY)
#define S_CLOCK_SEC2YRS	(S_CLOCK_SEC2DAY * S_CLOCK_DAY2YRS)

// These constants divide a day into four periods.

#define S_CLOCK_MORNING_BEG	(S_CLOCK_HRS2DAY / 4)
#define S_CLOCK_AFTERNN_BEG	(S_CLOCK_HRS2DAY / 2)
#define S_CLOCK_EVENING_BEG	((3 * S_CLOCK_HRS2DAY) / 4)
#define S_CLOCK_NIGHTTT_BEG	((11 * S_CLOCK_HRS2DAY) / 12)

// These constants divide a year into four seasons.

#define S_CLOCK_SPRING_BEG	(S_CLOCK_DAY2YRS / 8)
#define S_CLOCK_SUMMER_BEG	((3 * S_CLOCK_DAY2YRS) / 8)
#define S_CLOCK_AUTUMN_BEG	((5 * S_CLOCK_DAY2YRS) / 8)
#define S_CLOCK_WINTER_BEG	((7 * S_CLOCK_DAY2YRS) / 8)

//-------------------------------------------------------------------

/*******************************************************************\
| Clock functions with numeric output.                              |
\*******************************************************************/

/*
 * Function name : s_get_time
 * Function name : s_get_time_hour_of_period
 * Function name : s_get_time_hour_of_day
 * Function name : s_get_time_day_of_year
 *
 */

int s_get_time ()
{
  // It is important to limit the time to a reasonably small number
  // before multiplying it by the speed up factor, otherwise an
  // arithmetic overflow will occur.

  return ((time () % (S_CLOCK_SEC2YRS / S_CLOCK_GEN2SEC)) * S_CLOCK_GEN2SEC);
}

int s_get_time_hour_of_period ()
{
  return (((s_get_time () / S_CLOCK_SEC2HRS) - 1) % (S_CLOCK_HRS2DAY / 2) + 1);
}

int s_get_time_hour_of_day ()
{
  return ((s_get_time () / S_CLOCK_SEC2HRS) % S_CLOCK_HRS2DAY);
}

int s_get_time_day_of_year ()
{
  return ((s_get_time () / S_CLOCK_SEC2DAY) % S_CLOCK_DAY2YRS);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Clock functions with string output.                               |
\*******************************************************************/

/*
 * Function name : s_get_stime_hour_of_period
 *
 */

string s_get_stime_hour_of_period ()
{
  return (LANG_WNUM (s_get_time_hour_of_period ()));
}

/*
 * Function name : s_get_stime_period
 *
 */

string s_get_stime_period ()
{
  int iHours = s_get_time_hour_of_day ();
  if (iHours < S_CLOCK_MORNING_BEG) return ("night");
  if (iHours < S_CLOCK_AFTERNN_BEG) return ("morning");
  if (iHours < S_CLOCK_EVENING_BEG) return ("afternoon");
  if (iHours < S_CLOCK_NIGHTTT_BEG) return ("evening");
  return ("night");
}

/*
 * Function name : s_get_stime_season
 *
 */

string s_get_stime_season ()
{
  int iDays = s_get_time_day_of_year ();
  if (iDays < S_CLOCK_SPRING_BEG) return ("winter");
  if (iDays < S_CLOCK_SUMMER_BEG) return ("spring");
  if (iDays < S_CLOCK_AUTUMN_BEG) return ("summer");
  if (iDays < S_CLOCK_WINTER_BEG) return ("autumn");
  return ("winter");
}

//-------------------------------------------------------------------

/*******************************************************************\
| Clock functions with function output.                             |
\*******************************************************************/

/*
 * Function name : s_embed_stime_season
 *
 */

string s_embed_stime_season ()
{
  return (VBFC ("s_get_stime_season:" + file_name (this_object ())));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Clock functions with boolean output.                              |
\*******************************************************************/

/*
 * Function name : s_is_morning
 * Function name : s_is_afternoon
 * Function name : s_is_evening
 * Function name : s_is_night
 *
 */

int s_is_morning ()
{
  int iHours = s_get_time_hour_of_day ();
  return ((iHours >= S_CLOCK_MORNING_BEG) &&
          (iHours <  S_CLOCK_AFTERNN_BEG));
}

int s_is_afternoon ()
{
  int iHours = s_get_time_hour_of_day ();
  return ((iHours >= S_CLOCK_AFTERNN_BEG) &&
          (iHours <  S_CLOCK_EVENING_BEG));
}

int s_is_evening ()
{
  int iHours = s_get_time_hour_of_day ();
  return ((iHours >= S_CLOCK_EVENING_BEG) &&
          (iHours <  S_CLOCK_NIGHTTT_BEG));
}

int s_is_night ()
{
  int iHours = s_get_time_hour_of_day ();
  return ((iHours >= S_CLOCK_NIGHTTT_BEG) ||
          (iHours <  S_CLOCK_MORNING_BEG));
}

/*
 * Function name : s_is_spring
 * Function name : s_is_summer
 * Function name : s_is_autumn
 * Function name : s_is_winter
 *
 */

int s_is_spring ()
{
  int iDays = s_get_time_day_of_year ();
  return ((iDays >= S_CLOCK_SPRING_BEG) &&
          (iDays <  S_CLOCK_SUMMER_BEG));
}

int s_is_summer ()
{
  int iDays = s_get_time_day_of_year ();
  return ((iDays >= S_CLOCK_SUMMER_BEG) &&
          (iDays <  S_CLOCK_AUTUMN_BEG));
}

int s_is_autumn ()
{
  int iDays = s_get_time_day_of_year ();
  return ((iDays >= S_CLOCK_AUTUMN_BEG) &&
          (iDays <  S_CLOCK_WINTER_BEG));
}

int s_is_winter ()
{
  int iDays = s_get_time_day_of_year ();
  return ((iDays >= S_CLOCK_WINTER_BEG) ||
          (iDays <  S_CLOCK_SPRING_BEG));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Clock functions with VBFC output.                                 |
\*******************************************************************/

/*
 * Function name : s_embed_when_morning
 * Function name : s_embed_when_afternoon
 * Function name : s_embed_when_evening
 * Function name : s_embed_when_night
 *
 * Function name : s_embed_when_spring
 * Function name : s_embed_when_summer
 * Function name : s_embed_when_autumn
 * Function name : s_embed_when_winter
 *
 */

#define s_embed_when_xxx(fProc,sGet)				\
string fProc (string sText)					\
{								\
  return (VBFC (sGet + ":" + file_name (this_object ()) +	\
                "|" + sText));					\
}

s_embed_when_xxx (s_embed_when_morning, "s_get_when_morning")
s_embed_when_xxx (s_embed_when_afternoon, "s_get_when_afternoon")
s_embed_when_xxx (s_embed_when_evening, "s_get_when_evening")
s_embed_when_xxx (s_embed_when_night, "s_get_when_night")

s_embed_when_xxx (s_embed_when_not_night, "s_get_when_not_night")

s_embed_when_xxx (s_embed_when_spring, "s_get_when_spring")
s_embed_when_xxx (s_embed_when_summer, "s_get_when_summer")
s_embed_when_xxx (s_embed_when_autumn, "s_get_when_autumn")
s_embed_when_xxx (s_embed_when_winter, "s_get_when_winter")

s_embed_when_xxx (s_embed_when_not_winter, "s_get_when_not_winter")

#undef s_embed_when_xxx

#define s_get_when_xxx(fProc,sCheck)				\
string fProc (string sText)					\
{								\
  if (sCheck ()) return (sText); else return ("");		\
}

s_get_when_xxx (s_get_when_morning, s_is_morning)
s_get_when_xxx (s_get_when_afternoon, s_is_afternoon)
s_get_when_xxx (s_get_when_evening, s_is_evening)
s_get_when_xxx (s_get_when_night, s_is_night)

s_get_when_xxx (s_get_when_not_night, !s_is_night)

s_get_when_xxx (s_get_when_spring, s_is_spring)
s_get_when_xxx (s_get_when_summer, s_is_summer)
s_get_when_xxx (s_get_when_autumn, s_is_autumn)
s_get_when_xxx (s_get_when_winter, s_is_winter)

s_get_when_xxx (s_get_when_not_winter, !s_is_winter)

#undef s_get_when_xxx

//-------------------------------------------------------------------

