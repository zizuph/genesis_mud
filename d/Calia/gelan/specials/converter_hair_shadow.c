
/* 	this is the Gelan hair shadow

    coder(s):   Glykron & Maniac

    history:    11.7.95     error traps and cmdsoul added    Maniac
                13.9.94     destruct_shadow defined; calling
                            remove_object in shadow removed
                            player!                          Maniac 
                13.9.94     autoloading added                Maniac
                18. 4.93    header added                     Glykron

    purpose:    to allow a player to have hair via a subloc

    to do:      none
    bug:        none known
*/
inherit "/std/shadow";
#include <stdproperties.h>
#include <macros.h>
#include "specials.h"
#include HAIR_INCLUDE

#define HAIRSTYLE_SUBLOC "hairstyle"
#define HAIRSTYLE_SHADOW (GELAN_SPECIALS + "hair_shadow")
#define HAIRSTYLE_CMDSOUL (GELAN_SPECIALS + "hair_cmdsoul")

#define OLD_HAIRSTYLE_SHADOW  "/d/Calia/glykron/gelan/specials/hair_shadow"
#define OLD_HAIRSTYLE_CMDSOUL "/d/Calia/glykron/gelan/specials/hair_cmdsoul"

string hairstyle, length, colour, style;

void
set_hairstyle(string style)
{
    hairstyle = style;
}

string
query_hairstyle()
{
    return hairstyle;
}


void
set_hair_length(string l)
{
    length = l;
}

string
query_hair_length()
{
    return length;
}

void
set_hair_colour(string c)
{
    colour = c;
}

string 
query_hair_colour()
{
    return colour;
}

void
set_hair_style(string s)
{
    style = s;
}

string
query_hair_style()
{
    return style;
}


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != HAIRSTYLE_SUBLOC)
	return shadow_who->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
	str = "Your";
    else
	str = capitalize(me->query_possessive());

    return str + " hair is " + hairstyle + ".\n";
}


/* Use instead of remove_object() */
void
destruct_hair_shadow()
{
  if (member_array(OLD_HAIRSTYLE_CMDSOUL, shadow_who->query_cmdsoul_list()) > -1) {
      shadow_who->remove_cmdsoul(OLD_HAIRSTYLE_CMDSOUL);
      shadow_who->update_hooks();
  }
  destruct();
}


/* Get rid of hairstyle autoshadow from player and destruct shadow */ 
void
shadow_autoshadow_destruct()
{
    shadow_who->remove_autoshadow(MASTER_OB(this_object()) + ".c");
    destruct_hair_shadow(); 
}


/* Add the cmdsoul to the player */
void
add_hair_commands()
{
    shadow_who->add_cmdsoul(OLD_HAIRSTYLE_CMDSOUL);
    shadow_who->update_hooks();
}


public void
autoload_shadow(mixed arg)
{
  string *args;
  object ob;

  ::autoload_shadow(arg);
  args = explode(arg, ",");

    seteuid(getuid());

  if (shadow_who->query_wiz_level())
  {
    tell_object(shadow_who, "The hair shadow has been changed " +
        "to /d/Calia/gelan/specials/hair_shadow.c, and the " +
        "command soul is /d/Calia/gelan/specials/hair_cmdsoul.c. " +
        "It's impossible to 'update' a wizard via code, so " +
        "you'll have to do it yourself.\n");
    shadow_autoshadow_destruct();
    return;
  }

/* Patch to 'convert' players to the new shadow. */
/* Clones the new shadow. */
  ob = clone_object(HAIRSTYLE_SHADOW);
/* Shadows the player with the new shadow */
  ob->shadow_me(shadow_who);
  ob->autoload_shadow(arg);
/* Adds new shadow to the player's autoshadow list. */
  shadow_who->add_autoshadow(MASTER_OB(ob) + ":" + (arg ? arg : ""));
/* Completes removal of current shadow. */
  shadow_autoshadow_destruct();
  return;

  if (!args) {
      set_alarm(1.0, 0.0, "shadow_autoshadow_destruct");
      return;
  }

  if (sizeof(args) != 3) {
      set_alarm(1.0, 0.0, "shadow_autoshadow_destruct");
      return;
  }

  length = lengths[args[0]];
  colour = colours[args[1]];
  style = styles[args[2]];
  if ((!length) || (!colour) | (!style)) {
      set_alarm(1.0, 0.0, "shadow_autoshadow_destruct");
      return;
  }

  hairstyle = length + ", " + colour + " and " + style; 
  shadow_who->add_subloc(HAIRSTYLE_SUBLOC, this_object()); 
  set_alarm(1.0, 0.0, "add_hair_commands"); 
}

