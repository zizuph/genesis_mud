

/*
 * Based on:
 * /std/shadow.c
 *
 * This is a shadow object curse 
 *  ... "/d/Krynn/turbidus_ocean/obj/tavernkeeper_sailorcurse"
 * on players that causes ships
 * they board to become cursed
 * (std_boat_in.c)...
 * which allows for onboard mishaps
 *  ... "/d/Krynn/turbidus_ocean/obj/tavernkeeper_shipcurse"
 *
 * Vitwitch 2021
 *
 * 20211025 - Cotillion
 * - Possibly fixed shadow removal
 *
 * 20211030 - Vitwitch
 *   ... additional safeguards added for shadow removal
 */

#pragma save_binary
#pragma strict_types

#include "/sys/macros.h"

static object	shadow_who;	/* Which object are we shadowing */

#define CURSESHADOW1 "/d/Krynn/turbidus_ocean/obj/tavernkeeper_shipcurse"
#define CURSEMINUTES 48

#define DISABLE_EFFECTS 0

int gRemovalAlarmID;

/* prototypes */
public void remove_sailor_curse_shadow();
public void remind_sailor_curse();
public void remove_shadow();

/*
 * Function name: autoload_shadow
 * Description  : Called by the autoloading routine in /std/player_sec
 *                to ensure autoloading of the shadow.
 * Arguments    : mixed arg - possible arguments.
 */
public void
autoload_shadow(mixed arg)
{
    float secs;
    if (!objectp(shadow_who))
    {
	shadow_who = previous_object();
	shadow(shadow_who, 1);
        shadow_who->catch_msg("\nA cold salt wind blows over "+
        "your soul... you feel strangely burdened once more.\n\n");
        secs = 60.0 * itof(CURSEMINUTES);
        gRemovalAlarmID = set_alarm(secs,0.0,&remove_sailor_curse_shadow());
        set_alarm(1.0,0.0,remind_sailor_curse);
    }
}

/*
 * Function name: shadow_double
 * Description  : Checks whether a certain shadow(file) is already
 *                shadowing a certain object.
 * Arguments    : string fname - the filename of the shadow to check.
 *                object ob    - the object to check whether it is already
 *                               shadowed by fname.
 * Returns      : int 1/0 - true if the ob is already shadowed by fname.
 */
static int
shadow_double(string fname, object ob)
{
    while (objectp(ob = shadow(ob, 0)))
    {
	if (fname == MASTER_OB(ob))
	{
	    return 1;
	}
    }

    return 0;
}    


/*
 * Function   : remove_object
 * Description: Ensure that we remove the shadow object too
 */
public void 
remove_object() 
{ 
    if (objectp(shadow_who))
    {
        shadow_who->remove_object();
    }
    destruct();
}


public void 
remove_shadow()
{
    int flag = shadow_who->remove_autoshadow(MASTER);
    if (!flag)
        shadow_who->catch_msg("There is a wrongness in the fabric of space -- "+
          "the curse of Nax Zeb remains with you. Commune with a wizard.\n"); 
    destruct();
}


public varargs int
shadow_me(mixed to_shadow)
{
    int flag;
    float secs;

    if (stringp(to_shadow))
    {
	to_shadow = find_player(to_shadow);
    }
    
    if (!objectp(to_shadow))
    {
	to_shadow = previous_object();
    }

    if ((!objectp(shadow_who)) &&
	(!shadow_double(MASTER, to_shadow)))
    {
	if (shadow(to_shadow, 1))
	{
	    shadow_who = to_shadow;

            shadow_who->catch_msg("\nA cold salt wind blows over "+
            "your soul... you feel strangely burdened.\n"+
            "Albatross! Your shadow on deck could unleash catastrophe!\n\n");
            secs = 60.0 * itof(CURSEMINUTES);
            gRemovalAlarmID = set_alarm(secs,0.0,&remove_sailor_curse_shadow());

            set_alarm(1.0,0.0,remind_sailor_curse);

            flag = shadow_who->add_autoshadow(MASTER);
            if ( !flag )
	        return 0;
            else 
	        return 1;
	}
    }
    return 0;
}


int
report_sailor_curse()
{
    mixed adata = get_alarm(gRemovalAlarmID);

    // 1 KRYNN-hour = 2 NETHER-minutes
    return 1 + ftoi(adata[2] / 120.0);
}


public void
remind_sailor_curse()
{
    string str;
    int krynnhr;
    mixed adata;
    adata = get_alarm(gRemovalAlarmID);

    if ( DISABLE_EFFECTS ) return;

    str = "\nThe death-curse of Nax Zeb lies upon you..."+
         " a prayer to Zeboim to take you in cold stormy fury!\n\n"+
         "Only a fool would risk sailing her waters until "+
         "she forgets about you.";

    // 1 KRYNN-hour = 2 NETHER-minutes
   krynnhr = 1 + ftoi(adata[2] / 120.0);

    if ( krynnhr == 1 ) 
       str = sprintf("%s You guess about %d Krynn hour remains until that time.",
               str,krynnhr);
    else
       str = sprintf("%s You guess about %d Krynn hours remain until that time.",
               str,krynnhr);
    str = str + " You know Zeboim never sleeps -- and nor should you. "+
           "Beware the sea!!\n\n";

    shadow_who->catch_msg(str);

    // alarm interval previously 120 secs (1 Krynn Hour)
    set_alarm(480.0,0.0,remind_sailor_curse);

    return;
}


public object
query_shadow_who()
{
    return shadow_who;
}


mixed
aboard_ship( object player )
{
    if ( !player || !objectp(player) ) return 0;
    object ship = environment(player);

    if ( !objectp(ship) ) return 0;
    if ( !ship->query_ship() ) return 0;
    return ship;
}


int
is_sailor_curse_shadow()
{
    return 1;
}

int
is_a_shadow_cursed_sailor()
{
    return 1;
}

int
shadow_sailor_curse_number()
{
    return 4;
}


int
remove_sailor_curse_shadow()
{
    string str = "\nA lull settles upon your soul, "+
          "the cold salt winds blow no more.\n"+
          "You feel free of the death-curse of Nax Zeb.\n"+
          "Zeboim has forgotten you.\n\n";
    shadow_who->catch_msg(str);
    remove_shadow();
    remove_object();  // VW added 20211030
    return 1;
}


void
enter_env(object dest, object old)
{
    int flag;

    shadow_who->enter_env(dest,old);

    if ( DISABLE_EFFECTS ) return;

    // not a ship
    if ( !dest->query_ship() ) return;

    /* 
     * IS a ship... but if there is no ship_size, then the 
     * shipcurse is not invoked (prevents cursing GSL ships)
     *
     * ... and the player gets dumped back where they came from
     */ 
    if ( !dest->query_ship_size() )
    {
        shadow_who->catch_msg("\nA cold salt wind blows over "+
          "your soul... your burden of bad luck "+
          "seeks to board the vessel as well... the vessel resists "+
          "mightily with a shudder... The captain reacts to "+
          "your presence, shouting, 'Albatross! Albatross!', "+
          "whereupon you are tossed back on shore!\n\n" + 
          "Dazed from the fall... you are not sure where you are...\n\n");

        tell_room(old,
           "\n" + QCNAME(shadow_who) + " tries to board the vessel " +
           "but the captain shouts, 'Albatross! Albatross!', "+
            "whereupon " + QTNAME(shadow_who) + " is tossed back on shore!\n\n",
               shadow_who);

        shadow_who->move_living("M",old,0,1);
        return;
    }

    flag = dest->is_a_shadow_cursed_ship();
    if ( flag ) 
    {
        shadow_who->catch_msg("\nA cold salt wind blows over "+
          "your soul... you feel your burden of bad luck "+
          "add to that already carried by the "+
          "vessel in which you stand.\n\n");
        return;
    }

    setuid();
    seteuid(getuid());
    object shdw = clone_object(CURSESHADOW1);

    if (!shdw->is_ship_curse_shadow())
        shdw->remove_object();
    flag = ( shdw->shadow_me(dest) );

    if ( flag ) 
    {
        shadow_who->catch_msg("\nA cold salt wind blows over "+
          "your soul... you feel your accursed burden "+
          "expand to stain the vessel in which you stand."+
          "Unless you leave, this vessel risks calamity under sail!\n\n");

        tell_room(dest,"\nA cold salt wind blows upon the arrival "+
           "of a newcomer -- the very timbers and rigging of the "+
           "vessel in which you stand seem to throb with anger.\n\n",
            shadow_who);
    }

    return;
}


