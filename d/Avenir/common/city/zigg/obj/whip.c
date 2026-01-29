// file name:   whip.c
// creator(s):  Zielia
// last update:
//    Lucius, May 2016: Added locations support.
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/lib/commands";

#include "zigg.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <adverbs.h>
#include <macros.h>

#define SUBLOC "_whip_"
#define HIT 30
#define PEN 10

public int
create_weapon(void)
{
   setuid();
   seteuid(getuid());

   set_name("whip");
   set_short("sleek black whip");
   set_long("This snake whip is made of the black hide of some unknown "+
      "creature. It has a 4-strand wrist loop to prevent it being pulled "+
      "away from you and is made of 12 plated strands to endure frequent "+
      "impact well. It is about as longer than dwarf and tapers for the  "+
      "first three quarters until it becomes quite narrow and should "+
      "sting sharply. The last portion is untapered to provide an "+
      "even line of impact. At the end is a long twine cracker which you "+
      "imagine makes this whip sound fearsome. It will stay secure "+
      "at your waist when you're not wielding it.\n");
   set_adj(({"sleek", "black", "snake", "sybarun", "ziggurat"}));
   set_wt(W_CLUB);
   set_hit(HIT);
   set_pen(PEN);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   set_wf(this_object());
   add_prop(OBJ_M_NO_STEAL,
       "It is firmly secured: You'd be caught for sure!\n");
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(20) -10);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB) +
        random(50) - 25);
   add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;

   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))

      return "";

   if (for_obj == carrier)
      str = "You have a sleek black whip secured at your waist.\n";
   else
      str = capitalize(HE(carrier)) +" has a sleek black whip secured at "+
            HIS(carrier) + " waist.\n";

   return str;

}

public void
remove_object(void)
{
    if (IS_CLONE)
	ENV()->remove_subloc(SUBLOC);

    ::remove_object();
}

public int
wield(object what)
{
   write("You pull your "+ short() +" from your waist, letting it uncoil at "+
      "your feet.\n");

   say(QCTNAME(TP)+ " pulls "+ HIS(TP) +" "+ short() +" from "+ HIS(TP) +
	" waist, letting it uncoil at "+ HIS(TP) +" feet.\n");

   TP->remove_subloc(SUBLOC);
   return 0;
}


public int
unwield(object what)
{
    write("You let the coils of your "+ short() +
	" settle on the floor and then gather them up and secure it at your "+
	"waist.\n");

    say(QCTNAME(TP)+ " lets the coils of "+ HIS(TP) +" "+ short() +
	" settle on the floor and then gathers them up and secures it at "+
	HIS(TP) +" waist.\n");

    TP->add_subloc(SUBLOC, this_object());
    return 1;
}

public void
enter_env(object to, object from)
{
   ::enter_env(to, from);

   if (living(to))
      to->add_subloc(SUBLOC, this_object());
}

public void
leave_env(object from, object to)
{
   ::leave_env(from, to);
   from->remove_subloc(SUBLOC);
}

/* If you modify this, you need to update the wmarks.c
 * code as well to account for cover.
 */
private static string *places = ({
    "arm", "bosom", "chest", "shoulder", "leg",
    "tummy", "stomach", "thigh", "bottom", "back",
    "face", "hand", "foot",
});

public int
do_lash(string str)
{
    object ob;
    string verb = query_verb(), verb2;
    int attr = ACTION_CONTACT | ACTION_MACTIVITY |
		ACTION_INTIMATE | ACTION_OFFENSIVE;
    
    if (!strlen(str))
	return NF(CAP(verb) +" what?\n");

    if (!wielder)
	return NF("You should wield it first.\n");

    object *oblist = filter(all_inventory(ENV(TP)) - ({ TP }), living);

    if (!parse_command(str, oblist,
	    "[the] %o [on] [the] / [his] / [her] / [its] %s", ob, str))
    {
	return NF(CAP(verb) +" <whom> [on] [the] <where> "+
	    "[how] with your "+ short() +"?\n");
    }

    string *how = parse_adverb_with_space(str, "sharply", 1);

    if (!strlen(how[0]))
	how[0] = "back";
    else if (how[0] == "ran" || how[0] == "random")
	how[0] = one_of_list(places);

    if (!IN_ARRAY(how[0], places))
    {
	write("The location \""+ how[0] +"\" is not valid.\n"+
	    "Try striking at \"random\" spots to learn of some.\n");
	return 1;
    }

    oblist = ({ ob });

    if (verb == "lash")
	verb2 = "lashes";
    else
	verb2 = verb + "s";

    actor("You "+ verb, oblist, "'s "+ how[0] + how[1] +" with your "+ short() +
	    ", leaving behind a painful looking red mark.");
    all2act(" "+ verb2, oblist, "'s "+ how[0] + how[1] +" with "+ HIS(TP) +
	    " "+ short() +", leaving behind a painful looking red mark.",
	    how[1], attr);
    target(" "+ verb2 +" your " + how[0] + how[1] +" with "+ HIS(TP) +" "+
	    short() +". It slashes across your skin leaving behind a stinging, "+
	    "tender mark.", oblist, how[1], attr);

    if (!present("Zig::WMark", oblist))
    {
	object marks = clone_object(ZIG_OBJ +"wmarks");
	marks->move(oblist[0]);
    }

    present("Zig::WMark", oblist[0])->add_lashes(how[0]);
    return 1;
}

public int
do_crack(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "loudly", 0);

   if (!this_object()->query_wielded())
   {
      notify_fail("You should wield it first.\n");
      return 0;
   }

   if (!stringp(how[0]))
   {

      write("CRACK!\nYou crack your sleek black whip"+ how[1] +".\n");

      say("CRACK!\n"+QCTNAME(TP)+ " cracks "+ HIS(TP) +
         " sleek black whip"+ how[1] + ".\n");

      return 1;
   }

   return 0;
}

public void
init(void)
{
    ::init();

    add_action(do_lash,  "lash");
    add_action(do_lash,  "whip");
    add_action(do_lash,  "strike");
    add_action(do_crack, "crack");
}
