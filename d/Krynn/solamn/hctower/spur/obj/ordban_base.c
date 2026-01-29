/*
 *    Banner base file.
 *    by Teth, Grace, and Jeremiah
 *    Jan.30, 1996
 *    idea by Rastlin ---> add evil emotes as well
 *         by Rastlin ---> add to player's desc
 */

inherit "/std/object";
 
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
 
 
/*
 *    Prototypes
 */
void create_banner();


/*
 *    Global variables
 */
string b_extra_short = "picture of Teth",
       b_long_descr  = "This is a standard Solamnian banner.\n",
       b_god         = "Paladine",
       b_color       = "white",
       b_patrol      = "everywhere";

void
init_arg(string arg)
{
}
 
void
create_object()
{
   seteuid(getuid());
    create_banner();
    set_name("banner");
    set_adj("Solamnic");
    set_short("@@short_descr");
    set_pshort("Solamnic banners");
    set_long("@@long_descr");
   add_prop(OBJ_I_WEIGHT, 3500);
   add_prop(OBJ_I_VOLUME, 8000);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_I_NO_STEAL, 1);
}
 
void
create_banner() { }


void
set_extra_short(string str)
{
    if (strlen(str))
    {
        b_extra_short = str;
    }
}


string
short_descr()
{
    return b_color + " Solamnic banner bearing a " + b_extra_short;
}


void
set_long_descr(string str)
{
    if (strlen(str))
    {
        b_long_descr = str;
    }
}

string
long_descr()
{
    return b_long_descr;
}


void
set_deity(string str)
{
    if (strlen(str))
    {
        b_god = str;
    }
}

void
set_patrol(string str)
{
    if (strlen(str))
    {
        b_patrol = str;
    }
}

void
set_color(string str)
{
    if (strlen(str))
    {
        b_color = str;
    }
}

void
init()
{
   ::init();
   add_action("do_help", "help");
   add_action("battlecry", "bncry");
   add_action("lodge", "bnlodge");
   add_action("thrust", "bnthrust");
   add_action("bannerwave", "bnwave");
}
 
void
enter_env(object dest, object old)
{
    if (interactive(dest))
      dest->add_subloc("banner_subloc",this_object());
    ::enter_env(dest, old);
}
 
void
leave_env(object from, object to)
{
   if (interactive(from))
      from->remove_subloc("banner_subloc");
    ::leave_env(from, to); 
}
 
string
show_subloc(string subloc, object me, object for_obj)
{
   if (subloc != "banner_subloc")
      return me->show_subloc(subloc, me, for_obj);
   if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   
   if (for_obj == me)
      return "You are bearing the Banner of the " +
         C(b_extra_short) + ".\n";
   else
    return C(PRONOUN(me)) + " bears the Banner of the " +
    C(b_extra_short) + ", marking " + OBJECTIVE(me) + " as " +
    "leader of the " + C(b_patrol) + " patrol.\n";
   
}
 
 
int
do_help(string str)
{
   if (str == "banner")
      {
        write("The bearer of the " + b_extra_short + " banner can do the "
          + "following:\n" +
         "- help banner  - This message.\n" +
         "- bncry        - Utter a battlecry.\n" +
         "- bnlodge      - Lodge the banner in the ground.\n" +
         "- bnthrust     - Thrust the banner forward.\n" +
         "- bnwave       - Wave the banner in the air.\n");
      return 1;
   }
   return 0;
}
 
static int
battlecry()
{
   write("You utter a formidable battlecry in the name of " + b_god
    + " calling your brother and sister Knights to arms!\n");
   say(QCTNAME(TP) + " calls you to arms by uttering a formidable " +
    "battlecry in the name of " + b_god + "! Adrenaline rushes " +
    "through your veins.\n");
   return 1;
}
 
static int
lodge()
{
   write("You briefly lodge the pole of the banner into the ground, " +
      "demanding everyone's attention.\n");
   say(QCTNAME(TP) + " grabs your attention by firmly lodging the " +
      "pole of the banner into the ground, for a brief time.\n");
   return 1;
}
 
static int
thrust()
{
   write("You thrust the banner forward in a swift motion, presenting " +
      "the " + b_extra_short + " for all to see.\n");
   say(QCTNAME(TP) + " thrusts the banner forward in a quick motion. " +
      "Your eyes can't help but be drawn to the " + b_extra_short +
      ", a symbol of the Knights' virtues.\n");
   return 1;
}
 
static int
bannerwave()
{
   write("You wave the banner back and forth, the now-rushing air " +
      "catching it and making it flutter.\n");
   say(QCTNAME(TP) + " waves the banner slightly, catching the air. " +
      "The fluttering breeze ripples the banner, imbuing the symbol with " +
      "life, a sign of the vigour and honour of the Knighthood.\n");
   return 1;
}

