#include <stdproperties.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include "../sys/defs.h"
#include "../sys/clock.h"

inherit  ("/std/room");
inherit  ("/d/Gondor/morgul/feeling");

private static status orodruin;

static object clock;  // for convenient/fast use in inherited rooms

public void
reset_mordor_room() {}

public nomask void
reset_room() {
  // we add properties in the 'reset' because it's safer
  // as wizards or bad code can destroy our properties.
  // if you don't want default properties, overload
  // reset_mordor_room() and use remove_prop() there.
  if (orodruin)
    add_prop(ROOM_M_NO_SUN, 1); // Orodruin's smoke
  reset_mordor_room();
}

public void
create_mordor_room() {}

private nomask string
celestial_desc(string what, object for_who = TP) {
  int time, feel, sun, moon;
  string desc;

  if (TO->query_prop(ROOM_I_INSIDE))
    return ("You cannot see the " + what + " from indoors.\n");

  feel = query_feeling(for_who);
  if (orodruin || TO->query_prop(ROOM_M_NO_SUN)) {
    switch (feel) {
      case -1 :
        return ("You cannot see the " + what + " as dark clouds " +
                "blanket the land, covering you in comfortable " +
                "darkness.\n");
      case 0 :
        return ("You cannot see the " + what + " as dark clouds " +
                "blanket the land.\n");
      case 1 :
        return ("You cannot see the " + what + " as dark clouds " +
                "blanket the land, smothering you in oppressive " +
                "darkness.\n");
    }
  }

  if (!objectp(clock)) {
    setuid();
    seteuid(getuid());
    SAFE_LOAD(CLOCK);
    if (!objectp(clock = find_object(CLOCK)))
      return ("You find no " + what + ".\n");
  }
  time = clock->game_time();
  sun = clock->sun_position(time);

  switch (what) {
    case "stars" :
      switch (sun) {
        case POSITION_NOT_VISIBLE :
          return ("The stars twinkle brightly against the night sky.\n");
        case POSITION_EASTERN_HORIZON :
          return ("The stars twinkle faintly in the western sky as " +
                  "the coming of the dawn in the eastern horizon " +
                  "hides them in the sun's light.\n");
        case POSITION_EASTERN_RISING :
        case POSITION_OVERHEAD :
        case POSITION_WESTERN_SINKING :
          return ("It is full day, you cannot see any stars out.\n");
        case POSITION_WESTERN_HORIZON :
          return ("The stars twinkle faintly in the eastern sky of " +
                  "twilight as the sun sinks below the western " +
                  "horizon, sending the last rays of its light " +
                  "eastwards as the night approaches.\n");
      }

    case "sky" :
      switch (sun) {
        case POSITION_NOT_VISIBLE :
          desc = "night";
        case POSITION_EASTERN_HORIZON :
          desc = "early morning";
        case POSITION_EASTERN_RISING :
          desc = "morning";
        case POSITION_OVERHEAD :
          desc = "noon";
        case POSITION_WESTERN_SINKING :
          desc = "afternoon";
        case POSITION_WESTERN_HORIZON :
          desc = "evening";
      }
      return ("You examine the " + desc + " sky...\n" +
              celestial_desc("sun", for_who) +
              celestial_desc("moon", for_who) +
              celestial_desc("stars", for_who));
      
    case "sun" :
      switch (clock->sun_position(time)) {
        case POSITION_NOT_VISIBLE :
          return ("You cannot see the sun as it is night.\n");
        case POSITION_EASTERN_HORIZON :
          return ("The morning sun is rising on the eastern " +
                  "horizon as dawn breaks on a new day.\n");
        case POSITION_EASTERN_RISING :
          return ("The morning sun is climbing higher into the " +
                  "eastern sky as the day grows older.\n");
        case POSITION_OVERHEAD :
          return ("The noon sun is high overhead.\n");
        case POSITION_WESTERN_SINKING :
          return ("The afternoon sun is sinking lower into the " +
                  "western sky as the day grows older.\n");
        case POSITION_WESTERN_HORIZON :
          return ("The evening sun is sinking below the western " +
                  "horizon, sending the last rays of its light " +
                  "eastwards as night approaches.\n");
      }

    case "moon" :
      moon = clock->moon_position(time);
      if (moon == POSITION_NOT_VISIBLE)
        return ("You cannot see the moon.\n");
      switch (sun) {
        case POSITION_NOT_VISIBLE :
          if (clock->moon_phase(time) == MOON_NEW)
            return ("You see the new moon hidden against the night sky.\n");
          return ("You see the " + clock->moon_phase_string(time) +
                  " moon, Ithil, illuminating the night sky with his " +
                  "silvery radiance.\n");
        case POSITION_EASTERN_HORIZON :
          if (clock->moon_phase(time) == MOON_NEW)
            return ("You cannot see the moon.\n");
          desc = "The morning sun is rising on the eastern " +
                 "horizon as dawn breaks on a new day, yet you can " +
                 "still see the " + clock->moon_phase_string(time) +
                 " moon, Ithil, faintly ";
          switch (clock->moon_position(time)) {
            case POSITION_EASTERN_HORIZON :
            case POSITION_EASTERN_RISING :
              return (desc + "in the eastern sky.\n");
            case POSITION_OVERHEAD :
              return (desc + "in the sky directly above.\n");
            case POSITION_WESTERN_SINKING :
            case POSITION_WESTERN_HORIZON :
              return (desc + "in the western sky.\n");
          }

        case POSITION_EASTERN_RISING :
        case POSITION_OVERHEAD :
        case POSITION_WESTERN_SINKING :
          return ("You cannot see the moon as it's full day.\n");

        case POSITION_WESTERN_HORIZON :
          if (clock->moon_phase(time) == MOON_NEW)
            return ("You cannot see the moon.\n");
          desc = "The evening sun is sinking below the western " +
                 "horizon, sending the last rays of its light " +
                 "eastwards as night approaches, allowing you to " +
                 "see the " + clock->moon_phase_string(time) +
                 " moon, Ithil, faintly ";
          switch (clock->moon_position(time)) {
            case POSITION_EASTERN_HORIZON :
            case POSITION_EASTERN_RISING :
              return (desc + "in the eastern sky.\n");
            case POSITION_OVERHEAD :
              return (desc + "in the sky directly above.\n");
            case POSITION_WESTERN_SINKING :
            case POSITION_WESTERN_HORIZON :
              return (desc + "in the western sky.\n");
          }
      } // switch (sun)

  } // switch (what)
}

static nomask void
enable_orodruin(status flag = 1) {
  orodruin = flag;
}

public nomask void
create_room() {
  setuid();
  seteuid(getuid());
  SAFE_LOAD(CLOCK);
  clock = find_object(CLOCK);

  set_long("\nBUG: THIS ROOM NEEDS A DESCRIPTION!\n");

  add_item("moon",  &celestial_desc("moon"));
  add_item("sky",   &celestial_desc("sky"));
  add_item("stars", &celestial_desc("stars"));
  add_item("sun",   &celestial_desc("sun"));

  create_mordor_room();
  reset_room();
}

public nomask string
long(string s, object for_who = TP) {
  int time, feel, sun;
  object clock;
  string desc;

  if (stringp(s) || query_prop(ROOM_I_INSIDE))
    return (room::long(s));
  if (!objectp(clock)) {
    setuid();
    seteuid(getuid());
    SAFE_LOAD(CLOCK);
    if (!objectp(clock = find_object(CLOCK)))
      return (room::long(s));
  }

  time = clock->game_time();
  feel = query_feeling(for_who);

  switch (sun = clock->sun_position(time)) {
    case POSITION_NOT_VISIBLE :
      if (clock->game_hour(time) == 0)
        desc = "It is midnight.";
      else
        desc = "It is night.";

      desc += "  The air is chilly, and the dark sky is full of ";
      if (TO->query_prop(ROOM_M_NO_SUN)) {
        if (orodruin)
          desc += "clouds, illuminated with a sullen, red glow " +
                  "emanating from the cone of Orodruin; " +
                  "Mount Doom.";
        else
          desc += "clouds.";
      } else {
        if (orodruin)
          desc += "twinkling stars.  The landscape is illuminated " +
                  "with a sullen, red glow emanating from the cone " +
                  "or Orodruin; Mount Doom.";
        else
          desc += "twinkling stars.";
      }

      if ((clock->moon_phase(time) == MOON_NEW) ||
          (clock->moon_position(time) == POSITION_NOT_VISIBLE)) {
        switch (feel) {
          case -1 :
            desc += "  Comfortable darkness is all around, filling " +
                    "you with the feel of security and calmness.";
            break;
          case 1 :
            desc += "  The darkness is oppressive; shadows seem to " +
                    "threaten you from everywhere.";
            break;
        }
      } else {
        if (TO->query_prop(ROOM_M_NO_SUN)) {
          desc += "  The moon, Ithil, remains hidden behind the dark " +
                  "clouds which filter out most of its faint light, " +
                  "making it ";
          switch (feel) {
            case -1 :
              desc += "hardly noticeable and powerless to penetrate " +
                      "the comforting darkness.";
              break;
            case  0:
              desc += "hardly visible.";
              break;
            case  1:
              desc += "almost completely hidden and powerless to " +
                      "penetrate the suffocating blanket of darkness " +
                      "that lies heavily upon you.";
              break;
          }
        } else {
          desc += "  The " + clock->moon_phase_string(time) +
                  " moon, Ithil, illuminates the night sky with his " +
                  "silvery radiance.";
        }
        if (orodruin)
          desc += "  Its faint, grey light contrasts slightly " +
                  "with the red of the fires of Doom.";
      }
      break; // POSITION_NOT_VISIBLE

    case POSITION_EASTERN_HORIZON :
      desc = "It is early morning.  As dawn beings to break, ";
      if (TO->query_prop(ROOM_M_NO_SUN)) {
        desc += "the dark clouds grow back-lit with a faint grey light, ";
        switch (feel) {
          case -1 :
            desc += "but down here below the cloud cover, the friendly " +
                    "black of the night is still unbroken.";
            break;
          case 0 :
            desc += "a sure sign that finally the sun has risen to " +
                    "give light to a new day.";
            break;
          case 1 :
            desc += "but down here below the cloud cover, the shadows " +
                    "still reign and terrorize you with their great " +
                    "shapeless black masses.";
            break;
        }
      } else {
        desc += "the eastern sky begins to fill with a " +
                ((feel == -1) ? "harsh" : "warm") + " yellow light.";
      }
      if (orodruin)
        desc += "  The faint, yellow back-light of the sun contrasts " +
                "slightly with the red of the fires of Doom.";
      break; // POSITION_EASTERN_HORIZON

    case POSITION_EASTERN_RISING :
    case POSITION_OVERHEAD :
    case POSITION_WESTERN_SINKING :
      switch (sun) {
        case POSITION_EASTERN_RISING :
          desc = "It is morning.";
          break;
        case POSITION_OVERHEAD :
          desc = "It is noon.";
          break;
        case POSITION_WESTERN_SINKING :
          desc = "It is afternoon.";
          break;
      }
      if (TO->query_prop(ROOM_M_NO_SUN)) {
        desc += "  Dark clouds like a leaden wall cover the whole sky.  " +
                "Hardly a single beam of the sunlight can pierce the ";
        switch (feel) {
          case -1 :
            desc += "calming darkness, giving you security and comfort.";
            break;
          case 0 :
            desc += "darkness and shadows.";
            break;
          case 1 :
            desc += "terrible shadows around you.";
            break; 
        }
        if (orodruin)
          desc += "  The grey back-light of the sun behind the dark " +
                  "clouds contrasts with the sullen, red glow " +
                  "emanating from the cone of Orodruin; Mount Doom.";
      } else {
        switch (feel) {
          case -1 :
            desc += "  The cold sky above is of little comfort for the " +
                    "harsh light of the sun.";
            break;
          case 0 :
            desc += "  The sky above seems cold and bitter.";
            break;
          case 1 :
            desc += "  The sky above is cold, yet the yellow light of " +
                    "the sun brings warmth to your soul.";
            break;
        }
        if (orodruin)
          desc += "The landscape is slightly bloodied by the faint, red " +
                  "glow emanating from the cone of Orodruin; Mount Doom.";
      }
      break; // POSITION_FULL_DAY

    case POSITION_WESTERN_HORIZON :
      desc = "It is evening.";
      if (TO->query_prop(ROOM_M_NO_SUN))
        desc += "  From behind the thick layer of clouds the faint, " +
                "grey back-light of the sun begins to fade as it " +
                "sinks into the west.";
      else
        desc += "  The yellow light of the sun begins to fade as it " +
                "sinks into the west.";
      switch (feel) {
        case -1 :
          desc += "  The dark embrace of the night is nigh, giving " +
                  "you hope and joy.";
          break;
        case 0 :
          desc += "  Soon the night will have you.";
          break;
        case 1 :
          desc += "  Nightfall is threatening, and out of every " +
                  "corner more shadows seem to creep, trying to reach " +
                  "and devour you.";
          break;
      }
      if (orodruin) {
        if (TO->query_prop(ROOM_M_NO_SUN))
          desc += "  The faint, grey back-light of the sun contrasts " +
                  "with the sullen, red glow emanating from the cone " +
                  "or Orodruin; Mount Doom.";
        else
          desc += "  The landscape is slightly bloodied by the faint, " +
                  "red glow emanating from the cone of Orodruin; " +
                  "Mount Doom.";
      }
      break;
  }
      
  switch (feel) {
    case 0 :
      desc += "  This place seems to be out of a terrible dream.  It is " +
              "oppressive and makes you feel nervous.";
      break;
    case 1 :
      desc += "  This dreadful place makes you fear for your life.  " +
              "Dark shadows all around seem to weigh upon you like a " +
              "terrible burden, draining your life.";
      break;
  }

  desc += "  "; // sentence separator
  return (desc + room::long(s));
}

public nomask status
wizard_time(string str) {
  if (!TP->query_wiz_level())
    return (0);

  NF(capitalize(query_verb()) + " what?\n");
  if (!objectp(clock)) {
    setuid();
    seteuid(getuid());
    SAFE_LOAD(CLOCK);
    if (!objectp(clock = find_object(CLOCK)))
      return (0);
  }
  if (strlen(str))
    return (0);

  write(clock->stat_object());
  return (1);
}

public nomask status
check_time(string str) {
  object *livings;
  string desc;
  int time, x, sz;

  NF(capitalize(query_verb()) + " what?\n");
  if (!objectp(clock)) {
    setuid();
    seteuid(getuid());
    SAFE_LOAD(CLOCK);
    if (!objectp(clock = find_object(CLOCK)))
      return (0);
  }
  if (strlen(str))
    return (0);

  time = clock->game_time();

  switch (clock->sun_position(time)) {
    case POSITION_NOT_VISIBLE :
      if (clock->game_hour(time) == 0)
        desc = "midnight";
      else
        desc = "night";
      break;
    case POSITION_EASTERN_HORIZON :
      desc = "early morning";
      break;
    case POSITION_EASTERN_RISING :
      desc = "morning";
      break;
    case POSITION_OVERHEAD :
      desc = "noon";
      break;
    case POSITION_WESTERN_SINKING :
      desc = "afternoon";
      break;
    case POSITION_WESTERN_HORIZON :
      desc = "evening";
      break;
  }

  if (TO->query_prop(ROOM_M_NO_SUN)) {
    desc = "You guess it is " + desc + " now, but due to the " +
           "dark clouds enshrouding the sky above, you cannot " +
           "estimate the time more precisely.\n";
  } else {
    if (TO->query_prop(ROOM_I_INSIDE)) {
      desc = "You guess it is " + desc + " on the " +
             LANG_WORD(clock->game_day(time)) + " day of the month of " +
             clock->month_string(time) + " in the year " +
             clock->game_year(time) + " now, but since you are " +
             "inside and cannot study the sky, you cannot " +
             "estimate the time more precisely.\n";
    } else {
      int hour = clock->game_hour(time);
      if (hour > 12)
        hour -= 12;
      if (clock->game_hour(time) == 0)
        desc = "night";
      desc = "It is about " + LANG_WNUM(hour) + " o'clock in the " +
             desc + " on the " + LANG_WORD(clock->game_day(time)) +
             " day of the month of " + clock->month_string(time) +
             " in the year " + clock->game_year(time) + ".\n";
    }
  }

  write(desc);

  livings = FILTER_IS_SEEN(TP, FILTER_LIVE(all_inventory(TO))) - ({ TP, 0 });
  for (x = 0, sz = sizeof(livings); x < sz; x++)
    if (CAN_SEE_IN_ROOM(livings[x]))
      livings[x]->catch_msg(TP->query_The_name(livings[x]) +
                            " studies the sky, trying to determine " +
                            "what time it is.\n");
  
  return (1);
}

public void
init() {
  ::init();
  add_action(wizard_time, "clock");
  add_action(check_time,  "time");
}
