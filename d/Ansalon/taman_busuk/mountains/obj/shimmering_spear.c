/**
 * Magical Polearm.  
 * Designed By Hades.
 * Louie 2004
 *
 * Milan 2.11.2004 bugfixes.
 * Cotillion 16.11.2004 
 * - Fixed weight/volume. approx 1.4 meters at 500kg/m3
 */
 
inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>
#include <stdproperties.h>

/** prototypes **/
private int charge_counter;
private int is_recognized;
string long_desc();
int do_study(string str);
int do_charge(string str);

/* Kender prop, allow alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

/* Kender prop, allow alter ability to change the descriptions of the weapon */
public mixed
query_prop(string prop)
{
    if (prop == OBJ_I_CONVERT_HOOPAK)
        return is_recognized;
    
    return ::query_prop(prop);
}

public void
create_weapon()
{
    set_name("spear");
    add_name("pole");
    set_short("plain wooden pole");
    set_adj(({"plain","wooden"}));
    set_long("@@long_desc@@");
	
    charge_counter = 1;
    is_recognized = 0;
	
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment"}));
    
    /*
      add_prop(MAGIC_AM_MAGIC, ({ 15, "death"})); //poison, acid
      add_prop(MAGIC_AM_MAGIC, ({ 10, "fire"}));  //fire
      add_prop(MAGIC_AM_MAGIC, ({ 15, "water"})); //cold, acid
      add_prop(MAGIC_AM_MAGIC, ({ 10, "air"}));  //lightning
    */
	
    add_prop(MAGIC_AM_ID_INFO,
        ({"This weapon appears to be enchanted with "+
              "evil magic from the depths of the Abyss, "+
              "but would require study to unlock its secrets.", 20,
              "This weapon appears to be enchanted with "+
              "evil magic from the depths of the Abyss.  "+
              "It has been blessed by the Dark Queen, " +
              "and imbued with the essences of Her loyal "+
              "children, the chromatic dragons.  When "+
              "studied and recognized, it will "+
              "gain the ability to slowly build up " +
              "energy and eventually "+
              "release it against an enemy.", 50}));
    add_prop(OBJ_S_WIZINFO, "This weapon must be inspected "+
        "using the 'study <name>' command.  After that it "+
        "becomes a magical, evil weapon.  Only evil-aligned "+
        "can wield it.  It will build up counters during "+
        "combat, and eventually do a special attack for "+
        "extra damage.");

    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hit(25);
    set_pen(25);
    set_wf(this_object());
    set_hands(W_ANYH);
	
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(42, 42));
    add_prop(OBJ_I_WEIGHT, 1700 + 700); /* Spear + Head */
    add_prop(OBJ_I_VOLUME, 3166);
}

void
init()
{
    ::init();
	
    add_action(do_study, "study");
    add_action(do_charge, "chargeup");
	
}

int
do_charge(string str)
{
    if (!this_player()->query_wiz_level())
        return 0;
	
    this_player()->catch_tell("WIZINFO: Charging up!\n");
    charge_counter = 1000;
	
    return 1;
}


string
long_desc()
{
    string desc;
	
    if (!is_recognized) 
    {
        desc = "This is just a plain wooden pole and "+
            "not worth studying.\n";
    }
    else 
    {
        desc = "This magnificent spear is comprised "+
            "of a short black haft and a tip that "+
            "shimmers in a variety of colours...red, "+
            "blue, green, black, and white.  " +
            "The colours swirl along the blade like "+
            "mist, but the tip is cold and hard to "+
            "the touch.  "+
            "The entire weapon appears to be surrounded "+
            "by an aura of energy, waiting to be unleashed.\n";
    }
	
    return desc;
}


public mixed
wield(object obj)
{

    if (!is_recognized)
    {
        return 0;
    }
	
    if (this_player()->query_alignment() < -99)
    {
        write("The colours of the "+query_short()+
            " seem to pulse and shimmer brightly "+
            "as you wield it.\n");
        tell_room(environment(this_player()),
            "The colours of the "+query_short()+
            " seem to pulse and shimmer brightly "+
            "as "+ QTNAME(this_player())+" wields it.\n",
            this_player());
        return 1;
    }
    else
    {
        return "The sinister energy of the "+query_short()+
            " rejects you!\n";
    }
	

}

public void
transform_weapon(int make_recognized)
{
    if (!make_recognized)
    {
        // Transform the weapon back.
        set_short("plain wooden pole");
        set_adj(({"plain","wooden"}));        
        set_hit(25);
        set_pen(25);
        is_recognized = 0;
    }
    else
    {
        // Transform the weapon into shimmering.
        set_adj(({"shimmering","multi-coloured","multi-colored"}));
        set_short("shimmering multi-coloured spear");
        set_hit(42);
        set_pen(36);
        is_recognized = 1;  
    }
    if (wielder = this_object()->query_wielded())
    {
        wielder->update_weapon(this_object());
    }
}

int
do_study(string str)
{
    object wielder, spear;
	
    if (is_recognized)
    {
        return 0;
    }
	
    if (!strlen(str) ||
        !parse_command(str, environment(this_object()),"[the] %o", spear))
    {
        notify_fail("Study what?\n");
        return 0;
    }
	
    if (this_player()->query_alignment() > -100)
    {
        write("As you study the wooden pole, a flash of " +
            "colours flickers through your mind...black, red, "+
            "blue, white, and green.  " +
            "There is definitely more to this weapon than meets "+
            "the eye.\n");
    }
    else
    {
        write("As you study the wooden pole, a flash of " +
            "colours flickers through your mind...black, red, "+
            "blue, white, and green.  \n" +
            "A soft voice whisper in your head:  You "+
            "recognized me, and I am reborn because of it!\n"+
            "The plain wooden pole suddenly transforms!\n");

        transform_weapon(1);				
    }
    return 1;
}

/*
 * Milan commented out. Why not use standard function instead???

 static void
 tell_watcher(string str, object enemy)
 {
 object me,*ob;
 int i;

 me = query_wielded();
 ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
 ob -= ({ enemy });
 for (i = 0; i < sizeof(ob); i++)
 if (!ob[i]->query_option(OPT_NO_FIGHTS) && CAN_SEE_IN_ROOM(ob[i]))
 {
 if (CAN_SEE(ob[i], me))
 ob[i]->catch_msg(str);
 else
 tell_object(ob[i], "Someone is hit by someone.\n");
 }
 }
*/

/**
 * Do a special attack sometimes
 *
 * Milan modified slightly to fix runtimes and other stuff
 */
public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string *how, descrip;
    string *what = ({"injuring","hurting","harming","damaging"});
    int    penet;
    object me;
    object who = query_wielded();

    if (!is_recognized || !objectp(who) || !objectp(enemy))
    {
/*
	return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
*/
    ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
    return 0;
    }

    if (dam > 0)
	charge_counter++;
    
    if ((dam <= 20) || random(4) || (charge_counter < 10))
    {
/*
	return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
*/
        ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
        return 0;
    }

    switch(random(5))
    {
    case 0: descrip = "ignites in a red aura";
        break;
    case 1: descrip = "is enshrouded in a black mist";
        break;
    case 2: descrip = "flashes in a bright light";
        break;
    case 3: descrip = "is surrounded by a green fog";
        break;
    case 4: descrip = "emits a white mist";
        break;
    default: descrip = "does a cool thing (bug this!)";
    }
		
    who->catch_tell("Your "+query_short()+
        " suddenly "+descrip+
        ", " + what[random(sizeof(what))] +
        " " + enemy->query_the_name(who)+"!\n");
    enemy->catch_tell(capitalize(who->query_the_name(enemy)) +
        "'s "+query_short()+" suddenly "+
        descrip +
        ", " + what[random(sizeof(what))] + " you!\n");
    who->tell_watcher(QCTNAME(who)+"'s "+query_short()+
        " suddenly "+descrip+", " +
        what[random(sizeof(what))] +
        " "+QTNAME(enemy)+"!\n", enemy);
			
/*
    penet = dam * 2 + 30;
*/
   penet = MAX(dam * 2 + 30, dam * 3);
    enemy->hit_me(penet, MAGIC_DT, me, -1);
		
    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(who);
	who->catch_tell("You hear a woman's soft laughter echoing in your head.\n");
    }
		
    if (who->query_wiz_level()) 
	who->catch_tell("WIZINFO: Dam was "+dam+"!\n");

    charge_counter -= 10;
/*
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
*/
    ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
    return 0;
}

public string
query_recover()
{
    string recover_string = ::query_recover();
    recover_string += "#REC#" + is_recognized;
    recover_string += "#CHRG#" + charge_counter;
    return recover_string;
}

public void
init_recover(string arg)
{
    ::init_recover(arg);
    string foobar;

    sscanf(arg, "%s#REC#%d#CHRG#%d", foobar, is_recognized, charge_counter, foobar);
    transform_weapon(is_recognized);
}
