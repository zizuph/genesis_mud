/* Created by Sir Macker 02/01/95 */

inherit "/std/weapon";
inherit "/sys/global/cmdparse.c";
#include <wa_types.h>
#include <std.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#define DEFAULT_NAME "No_Name"
#define SABRE_LOG "/d/Krynn/icewall/sabre_log"

string name = DEFAULT_NAME;
object my_owner;
int extra_sword= 0;
int extra_parry= 0;
int extra_quick = 0;

object get_owner(object ob); /*prototype*/

create_weapon()
{
        set_name("sabre");
        add_name("crystaline_sabre");
        add_name("sword");
        set_adj("crystaline");
        set_short("crystaline sabre");
        set_long("@@my_long");
        set_default_weapon(20, 20, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
        add_prop(OBJ_I_VOLUME, 2600);
        set_alarm(1.0, 0.0, "establish_owner");
        add_prop(OBJ_I_WEIGHT, 1700); /*It's crystal...not metal*/
	add_prop(OBJ_I_VALUE, 1500+random(1000));
	set_hit(40);
	set_pen(40);
        set_wf(TO);
  add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
	add_prop(MAGIC_AM_ID_INFO,({
		"This sabre is a magical blade which can be named.", 1,
		"It seems as though the blade makes its wielder quicker.", 25,
		"The crystaline sabre also improves its wielder's " +
		"abillity to use a sword and parry attacks temporarily.", 60,
		"Anyone can wield this sword, but greater warriors wield " +
		"it much more effectively than young adventurers.", 85}));
	add_prop(OBJ_S_WIZINFO,
		"The crystaline sabre can be named. It is a magical weapon " +
	"with the following properties: \n"+
		"-It won't break.\n"+
		"-It adds quickness to the wielder.\n"+
		"	(25+random(20))\n\n"+
		"-It increases the wielder's sword and parry skills.\n" +
		"       random(10) and random(10) up to 90 total\n"+
		"       This drains 1/8th of the player's mana.\n\n"+
		"-It's hit and pen are dependant upon the wielder's ave stats,\n"+
		"       the max being 40-40.\n"+
		"set_hit(((TP->query_average_stat())*3/10)+10);\n"+
		"set_pen(((TP->query_average_stat())*3/10)+10);\n\n"+
		"");
	set_likely_break(0);
}

string my_long()
{
string str;
        if(!living(E(TO)))
                str = "This sabre looks as though it is magically " +
                "made of an icy crystaline material of some kind. " +
                "Perhaps you should get it if you'd like to take a " +
                "closer look at it.\n";
        else if(name != DEFAULT_NAME)
                str = "This sabre looks as though it is magically " +
                "made of an icy crystaline material of some kind. " +
                "This is your blade, " +
                "and you have appropriately named it " + C(name) + ". " +
                "May it aid you in combat well!\n";
        else
                str = "This sabre looks as though it is magically " +
                "made of an icy crystaline material of some kind. " +
                "This sword is now yours to wield in combat. You may " +
                "also name your sword whatever you wish- in fact, you " +
                "have a gut feeling that the sword would like a name.\n";

        return str;
}


public void
init()
{
        ADA("name");
        return(::init());
}

int name(string what)
{
string ob_string, ob_name;
object *item_list;

        NF("Name what? The sabre?\n");
	if((!stringp(what))||(!strlen(what)))
		return 0;
        if(!parse_command(what, TP, " [my] [the] [crystaline] " +
                "%i %w", item_list, ob_name))
                return 0;
        if(strlen(ob_name) > 15)
                {
                NF("Sorry, but that name is just too damn long.\n");
                return 0;
                }
        if(SECURITY->exist_player(lower_case(ob_name)))
                {
                NF(C(lower_case(ob_name)) + " might not be happy " +
                "if you gave that name to your sabre.\n");
                return 0;
                }
        if(member_array(TO, item_list) != -1)
                {
                name = lower_case(ob_name);
                add_name(name);
                 add_name(C(name));
                set_short(C(name));
                TP->catch_msg("You look at your crystaline " +
                "sabre, and decide that \"" + query_short() + "\"" +
                " would be an appropriate name. The sabre vibrates in " +
                "approval of its new name.\n");
                say("You notice " + QTNAME(TP) + " carefully studying " +
                POSSESSIVE(TP) + " crystaline sabre and mumbling the " +
                "word \"" + C(name) + "\" to " + OBJECTIVE(TP) + "self.\n");
		write_file(SABRE_LOG, C(TP->query_real_name()) +
		"		" + query_short() + "\n");
                return 1;
                }
        return 0;
}





string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}

void
establish_owner()
{
        my_owner = get_owner(TO);
}

object get_owner(object ob)
{
object owner = ob;
      while(!((owner->this_room())||(interactive(owner))))
      owner = E(owner);
return owner;
}

varargs public int
move(mixed dest, mixed subloc)
{
object old_owner;
        old_owner = my_owner;
        if(!(::move(dest, subloc)))
        {
        my_owner = get_owner(dest);
        if(old_owner != my_owner)
        {
        set_short("crystaline sabre");
        remove_name(({name, C(name)}));
        name = DEFAULT_NAME;
        }
        }
     return 0;
}

int
increase_abillities()
{
	extra_quick = 25 + random(20);
	TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS)
		+ extra_quick);
	if((TP->query_skill(SS_PARRY) >= 90)||
		(TP->query_skill(SS_WEP_SWORD) >= 90))
		return 0;

	extra_sword = random(10);
	extra_parry = random(10);
	if((TP->query_skill(SS_PARRY) + extra_parry) > 90)
		extra_parry = 90 - TP->query_skill(SS_PARRY);
	if((TP->query_skill(SS_WEP_SWORD) + extra_sword) > 90)
		extra_sword = 90 - TP->query_skill(SS_WEP_SWORD);

	TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) + extra_parry);
	TP->set_skill_extra(SS_WEP_SWORD, TP->query_skill_extra(SS_WEP_SWORD) + extra_sword);
	TP->add_mana(-(TP->query_mana() / 8));
	return 1;
}

mixed wield()
{
        if(name == DEFAULT_NAME)
        {
                write("Just as you are about to raise the crystaline " +
                "sabre, the sword throbs in your hand.\n");
        set_alarm(1.0, 0.0, "write_message",
                "You have a strange feeling that there's something " +
                "you should do before wielding this blade.\n");
        return -1;
	}
		set_hit(((TP->query_average_stat())*3/10)+10);
		set_pen(((TP->query_average_stat())*3/10)+10);
		if(query_hit() > 40)
		{
		set_hit(40);
		set_pen(40);
		}
        write("You grip " + query_short() + " in both your hands " +
                "and raise it out in front of you, to eye level.\n");
        set_alarm(2.0,0.0,"write_message","You feel as though the " +
                "spirit of "+ query_short() +
                " is mingling with your own.\n");
        set_alarm(6.0, 0.0, "write_message", "You feel the sword " +
                "correcting for your weaknesses and adjusting for " +
                "your strengths.\n");
	if(increase_abillities())
		set_alarm(10.0, 0.0, "write_message", "Some of your mental " +
		"energy is drained by " + query_short() +
		" to help give it the power to aid you in combat.\n");
		set_alarm(11.0, 0.0, "write_message", 
		"A strange blue light from " + query_short() + " briefly " +
		"surrounds you. You suddenly feel quicker than lightning!\n");
        set_alarm(14.0, 0.0, "write_message","You and " + query_short() +
                " essentially become one powerfull weapon " +
                "with force enough to slay many enemies!\n");
        say(QCTNAME(TP) + " wields a crystaline sabre, which " +
                PRONOUN(TP) + " has named \"" +query_short()+"\".\n");
        set_alarm(2.0, 0.0, "say_message","You see " +query_short()+
                 " surround " + QTNAME(TP) +
                " with an eerie blue glow for a moment.\n");
        set_alarm(7.0, 0.0, "say_message", "The eerie glow " +
                "slowly fades away......\n");

return 1;
}

int unwield()
{
        write("You slowly lower " + query_short() + " to your side.\n");
        set_alarm(3.0, 0.0, "write_message",
                query_short() + " once again seems more like a normal sword.\n");
        say(QCTNAME(TP) + " slowly lowers " + POSSESSIVE(TP) +
                " blade, appropriately named \"" +query_short()+"\".\n");
        set_alarm(3.0, 0.0, "say_message", QCTNAME(TP) +
                " gives " + query_short() + " a blank look.\n");
	TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY) - extra_parry);
	TP->set_skill_extra(SS_WEP_SWORD, TP->query_skill_extra(SS_WEP_SWORD) - extra_sword);
	extra_parry = 0;
	extra_sword = 0;
	TP->change_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) -
		extra_quick);
	extra_quick = 0;
        return 1;
}
void
write_message(string str)
{
        write(str);
}

void
say_message(string str)
{
        say(str);
}


/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}


int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
  string msg;
  object wielder;

  wielder = query_wielded();
  if (phurt == -1 || phurt == -2) /*Missed by a lot*/
  {
    wielder->catch_msg("You swing " + query_short() + " at " +
		QTNAME(enemy) + " but miss so badly that you " +
		"almost cut yourself.\n");
    enemy->catch_msg(QCTNAME(wielder) + " wildly tries to hit you " +
		"with " +POSSESSIVE(wielder)+ " crystaline sabre but " +
		"doesn't even come close.\n");
    
    tell_watcher(QCTNAME(wielder) + " makes a complete ass of " +
		OBJECTIVE(wielder) + "self by feebley attempting " +
		"to hit " + QTNAME(enemy) + " with " + POSSESSIVE(wielder) + 
		" crystaline sabre.\n" ,enemy);
  }
  else if (phurt == 0) /*Barely missed*/
  {
    wielder->catch_msg(query_short() + " slices by " +QTNAME(enemy)+
		"'s " + hdesc + " so close to the skin that you " +
		"think you see a few small hairs falling to the ground.\n");
    enemy->catch_msg(QCTNAME(wielder) + "'s sabre, \""+ query_short() +
		"\", slices so close to your " + hdesc + " that you now " +
		"have a bald spot there.\n");
	tell_watcher(QCTNAME(wielder) + "'s sabre, \""+query_short() +
		"\", slices tiny hairs off "+ QTNAME(enemy)+ "'s " +
		hdesc + ".\n" ,enemy);
  }
  else
  {
    switch(phurt)
    {
      case 1..4: /*Barely hit*/
        wielder->catch_msg("With your amazing quickness, " +
		"you manage to scratch " + QTNAME(enemy) + "'s " +
		hdesc + " with " +query_short()+ ".\n");
        enemy->catch_msg("With stunning speed, " + QTNAME(wielder) +
		" scratches your " +hdesc+ " with his strange looking " +
		"crystaline sabre.\n");
        tell_watcher("Using \""+query_short()+"\", "+ QTNAME(wielder) +  
		" scratches " + QTNAME(enemy) +"'s " + hdesc + 
		" with amazing speed.\n", enemy);
        break;
      case 5..9: /*Weak hit*/
        wielder->catch_msg("You quickly slice at " + QTNAME(enemy) +
		"'s " +hdesc+ " with " + query_short() + 
		", hitting and harming " + OBJECTIVE(enemy) +
		" slightly.\n");
        enemy->catch_msg(QCTNAME(wielder) + " quickly slices into " +
		"your " +hdesc+ " with \""+ query_short()+ "\", " +
		"harming you slightly.\n");
        tell_watcher(QCTNAME(wielder) + " slightly hurts " +
		QTNAME(enemy) + "'s " +hdesc+ " with " +
		POSSESSIVE(wielder) + " crystaline sabre, \"" +
		query_short()+ "\".\n",enemy);
        break;
      case 10..19: /*Acceptable hit*/
        wielder->catch_msg("Guided by your hand, " + query_short() +
		" slashes into " + QTNAME(enemy) + "'s " +hdesc+
		" with blinding speed.\n");
        enemy->catch_msg("With help from " + QTNAME(wielder) +
		", \"" +query_name()+ "\" slashes into your " +
		hdesc+ " with blinding speed, causing you intense pain.\n");
        tell_watcher(QCTNAME(wielder) + "'s blade \"" + query_short() +
		"\" slashes into " +QTNAME(enemy)+ "'s " +
		hdesc+ " with blinding speed, causing " +OBJECTIVE(enemy)+
		" to wince in pain.\n" ,enemy);
        break;
      case 20..29: /*Good hit*/
        wielder->catch_msg("You use your mysterious agillity " 
		+"to plunge " +query_short()+ " into " +QTNAME(enemy) +  
		"'s " +hdesc+ ", doing some major damage.\n");
        enemy->catch_msg(QCTNAME(enemy) + " plunges \""+query_short()+
		"\" into your " +hdesc+ " before you can even think of " +
		"dodging.\n");
        tell_watcher(QCTNAME(wielder) + " streaks by you, and plunges \""+
		query_short() + "\" into the " +hdesc+ " of "+
		QTNAME(enemy) + ".\n",enemy);
        break;
      case 30..49: /*Very good hit*/
        wielder->catch_msg("You amaze yourself with tremendous " +
		"speed as " + query_short() + " digs a deep gash into " + 
		QTNAME(enemy)+ "'s " +hdesc+ ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " is in your face before " +
		"you can blink, and " + PRONOUN(wielder)+ "digs deep into your " +
		hdesc+ " with \""+ query_short() +"\", leaving a nasty " +
		"wound.\n");
        tell_watcher(QCTNAME(wielder) + " is in " +QTNAME(enemy)+
		"'s face before you can blink, digging a deep hole into " +
		POSSESSIVE(enemy) + " " + hdesc+ " with \"" + query_short() + 
		"\".\n",enemy);
        break;
      case 50..69: /*Damn good hit!*/
        wielder->catch_msg("Quicker than lightning, you guide " +query_short()+
		" through " +QTNAME(enemy)+ "'s " +hdesc+ " like butter, " +
		"leaving a terrible wound behind!\n");
	enemy->catch_msg(QCTNAME(wielder)+" moves faster than lightning"+
		", as " +PRONOUN(wielder)+ " rips through the internals " +
		"of your "+hdesc+ " with \""+query_short()+ 
		"\", leaving you in a world of hurt!\n");
        tell_watcher("With lightning speed, " +QTNAME(wielder)+
		" rips through " +QTNAME(enemy)+ "'s "+hdesc+
		" with \""+query_short()+ "\", leaving " +OBJECTIVE(enemy) +
		" in a world of hurt!\n",enemy);
        break;
	case 70..MAXINT :  /*Not much you can do now other than pick up fallen limbs*/
        wielder->catch_msg("You bid farewell to " +QTNAME(enemy)+ 
		" as you SLICE and DICE " +OBJECTIVE(enemy)+ " with " +
		query_short()+ " in an attempt to deliver " +
		OBJECTIVE(enemy) + " into the hands of DEATH!!\n" +
		"Blood flies everywhere!\n");
        enemy->catch_msg(QCTNAME(wielder) + " bids you farewell as " +
		PRONOUN(wielder) + " sharpens \"" +query_short()+
		"\" on your skull!!\n" +
		"Blood flies everywhere!\n");
        tell_watcher(QCTNAME(wielder) + " raises \""+query_short()+
		"\" high above " +POSSESSIVE(wielder)+ " head, and " +
		"brings it down in a wide gracefull arc, slamming the " +
		"blade into " +QTNAME(enemy)+ "'s head!!\n" +
		"Blood flies everywhere!\n",enemy);
        break;
      default: /*Make it look pretty good*/
        wielder->catch_msg("You quickly leap at " +QTNAME(enemy)+
		", slashing into " +OBJECTIVE(enemy) + " with " +
		query_short()+ ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " quickly jumps at you, " +
		"slashing into your " +hdesc+ " with " +POSSESSIVE(wielder)+
		" sabre, \""+ query_short()+".\n");
        tell_watcher(QCTNAME(wielder) + " quickly leaps at " +
		QCTNAME(enemy) + " and slashes into " +OBJECTIVE(enemy)+
		" with " +POSSESSIVE(wielder)+ " sabre, \""+
		 query_short()+".\n",enemy);
        break;
      }
/*    special_attack(enemy,dam); */
  }
  return 1;
}

